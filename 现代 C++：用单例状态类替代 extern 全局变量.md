# 现代 C++：用单例状态类替代 extern 全局变量

你当前用 `extern` 暴露全局变量、让 `a.cpp` 赋值、`b.cpp` 读取的方式，核心问题是**全局变量直接暴露，耦合高、无控制、易出bug**——现代 C++ 更优的方案是：**把这组全局变量封装成「全局状态类」（单例+Getter/Setter），** **`a.cpp`** ** 通过类接口赋值，** **`b.cpp`** ** 通过类接口读取**，彻底替代 `extern`，同时保留“全局状态共享”的核心需求。

下面给你一套可直接落地的完整方案，兼顾“全局共享”和“现代 C++ 设计规范”：

### 一、核心思路（替代 extern 的核心逻辑）

1. **封装全局变量**：把需要共享的一组变量，封装到一个「单例类」中（保证全局唯一实例）；

2. **控制访问权限**：类内用 `private` 隐藏变量，对外暴露 `const Getter`（读）和 `Setter`（写），可加校验/日志/线程安全；

3. **跨文件调用**：所有文件（`a.cpp`/`b.cpp`）通过类的静态接口访问，无需 `extern`。

### 二、完整实现代码（可直接复制使用）

#### 步骤1：定义全局状态类的头文件（`GlobalState.h`）

这是唯一需要跨文件包含的头文件，替代原来的 `extern` 声明：

```C++

#pragma once
#include <string>
#include <mutex>  // 可选：线程安全（多线程场景加）

// 全局状态类：封装所有需要共享的全局变量
class GlobalState {
public:
    // 1. 获取单例实例（全局唯一，C++11 后局部静态变量线程安全）
    static GlobalState& getInstance() {
        static GlobalState instance;
        return instance;
    }

    // 2. 读接口（Getter）：const 保证不修改内部状态，返回值/引用按需选
    // 示例：基础类型（int）—— 返回值
    int getCounter() const {
        std::lock_guard<std::mutex> lock(mtx_);  // 可选：多线程加锁
        return counter_;
    }

    // 示例：字符串（std::string）—— 返回 const 引用（避免拷贝）
    const std::string& getName() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return name_;
    }

    // 3. 写接口（Setter）：a.cpp 用这个接口赋值，可加校验逻辑
    void setCounter(int new_counter) {
        std::lock_guard<std::mutex> lock(mtx_);
        // 可选：加校验（比如禁止负数）
        if (new_counter >= 0) {
            counter_ = new_counter;
        }
    }

    void setName(const std::string& new_name) {
        std::lock_guard<std::mutex> lock(mtx_);
        // 可选：加校验（比如禁止空字符串）
        if (!new_name.empty()) {
            name_ = new_name;
        }
    }

    // 禁用拷贝/赋值：保证单例唯一性（必须加）
    GlobalState(const GlobalState&) = delete;
    GlobalState& operator=(const GlobalState&) = delete;

private:
    // 私有构造函数：外部无法创建实例，只能通过 getInstance() 获取
    GlobalState() : counter_(0), name_("default") {}

    // 需要共享的全局变量（私有化，外部无法直接访问）
    int counter_;
    std::string name_;

    // 可选：互斥锁（多线程读写时加，保证线程安全）
    mutable std::mutex mtx_;
};
```

#### 步骤2：a.cpp（赋值类）—— 通过类接口给全局状态赋值

```C++

#include "GlobalState.h"

// a.cpp 中的类：负责赋值全局状态
class DataUpdater {
public:
    void updateGlobalData(int new_counter, const std::string& new_name) {
        // 调用 Setter 赋值，无需 extern
        GlobalState::getInstance().setCounter(new_counter);
        GlobalState::getInstance().setName(new_name);
    }
};

// 测试示例
int main_a() {  // 仅示例，实际可在业务逻辑中调用
    DataUpdater updater;
    updater.updateGlobalData(100, "Guido");  // 给全局状态赋值
    return 0;
}
```

#### 步骤3：b.cpp（读取类）—— 通过类接口读取全局状态

```C++

#include "GlobalState.h"
#include <iostream>

// b.cpp 中的类：负责读取全局状态
class DataReader {
public:
    void printGlobalData() {
        // 调用 Getter 读取，无需 extern
        int counter = GlobalState::getInstance().getCounter();
        const std::string& name = GlobalState::getInstance().getName();
        
        std::cout << "Counter: " << counter << ", Name: " << name << std::endl;
    }
};

// 测试示例
int main_b() {  // 仅示例，实际可在业务逻辑中调用
    DataReader reader;
    reader.printGlobalData();  // 输出：Counter: 100, Name: Guido
    return 0;
}
```

#### 步骤4：主程序（main.cpp）—— 整合调用

```C++

#include "GlobalState.h"
#include "a.cpp"  // 实际项目中应包含 a.hpp，这里简化
#include "b.cpp"  // 实际项目中应包含 b.hpp，这里简化

int main() {
    // 1. a.cpp 的类赋值
    DataUpdater updater;
    updater.updateGlobalData(100, "Guido");

    // 2. b.cpp 的类读取
    DataReader reader;
    reader.printGlobalData();  // 输出：Counter: 100, Name: Guido

    return 0;
}
```

### 三、这个方案的核心优势（对比 extern）

|维度|extern 全局变量|单例状态类方案|
|---|---|---|
|耦合度|高（直接依赖全局变量名）|低（仅依赖类接口，变量名私有化）|
|访问控制|无（可任意修改，无校验）|可控（Setter 加校验、日志、锁）|
|线程安全|需手动加锁，易漏|类内封装锁，统一控制|
|可维护性|变量分散，难追溯修改记录|所有修改通过接口，易调试/审计|
|扩展性|差（新增变量需加 extern）|好（新增变量只需加 Getter/Setter）|
### 四、进阶优化（可选，根据项目规模）

#### 1. 多线程场景：已内置互斥锁

代码中 `mtx_` 是 `mutable` 类型（因为 `const Getter` 函数也需要加锁），多线程读写时无需额外处理，天然安全。

#### 2. 大型项目：替换为依赖注入

如果项目规模大、需要高可测试性，可把 `GlobalState` 作为依赖注入到 `DataUpdater`/`DataReader` 中（而非直接用单例）：

```C++

// a.cpp 改造：构造函数注入 GlobalState
class DataUpdater {
public:
    explicit DataUpdater(GlobalState& state) : state_(state) {}
    void updateGlobalData(int new_counter, const std::string& new_name) {
        state_.setCounter(new_counter);
        state_.setName(new_name);
    }
private:
    GlobalState& state_;
};

// 调用时注入
GlobalState& state = GlobalState::getInstance();
DataUpdater updater(state);
```

这种方式彻底解耦，单元测试时可注入模拟的 `GlobalState`，无需依赖真实全局状态。

#### 3. 配置持久化：加序列化接口

如果需要把全局状态保存到文件/数据库，可在 `GlobalState` 中加序列化/反序列化接口：

```C++

// GlobalState.h 中新增
#include <fstream>
void saveToFile(const std::string& path) {
    std::ofstream file(path);
    file << counter_ << "\n" << name_;
}

void loadFromFile(const std::string& path) {
    std::ifstream file(path);
    file >> counter_ >> name_;
}
```

### 总结

1. 核心方案：用「单例状态类+Getter/Setter」替代 `extern` 全局变量，`a.cpp` 调用 Setter 赋值，`b.cpp` 调用 Getter 读取；

2. 关键优势：低耦合、可控制、线程安全、易扩展；

3. 进阶选择：大型项目可结合「依赖注入」进一步解耦，多线程场景加内置锁，需持久化加序列化接口。

这个方案完全符合现代 C++ 的设计理念，既保留了“全局共享状态”的需求，又解决了 `extern` 全局变量的所有痛点。
> （注：文档部分内容可能由 AI 生成）