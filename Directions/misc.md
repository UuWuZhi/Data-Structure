# C++ 杂项

---

## 引用

引用是变量的**别名**，一旦绑定就不能更改。它常用于函数参数传递，避免拷贝开销。

```cpp
int a = 10;
int &ref = a;   // ref 是 a 的引用
ref = 20;       // 相当于 a = 20

// 函数中使用引用（传递实参本身）
void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}
```

引用与指针的区别：**引用必须初始化，不能为空，不能改变指向**。

---

## new 和 delete

new 在堆上动态分配内存，delete 释放内存。需要手动管理，避免内存泄漏。

```cpp
// 单个对象
int *p = new int(42);   // 分配并初始化
std::cout << *p << std::endl;
delete p;               // 释放内存

// 数组
int *arr = new int[10]; // 分配10个int
arr[0] = 100;
delete[] arr;           // 释放数组必须用 delete[]
```

结合引用与动态内存

```cpp
int *ptr = new int(5);
int &ref = *ptr;        // 引用指向动态对象
ref = 10;               // 修改动态对象
delete ptr;             // 释放后 ref 变为悬空引用，不可再使用
```