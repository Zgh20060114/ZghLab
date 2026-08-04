- c风格回调
```cpp 
#include <iostream>

// 1. 定义函数指针类型别名
typedef void (*Callback)(int);

// 2. 接受函数指针的函数
void processData(int value, Callback callback) {
    if (callback) {
        callback(value);
    }
}

// 3. 具体的回调函数
void printResult(int result) {
    std::cout << "Result: " << result << std::endl;
}

int main() {
    // 4. 传递普通函数作为回调
    processData(10, printResult);
    return 0;
}
```
- 现代cpp风格回调
```cpp 
#include <iostream>
#include <functional>

// 1. 使用 using 定义回调类型别名，提高可读性
using Callback = std::function<void(int)>;

// 2. 接受回调的函数
void processData(int value, Callback callback) {
    std::cout << "Processing value: " << value << std::endl;
    if (callback) { // 调用前务必检查是否为空
        callback(value * 2);
    }
}

int main() {
    // 3. 传递 Lambda 表达式作为回调
    processData(10, [](int result) {
        std::cout << "Callback result: " << result << std::endl;
    });

    return 0;
}
```
