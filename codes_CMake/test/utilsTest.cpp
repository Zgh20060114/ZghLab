#include "utils.hpp"
#include <iostream>

int main() {
  int result = add(2, 3);
  if (result == 5) {
    std::cout << "Test passed!" << std::endl;
    return 0;
  } else {
    std::cout << "Test failed! Expected 5, got " << result << std::endl;
    return 1;
  }
}
