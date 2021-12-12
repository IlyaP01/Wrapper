/**
 * @file
 * @brief Main file
 * @authors Pavlov Ilya
 *
 * File contains entry point and some tests
 */

#include "engine/engine.h"
#include <iostream>

class Summator {
public:
  int sum(int a, int b) {
    return a + b;
  }
};

class Subtractor {
public:
  int subtract(int a, int b) {
    return a - b;
  }
};

class Abs {
public:
  int abs(int a) {
    return a < 0 ? -a : a;
  }
};

int main() {
  Summator s;
  Subtractor sb;
  Abs abs;
 
  Wrapper wrapper1(&s, &Summator::sum, { {"arg1", 0}, {"arg2", 0} });
  Wrapper wrapper2(&sb, &Subtractor::subtract, { {"arg1", 0}, {"arg2", 0} });
  Wrapper wrapper3(&abs, &Abs::abs, { {"arg", 0} });

  Engine engine;
  engine.register_command("sum", &wrapper1);
  engine.register_command("diff", &wrapper2);
  engine.register_command("abs", &wrapper3);

  std::cout << engine.execute("sum", { {"arg1", 3}, {"arg2", 7}}) << std::endl;
  std::cout << engine.execute("sum", { {"arg1", 3}}) << std::endl;
  std::cout << engine.execute("diff", { {"arg2", 3}, {"arg1", 4}}) << std::endl;
  std::cout << engine.execute("abs", {}) << std::endl;
  std::cout << engine.execute("abs", { {"arg", -5} }) << std::endl;

  return 0;
}