#pragma once
#include <type_traits>
#include <concepts>
#include <iostream>

// Замена concept на традиционный SFINAE
template <typename T>
concept Scalar = std::is_scalar_v<T>;

// Используем concept в шаблоне
template <Scalar T>
class Point
{
    static_assert(std::is_scalar_v<T>, "T must be a scalar type");

public:
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    // Перегрузка оператора вывода
    friend std::ostream &operator<<(std::ostream &os, const Point<T> &p)
    {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    // Перегрузка оператора ввода
    friend std::istream &operator>>(std::istream &is, Point<T> &p)
    {
        return is >> p.x >> p.y;
    }

    // Операторы для арифметических операций
    Point<T> operator+(const Point<T> &other) const
    {
        return Point<T>(x + other.x, y + other.y);
    }

    Point<T> operator/(T divisor) const
    {
        return Point<T>(x / divisor, y / divisor);
    }
};