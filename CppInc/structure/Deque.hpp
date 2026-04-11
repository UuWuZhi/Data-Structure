#pragma once

#include <iostream>

namespace ds {

template<class T>
class Deque
{
    T* data;
    size_t capacity;
    size_t front;
    size_t rear;
public:
    explicit Deque(const size_t cap) : capacity(cap + 1), front(0), rear(0)
    {
        data = new T[capacity];
    }
    ~Deque()
    {
        delete[] data;
    }
    [[nodiscard]] bool empty() const
    {
        return front == rear;
    }
    [[nodiscard]] bool full() const
    {
        return front == (rear + 1) % capacity;
    }
    bool insert_front(const T& val)
    {
        if (full()) return false;
        front = (front - 1 + capacity) % capacity;
        data[front] = val;
        return true;

    }
    bool insert_rear(const T& val)
    {
        if (full()) return false;
        data[rear] = val;
        rear = (rear + 1) % capacity;
        return true;
    }
    bool delete_front()
    {
        if (empty()) return false;
        front = (front + 1) % capacity;
        return true;
    }
    bool delete_rear()
    {
        if (empty()) return false;
        rear = (rear - 1 + capacity) % capacity;
        return true;
    }
    bool print()
    {
        if (empty()) return false;
        for (size_t i = front; i != rear; i = (i + 1) % capacity)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
        return true;
    }
};

} // namespace ds
