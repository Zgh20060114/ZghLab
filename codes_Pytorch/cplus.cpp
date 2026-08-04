#include <cmath>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
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
  int a{4};
};

class C {
public:
  void cPrint() const { std::cout << "C::cPrint()" << std::endl; }
};

class A {
private:
  C *c_ptr = new C();

public:
  C *operator->() { return c_ptr; } // 返回 C*
};

class B {
private:
  A *a_ptr = new A();

public:
  A *operator->() { return a_ptr; } // 返回 A&
};

using INT = int;
int main() {
  B b;
  b->cPrint(); // ✅ 可以运行
  // 过程：b-> → 调用 B::operator->() 返回 A& → 编译器自动取地址得到 A* → 调用
  // A::operator->() 返回 C* → 调用 cPrint()
  return 0;
}

// int main(int argc, char *argv[]) {
//   // auto vec = std::vector<int>{1, 2, 3};
//   // std::cout << vec << std::endl;
//   // auto p1_ptr = std::make_unique<Point>(1, 2);
//   // auto p1_ptr = std::make_unique<Point>();
//   // auto p = Point{1, 2};
//   // auto p1_vec = std::vector<Point>{p};
//   // std::vector<Point> p2_vec{Point{3, 4}};
//   // static auto stc_ptr = std::make_unique<Point>(1, 2);
//   // Point p{};
//   // // std::cout << sizeof(int) << std::endl;
//   // std::vector<int> vec{1, 2};
//   // auto vec1 = std::vector<int>{1, 2, 3};
//   // auto a = int{};
//   // std::cin >> a;
//   // std::cout << a << std::endl;
//   // if (!std::cin.good()) {
//   //   std::cin.clear(); // 恢复流的状态
//   //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
//   //                   '\n'); // 清除缓冲区的内容
//   // }
//   // std::cout << &(std::cin) << std::endl;
//   // auto file_path = std::filesystem::path{"./DQNexample.py"};
//   // auto ifs = std::ifstream{file_path};
//   // auto str_line = std::string{};
//   // while (std::getline(ifs, str_line, '\n')) {
//   //   std::cout << str_line << "\n";
//   // }
//   // int n1{0};
//   // int n2{0};
//   // std::cin >> n1 >> n2;
//   // std::cout << n1 << " " << n2 << std::endl;
//   // std::istringstream iss{str_line};
//   // std::cout << std::pow(2, 3) << std::endl;
//   // std::cout << sizeof p;
//   Point p1{1, 2};
//   std::cout << p1.get() << std::endl;
//
//   return 0;
// }
