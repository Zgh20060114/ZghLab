#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Point {
public:
  // Point() = default;
  Point(int x = 0, int y = 0) : _x(x), _y(y) {
    std::cout << "调用构造函数" << std::endl;
  }
  Point(const Point &rhs) { std::cout << "调用拷贝构造函数" << std::endl; }
  Point &operator=(const Point &rhs) {
    std::cout << "调用拷贝赋值函数" << std::endl;
    return *this;
  }
  Point(Point &&rhs) { std::cout << "调用移动构造函数" << std::endl; }
  Point &operator=(Point &&rhs) {
    std::cout << "调用移动赋值函数" << std::endl;
    return *this;
  }

private:
  const int _x = 0;
  const int _y = 0;
  auto vect = std::vector<int>{};
};

int main(int argc, char *argv[]) {
  // auto vec = std::vector<int>{1, 2, 3};
  // std::cout << vec << std::endl;
  // auto p1_ptr = std::make_unique<Point>(1, 2);
  // auto p1_ptr = std::make_unique<Point>();
  // auto p = Point{1, 2};
  // auto p1_vec = std::vector<Point>{p};
  // std::vector<Point> p2_vec{Point{3, 4}};
  static auto stc_ptr = std::make_unique<Point>(1, 2);
  Point p;
  Point p2{11};
  // std::cout << sizeof(int) << std::endl;
  std::string str{"hello"};
  std::vector<int> vec{1, 2};
  auto vec1 = std::vector<int>{1, 2, 3};
  return 0;
}
