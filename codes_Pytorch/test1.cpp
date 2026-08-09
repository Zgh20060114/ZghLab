#include <cstring>
#include <iostream>
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
  Point(int x) {}

private:
  int _x = 0;
  int _y = 0;
};
class Point3D : public Point {
public:
  Point3D(int z) : _z(z) {}

private:
  int _z = 0;
};
int main(int argc, char *argv[]) {

  // std::vector<int> vec{2, 3};
  // std::cout << vec.size() << "\n";
  // std::cout << vec.capacity() << "\n";
  // std::cout << strlen(nullptr) << "\n"; // 段错误
  // auto pai = std::make_pair(1, 2);

  std::cout << sizeof(std::string) << "\n";
  std::string str{"aaa"};
  std::cout << str.size() << "\n";
  std::cout << str.capacity() << "\n";
  return 0;
}
