#include <iostream>
template<class T>
class CircularQueue
{
    T* data;
    int capacity;
    int front;
    int rear;
public:
    explicit CircularQueue(const int cap) : capacity(cap + 1), front(0), rear(0)
    {
        data = new T[capacity];
    }
    ~CircularQueue()
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
    [[nodiscard]] T top() const
    {
        if (empty()) return -1;
        return data[front];
    }
    [[nodiscard]] int size() const
    {
        return (rear + capacity - front) % capacity;
    }
    bool push(const T& val)
    {
        if (full()) return false;
        data[rear] = val;
        rear = (rear + 1) % capacity;
        return true;
    }
    int pop()
    {
        if (empty()) return -1;
        const int t = data[front];
        front = (front + 1) % capacity;
        return t;
    }
    void print()
    {
        for (int i = front; i != rear; i = (i + 1) % capacity)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};