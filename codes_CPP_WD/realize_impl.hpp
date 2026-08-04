#pragma once
#include <iostream>
#include <string>

class RealizeImpl {
public:
  RealizeImpl(int val = 0) : m_value(val), m_name("default") {}
  void setValue(int val) { m_value = val; }
  int getValue() const { return m_value; }
  void print() const {
    std::cout << "Value: " << m_value << ", Name: " << m_name << std::endl;
  }

private:
  int m_value;
  std::string m_name;
};
