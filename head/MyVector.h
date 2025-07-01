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

    //删除元素
    void removeAt(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        // 调用析构函数（如果是复杂对象）
        data[index].~T();

        // 将后面的元素前移
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        --size;
    }

    /**
     * 二分查找
     * @param target 要查找的目标值
     * @param getKey 获取元素键值的函数
     * @param comp 比较函数，返回 true 表示第一个参数小于第二个参数
     * @return 返回目标值的索引，如果未找到则返回 -1
     */
    template<typename Key, typename Comparator>
    int binarySearch(Key target, Key (*getKey)(const T&), Comparator comp) const {
        size_t left = 0;
        size_t right = size - 1;

        while (left <= right) {
            size_t mid = left + (right - left) / 2;
            Key current = getKey(data[mid]);

            if (!comp(current, target) && !comp(target, current)) {
                return static_cast<int>(mid); // 相等
            } else if (comp(current, target)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1; // 未找到
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