#include <iostream>

template<class T>
class Stack
{
    T* data;
    size_t capacity;
    size_t count;
public:
    explicit Stack(const size_t cap) : data(nullptr), capacity(cap), count(0)
    {
        data = new T[capacity];
    }
    ~Stack()
    {
        delete[] data;
    }
    [[nodiscard]] bool empty() const
    {
        return count == 0;
    }
    [[nodiscard]] bool full() const
    {
        return count == capacity;
    }
    bool push(const T& val)
    {
        if (full()) return false;
        data[count] = val;
        ++count;
        return true;
    }
    bool pop()
    {
        if (empty()) return false;
        --count;
        return true;
    }
    [[nodiscard]] T top() const
    {
        if (empty()) return T{};
        return data[count - 1];
    }
    bool print()
    {
        if (empty()) return false;
        for (int i = count - 1; i >= 0; --i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
        return true;
    }
};