#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>


template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    Vector();

    ~Vector();

    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    void push_back(const T& value);
    void pop_back();
    T& at(size_t index) const;
    size_t getSize() const;
};

template <typename T>
Vector<T>::Vector() : data(nullptr), capacity(0), size(0) {}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
Vector<T>::Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    data[size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template <typename T>
T& Vector<T>::at(size_t index) const {
    if (index < size) {
        return data[index];
    }
    
    throw std::out_of_range("Index out of range");
}

template <typename T>
size_t Vector<T>::getSize() const {
    return size;
}

#endif 
