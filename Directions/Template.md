# C++ 模板

模板让你编写**通用代码**，不依赖于具体数据类型。它分为**函数模板**和**类模板**。

---

## 函数模板

```cpp
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int x = 5, y = 10;
    std::cout << max(x, y) << std::endl;    // 实例化为 int

    double p = 3.14, q = 2.71;
    std::cout << max(p, q) << std::endl;    // 实例化为 double
    return 0;
}
```

## 类模板 

```cpp
template <typename T>
class Box {
private:
    T content;
public:
    void set(T val) { content = val; }
    T get() { return content; }
};

int main() {
    Box<int> intBox;        // 指定类型为 int
    intBox.set(123);
    
    Box<std::string> strBox;
    strBox.set("Hello");
    
    std::cout << intBox.get() << std::endl;   // 123
    std::cout << strBox.get() << std::endl;   // Hello
    return 0;
}
```

## 多个模板参数

```cpp
template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;
    Pair(T1 a, T2 b) : first(a), second(b) {}
};

Pair<int, double> p(10, 3.14);
```

模板代码通常全部写在头文件中，因为编译器需要看到完整定义才能实例化。
