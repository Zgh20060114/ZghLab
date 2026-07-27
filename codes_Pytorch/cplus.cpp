#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
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
  auto p2 = Point{11};
  // std::cout << sizeof(int) << std::endl;
  std::vector<int> vec{1, 2};
  auto vec1 = std::vector<int>{1, 2, 3};
  // auto a = int{};
  // std::cin >> a;
  // std::cout << a << std::endl;
  // if (!std::cin.good()) {
  //   std::cin.clear(); // 恢复流的状态
  //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
  //                   '\n'); // 清除缓冲区的内容
  // }
  // std::cout << &(std::cin) << std::endl;
  auto file_path = std::filesystem::path{"./DQNexample.py"};
  auto ifs = std::ifstream{file_path};
  auto str_line = std::string{};
  while (std::getline(ifs, str_line, '\n')) {
    std::cout << str_line << "\n";
  }
  return 0;
}
