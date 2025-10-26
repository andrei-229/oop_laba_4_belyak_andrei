#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>

template <typename T>
class Array
{
    std::unique_ptr<T[]> data;
    size_t _size = 0;
    size_t _capacity = 0;

    void resize(size_t new_capacity)
    {
        // Используем new вместо make_shared для массивов
        std::unique_ptr<T[]> new_data(new T[new_capacity]);
        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i] = std::move(data[i]); // Используем перемещение
        }
        data = std::move(new_data);
        _capacity = new_capacity;
    }

public:
    Array() = default;

    Array(const Array &other) : _size(other._size), _capacity(other._capacity)
    {
        data = std::unique_ptr<T[]>(new T[_capacity]);
        for (size_t i = 0; i < _size; ++i)
        {
            data[i] = other.data[i]; // Копируем элементы
        }
    }

    Array(Array &&other) noexcept
        : data(std::move(other.data)), _size(other._size), _capacity(other._capacity)
    {
        other._size = 0;
        other._capacity = 0;
    }

    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            _size = other._size;
            _capacity = other._capacity;
            data = std::unique_ptr<T[]>(new T[_capacity]);
            for (size_t i = 0; i < _size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array &operator=(Array &&other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
            _size = other._size;
            _capacity = other._capacity;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    void push_back(const T &value)
    {
        if (_size == _capacity)
            resize(_capacity ? _capacity * 2 : 1);
        data[_size++] = value; // Копирование
    }

    void push_back(T &&value)
    {
        if (_size == _capacity)
            resize(_capacity ? _capacity * 2 : 1);
        data[_size++] = std::move(value); // Перемещение
    }

    void erase(size_t index)
    {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        for (size_t i = index; i < _size - 1; ++i)
        {
            data[i] = std::move(data[i + 1]); // Используем перемещение
        }
        --_size;
    }

    T &operator[](size_t index)
    {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    void clear()
    {
        data.reset();
        _size = 0;
        _capacity = 0;
    }

    // Перегрузка оператора вывода для массива
    friend std::ostream &operator<<(std::ostream &os, const Array<T> &arr)
    {
        os << "Array[" << arr._size << "]:\n";
        for (size_t i = 0; i < arr._size; ++i)
        {
            os << "  [" << i << "] " << arr.data[i] << "\n";
        }
        return os;
    }
    size_t length(){
        return _size;
    }
};