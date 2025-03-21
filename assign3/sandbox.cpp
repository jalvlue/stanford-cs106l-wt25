/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include "class.h"
#include <iostream>
#include <ostream>

void sandbox() {
  auto my_gc = GC{};
  auto orig_threshold = my_gc.get_threshold();
  std::cout << "original threshold: " << orig_threshold << std::endl;

  my_gc.set_threshold(5);
  auto new_threshold = my_gc.get_threshold();
  std::cout << "new threshold: " << new_threshold << std::endl;

  my_gc.throw_garbage(1);
  my_gc.throw_garbage(2);
  my_gc.throw_garbage(3);
  my_gc.throw_garbage(4);
  my_gc.throw_garbage(5);
  my_gc.throw_garbage(6);
  auto buf = my_gc.get_buffer();
  for (const auto &item : buf) {
    std::cout << item << " ";
  }
  std::endl(std::cout);
}
