#include "spellcheck.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string &source) {
  auto spaces = find_all(source.begin(), source.end(), isspace);
  spaces.push_back(spaces.back());

  auto ret = Corpus{};
  auto result = std::inserter(ret, ret.end());
  std::transform(
      spaces.begin(), spaces.end() - 1, spaces.begin() + 1, result,
      [&source](auto it1, auto it2) { return Token{source, it1, it2}; });

  std::erase_if(ret, [](Token t) { return t.content.empty(); });

  return ret;
}

std::set<Mispelling> spellcheck(const Corpus &source,
                                const Dictionary &dictionary) {
  auto mis_spelled_words =
      source | std::ranges::views::filter([&dictionary](auto token) {
        // filter correct-spelled words
        return !dictionary.contains(token.content);
      }) |
      std::ranges::views::transform([&dictionary](auto token) {
        // transform misspelled words into struct Mispelling{}
        auto suggestion_view =
            dictionary | std::ranges::views::filter([&token](auto word) {
              // collect reasonable suggestions by filter a view on dictionary
              return levenshtein(word, token.content) == 1;
            });
        return Mispelling{
            token, std::set(suggestion_view.begin(), suggestion_view.end())};
      }) |
      std::ranges::views::filter([](auto mis_spelled_word) {
        // filter really bad misspelled words without suggestions
        return mis_spelled_word.suggestions.size() > 0;
      });

  return std::set<Mispelling>(mis_spelled_words.begin(),
                              mis_spelled_words.end());
};

/* Helper methods */

#include "utils.cpp"