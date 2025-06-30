#pragma once
#include <cstddef>   // 提供 size_t 定义


template<typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    // 构造函数
    explicit MyVector(size_t initialCapacity = 4)
        : capacity(initialCapacity), size(0) {
        data = new T[capacity];
    }

    // 析构函数
    ~MyVector() {
        delete[] data;
    }

    // 添加元素
    void add(const T& value) {
        push_back(value); // 或者直接实现扩容逻辑
    }

    void push_back(const T& value) {
        if (size == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    // 下标访问
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // 获取大小
    size_t getSize() const {
        return size;
    }
};