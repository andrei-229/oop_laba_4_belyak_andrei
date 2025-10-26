#pragma once
#include "Point.h"
#include <memory>

template <typename T>
class Figure
{
    static_assert(std::is_scalar_v<T>, "T must be a scalar type");

public:
    virtual ~Figure() = default;

    // Чисто виртуальные методы
    virtual Point<T> geocenter() const = 0;
    virtual double area() const = 0;
    virtual void print_vertices() const = 0;

    // Виртуальные методы с реализацией по умолчанию
    virtual operator double() const { return area(); }

    virtual bool operator==(const Figure &other) const
    {
        return area() == other.area();
    }

    // Виртуальные методы для ввода/вывода
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
};

// Перегрузка глобальных операторов для Figure
template <typename T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &fig)
{
    fig.print(os);
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, Figure<T> &fig)
{
    fig.read(is);
    return is;
}