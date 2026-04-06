# C++ 类

类是 C++ 面向对象编程的核心。它允许你将数据（成员变量）和操作这些数据的函数（成员方法）封装在一起。

---

## 定义一个简单的类

```cpp
// 定义
class Student {
public:
    // 成员变量
    std::string name;
    int age;

    // 成员函数
    void introduce() {
        std::cout << "我是" << name << "，今年" << age << "岁。" << std::endl;
    }
};


// 创建和使用对象
#include <iostream>
#include <string>

int main() {
    Student stu;            // 创建对象
    stu.name = "小明";
    stu.age = 18;
    stu.introduce();        // 调用成员函数
    return 0;
}
```

## 访问控制

- public：任何地方都可以访问
- private：只有类内部可以访问（默认）
- protected：类内部和派生类可以访问

## 构造函数与析构函数

```cpp
class Student {
public:
    Student(std::string n, int a) {  // 构造函数
        name = n;
        age = a;
    }
    ~Student() {                     // 析构函数
        std::cout << name << "被销毁了" << std::endl;
    }
private:
    std::string name;
    int age;
};
```

构造函数在对象创建时自动调用，析构函数在对象销毁时自动调用。

---





