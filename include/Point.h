#pragma once
#include <type_traits>
#include <concepts>
#include <iostream>


template <typename T>
concept Scalar = std::is_scalar_v<T>;


template <Scalar T>
class Point
{
    static_assert(std::is_scalar_v<T>, "T must be a scalar type");

public:
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}


    friend std::ostream &operator<<(std::ostream &os, const Point<T> &p)
    {
        return os << "(" << p.x << ", " << p.y << ")";
    }


    friend std::istream &operator>>(std::istream &is, Point<T> &p)
    {
        return is >> p.x >> p.y;
    }


    Point<T> operator+(const Point<T> &other) const
    {
        return Point<T>(x + other.x, y + other.y);
    }

    Point<T> operator/(T divisor) const
    {
        return Point<T>(x / divisor, y / divisor);
    }
};