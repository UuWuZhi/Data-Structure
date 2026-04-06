# C++ `<iostream>`

`<iostream>` 提供了标准输入输出流对象，是 C++ 中最常用的头文件之一。

---

## 基本对象

- `std::cin`  —— 标准输入（键盘）
- `std::cout` —— 标准输出（屏幕）
- `std::endl` —— 输出换行并刷新缓冲区

## 输出：cout

```cpp
#include <iostream>

int main() {
    int a = 10;
    double b = 3.14;
    std::string s = "Hello";

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << s << " World!" << std::endl;
    return 0;
}
```

- << 是插入运算符
### 格式化输出

```cpp
#include <iomanip>   // 需要此头文件

double pi = 3.1415926;
std::cout << std::fixed << std::setprecision(2) << pi << std::endl;
// 输出：3.14
```

## 输入：cin

```cpp
int age;
std::string name;
std::cout << "请输入姓名和年龄：";
std::cin >> name >> age;   // 以空白字符分隔
```