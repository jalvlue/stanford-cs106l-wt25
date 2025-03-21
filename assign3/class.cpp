#include "class.h"
#include <vector>

GC::GC() {
  this->threshold = DEFAULT_THRESHOLD;
  this->buf = std::vector<int>(20, 0);
}

GC::GC(int threshold) : threshold(threshold) {}

void GC::set_threshold(int threshold) {
  if (this->buf.size() >= threshold) {
    this->clear();
  }
  this->threshold = threshold;
}

int GC::get_threshold() const { return this->threshold; }

std::vector<int> GC::get_buffer() { return this->buf; }

void GC::force_clear() { this->clear(); }

void GC::clear() { this->buf.clear(); }

void GC::throw_garbage(int garbage) {
  this->buf.emplace_back(garbage);
  if (this->full()) {
    this->clear();
  }
}

bool GC::full() { return this->buf.size() >= this->threshold; }
