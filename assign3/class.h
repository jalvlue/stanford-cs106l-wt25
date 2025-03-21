#include <vector>

#define DEFAULT_THRESHOLD 20

 class GC {
public:
  GC();
  GC(int);
  void set_threshold(int);
  int get_threshold() const;
  void throw_garbage(int);
  std::vector<int> get_buffer();
  void force_clear();

private:
  int threshold;
  std::vector<int> buf;
  void clear();
  bool full();
};
