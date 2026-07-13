#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  // auto vec = std::vector<int>{1, 2, 3};
  // std::cout << vec << std::endl;
  std::cout << sizeof(int) << std::endl;
  return 0;
}

class Point {
public:
  Point(int x, int y) : _x(x), _y(y) {}
  // Point(int x, int y){
  //   _x = x;
  //   _y = y;
  // }

private:
  const int _x;
  const int _y;
};
