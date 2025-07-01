#pragma once
#include <cstddef>   // 提供 size_t 定义


template<typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    template<typename T>
    MyVector<T>::MyVector(size_t initialCapacity)
        : capacity(initialCapacity), size(0), hashTableSize(initialCapacity * 2) {
        data = new T[capacity];
        hashValues = new size_t[hashTableSize];
        indices = new size_t[hashTableSize];

        // 初始化哈希表为空（用特殊值标记未使用）
        for (size_t i = 0; i < hashTableSize; ++i) {
            hashValues[i] = 0; // 0 表示空位（假设 0 不是合法哈希值）
            indices[i] = static_cast<size_t>(-1); // -1 表示无效索引
        }
    }

    template<typename T>
    MyVector<T>::~MyVector() {
        delete[] data;
        delete[] hashValues;
        delete[] indices;
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
    template<typename Key, typename GetKey,typename Comparator>
    int binarySearch(Key target, GetKey getkey, Comparator comp) const {
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

    // 自定义哈希函数
    template<typename T>
    size_t MyVector<T>::customHash(const std::string& str) const {
        size_t hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c); // hash * 33 + c
        }
        return hash;
    }

    template<typename T>
    void MyVector<T>::rebuildHashTable(std::function<std::string(const T&)> getKey) {
        // 清空旧哈希表
        for (size_t i = 0; i < hashTableSize; ++i) {
            hashValues[i] = 0;
            indices[i] = static_cast<size_t>(-1);
        }

        for (size_t i = 0; i < size; ++i) {
            size_t hashValue = customHash(getKey(data[i]));

            // 线性探测解决冲突
            size_t pos = hashValue % hashTableSize;
            while (hashValues[pos] != 0 && hashValues[pos] != hashValue) {
                pos = (pos + 1) % hashTableSize; // 线性探测
            }

            hashValues[pos] = hashValue;
            indices[pos] = i;
        }
    }   
};