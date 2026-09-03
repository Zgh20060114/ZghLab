#include <cmath>
#include <cstdio>
#include <cstring>
#include <cxxabi.h>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

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
  template <class T> T getDistance() { return std::pow(getX(), 2); }

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

void print() { std::cout << '\n'; }
template <class T, class... Args> void print(T t, Args... args) {
  std::cout << t << " ";
  print(args...);
}
// template <class T1, class T2> T1 add(T1 t1, T2 t2) { return t1 + t2; }
template <class T> T add() { return 0; }
template <class T1, class T2, class... Args> T1 add(T2 t, Args... args) {
  return t + add<T1>(args...);
}

template <class T1, class T2 = int, class T3, int ratio = 10>
T2 multiply(T1 t1, T3 t2) {
  return t1 * t2 * ratio;
}

template <>
const char *add<const char *, const char *>(const char *c1, const char *c2) {}

template <typename T> std::string type_name() {
  // using TR = std::decay_t<T>; // 先获取 decay 后的类型
  // 获取编译器内部的修饰名 (mangled name)
  const std::string mangled_name = typeid(T).name();
  int status = 0;
  // 使用 abi::__cxa_demangle 将其转换为人类可读的格式
  std::unique_ptr<char, decltype(&std::free)> demangled_name(
      abi::__cxa_demangle(mangled_name.c_str(), nullptr, nullptr, &status),
      std::free);
  return (status == 0) ? demangled_name.get() : mangled_name;
}
template <typename T> std::string_view type_name_pretty() {
#if defined(__clang__) || defined(__GNUC__)
  // 返回 "std::string_view type_name_pretty() [T = const int&]"
  std::string_view pretty = __PRETTY_FUNCTION__;
  auto start = pretty.find("T = ") + 4;
  auto end = pretty.find(';', start);
  return pretty.substr(start, end - start);
#else
  return "unsupported";
#endif
}

template <class T> class Vector {
public:
  template <class InputIt> Vector(InputIt first, InputIt last, T t);

  template <class U>
  Vector(const Vector<U> &other); // 允许 vector<int> v = vector<double>(...)
};

class FileCloser {
  void operator()(FILE *f) const {
    if (f)
      fclose(f);
  }
};
class Session : public std::enable_shared_from_this<Session> {
public:
  void start() { auto sft = shared_from_this(); }
};
int main(int argc, char *argv[]) {

  // std::shared_ptr<FILE> file{fopen("data.txt", "r"), FileCloser{}};
  // Point *po = new Point();
  // std::shared_ptr<Point> sp{po};
  // std::shared_ptr<Point> sp1{po};
  // std::cout << multiply<double>(15.2, 2.2) << '\n';
  // print(1, 2, 3, 4);
  // std::cout << add<double>(1.1, 2.1, 3.1, 4.1) << '\n';

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
  // Circle circle{};
  // Shape *shape = &circle;
  // Pen *pen = &circle;
  // std::cout << &circle << '\n';
  // std::cout << shape << '\n';
  // std::cout << pen << '\n';

  // std::unique_ptr<Shape> shape = std::make_unique<Circle>();
  // shape->draw();
  // int a{};
  // int &&c = a + 1;
  // const int &b = a;
  // Point *p{};
  // std::string e = "hello";
  // std::string &&f = std::move(e);
  // std::string &g = e;
  // std::cout << g << '\n';
  // f = std::string{"world"};
  // std::cout << e << '\n';
  // std::cout << typeid(a).name() << '\n';
  // std::cout << typeid(p).name() << '\n';
  // std::cout << type_name_pretty<decltype(p)>() << '\n';
  // auto sp{std::make_shared<int>()};
  // if (sp) {
  //   std::cout << sp.get() << '\n';
  // }
  // std::weak_ptr<int> wp{sp};
  // if (auto s_wp = wp.lock()) {
  //   std::cout << s_wp.get() << '\n';
  // }
  // std::unique_ptr<FILE> up_file{fopen("data.txt", "r")};
  // auto vec_uptr = std::vector<std::unique_ptr<int>>{};
  // vec_uptr.push_back(uptr);
  std::vector<int> v_a{1, 2};
  std::list<int> l_a{1, 2};
  std::cout << v_a.max_size() << "\n";
  std::list<int>::iterator it{l_a.begin()};
  it = l_a.erase(it);
  std::cout << *it << "\n";
  return 0;
}
