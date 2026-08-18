#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
//
// class C {
// public:
//   void cPrint() const { std::cout << "C::cPrint()" << std::endl; }
// };
//
// class A {
// private:
//   C *c_ptr = new C();
//
// public:
//   C *operator->() { return c_ptr; } // 返回 C*，即原生指针
//   C &operator*() { return *c_ptr; } // 返回 C*，即原生指针
//   ~A() { delete c_ptr; }
// };
//
// class B {
// private:
//   A *a_ptr = new A();
//
// public:
//   A *operator->() { return a_ptr; } // 返回 A*，即原生指针
//   ~B() { delete a_ptr; }
// };
//
// int main() {
//   // B b;         // B 的类外对象 b
//   // b->cPrint(); // ✅ 可以运行！输出: C::cPrint()
//   A a;
//   a->cPrint();
//   (*a).cPrint();
//   return 0;
// }

// class Line {
// public:
//   int a;
//   void print() { std::cout << b << std::endl; }
//   class Point {
//   public:
//     int b;
//   };
// };
class Point {
public:
  Point() {}
  Point(int x, int y) : _x(x), _y(y) {}
  int getX() const { return _x; }
  int getY() const { return _y; }
  virtual void print() {}

  Point &operator=(const Point &rhs) {
    _x = rhs._x;
    _y = rhs._y;
    std::cout << "调用的是Point的拷贝赋值运算符函数." << '\n';
    return *this;
  }

private:
  int _x{0};
  int _y{0};
};

class Point3D : public Point {
public:
  Point3D() {}
  Point3D(int x, int y, int z) : Point(x, y), _z(z) {}
  void printPoint3D() {
    std::cout << getX() << "," << getY() << "," << _z << "," << '\n';
  }

private:
  int _z{0};
};

class Shape {
public:
  virtual void draw() const { std::cout << "draw shape" << '\n'; }
  virtual ~Shape() = default;

private:
  std::unique_ptr<std::string> ptr_str{std::make_unique<std::string>("Shape")};
};
class Pen {
public:
  virtual void draw() const { std::cout << "draw pen" << '\n'; }
  virtual ~Pen() = default;
};
class Circle : public Pen, public Shape {
private:
  void draw() const override { std::cout << "draw circle" << '\n'; };
  std::unique_ptr<std::string> ptr_str{std::make_unique<std::string>("Circle")};
};

template <class T1, class T2> T1 add(T1 t1, T2 t2) { return t1 + t2; }
template <class T1, class T2 = int, class T3, int ratio = 10>
T2 multiply(T1 t1, T3 t2) {
  return t1 * t2 * ratio;
}

template <>
const char *add<const char *, const char *>(const char *c1, const char *c2) {}
int main(int argc, char *argv[]) {

  std::cout << multiply<double>(15.2, 2.2) << '\n';

  // std::vector<int> vec{2, 3};
  // std::cout << vec.size() << "\n";
  // std::cout << vec.capacity() << "\n";
  // std::cout << strlen(nullptr) << "\n"; // 段错误
  // auto pai = std::make_pair(1, 2);

  // std::cout << sizeof(std::string) << "\n";
  // std::string str{"aaa"};
  // std::cout << str.size() << "\n";
  // std::cout << str.capacity() << "\n";

  // Point3D d1{};
  // Point b1{};
  // Point *base = &d1;
  // // Point b1{1, 1};
  // // Point *base = &b1;
  // auto derive = dynamic_cast<Point3D *>(base);
  // if (derive == nullptr) {
  //   std::cout << "没有转换" << '\n';
  // } else {
  //   derive->printPoint3D();
  // }
  //
  // Point3D d2{};
  // Point b2{};
  // b2 = d2;
  Circle circle{};
  Shape *shape = &circle;
  Pen *pen = &circle;
  std::cout << &circle << '\n';
  std::cout << shape << '\n';
  std::cout << pen << '\n';

  // std::unique_ptr<Shape> shape = std::make_unique<Circle>();
  // shape->draw();
  return 0;
}
