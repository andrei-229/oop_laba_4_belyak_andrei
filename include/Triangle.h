#pragma once
#include "Figure.h"
#include <vector>
#include <cmath>

template <typename T>
class Triangle : public Figure<T>
{
    std::unique_ptr<Point<T>> vertices[3];

public:
    Triangle()
    {
        for (int i = 0; i < 3; ++i)
            vertices[i] = std::make_unique<Point<T>>();
    }

    Triangle(const std::vector<Point<T>> &points)
    {
        if (points.size() != 3)
            throw std::invalid_argument("Triangle requires exactly 3 points");
        for (int i = 0; i < 3; ++i)
            vertices[i] = std::make_unique<Point<T>>(points[i]);
    }

    Triangle(const Triangle &other)
    {
        for (int i = 0; i < 3; ++i)
        {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Triangle &operator=(const Triangle &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < 3; ++i)
            {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            }
        }
        return *this;
    }

    Triangle(Triangle &&other) noexcept
    {
        for (int i = 0; i < 3; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Triangle &operator=(Triangle &&other) noexcept
    {
        if (this != &other)
        {
            for (int i = 0; i < 3; ++i)
            {
                vertices[i] = std::move(other.vertices[i]);
            }
        }
        return *this;
    }

    Point<T> geocenter() const override
    {
        T x = 0, y = 0;
        for (const auto &v : vertices)
        {
            x += v->x;
            y += v->y;
        }
        return Point<T>(x / 3, y / 3);
    }

    double area() const override
    {
        return std::abs(
                   (vertices[1]->x - vertices[0]->x) * (vertices[2]->y - vertices[0]->y) -
                   (vertices[2]->x - vertices[0]->x) * (vertices[1]->y - vertices[0]->y)) /
               2.0;
    }

    void print_vertices() const override
    {
        for (int i = 0; i < 3; ++i)
            std::cout << *vertices[i] << " ";
        std::cout << std::endl;
    }

    void print(std::ostream &os) const override
    {
        os << "Triangle vertices: ";
        for (int i = 0; i < 3; ++i)
            os << *vertices[i] << " ";
        os << "| Geocenter: " << geocenter() << " | Area: " << area();
    }

    void read(std::istream &is) override
    {
        std::cout << "Enter 3 points for Triangle (x y for each point):" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "Point " << (i + 1) << ": ";
            is >> *vertices[i];
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Triangle<T> &tri)
    {
        tri.print(os);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Triangle<T> &tri)
    {
        tri.read(is);
        return is;
    }
};