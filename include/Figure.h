#pragma once
#include "Point.h"
#include <memory>

template <typename T>
class Figure
{
    static_assert(std::is_scalar_v<T>, "T must be a scalar type");

public:
    virtual ~Figure() = default;

    virtual Point<T> geocenter() const = 0;
    virtual double area() const = 0;
    virtual void print_vertices() const = 0;

    virtual operator double() const { return area(); }

    virtual bool operator==(const Figure &other) const
    {
        return area() == other.area();
    }

    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
};

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