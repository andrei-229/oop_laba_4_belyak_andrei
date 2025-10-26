#pragma once
#include "Figure.h"
#include <vector>
#include <cmath>

template <Scalar T>
class Octagon : public Figure<T>
{
    std::unique_ptr<Point<T>> vertices[8];

public:
    Octagon()
    {
        for (int i = 0; i < 8; ++i)
            vertices[i] = std::make_unique<Point<T>>();
    }

    Octagon(const std::vector<Point<T>> &points)
    {
        if (points.size() != 8)
            throw std::invalid_argument("Octagon requires exactly 8 points");
        for (int i = 0; i < 8; ++i)
            vertices[i] = std::make_unique<Point<T>>(points[i]);
    }

    Octagon(const Octagon &other)
    {
        for (int i = 0; i < 8; ++i)
        {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Octagon &operator=(const Octagon &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < 8; ++i)
            {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            }
        }
        return *this;
    }

    // Конструктор перемещения
    Octagon(Octagon &&other) noexcept
    {
        for (int i = 0; i < 8; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    // Оператор присваивания перемещением
    Octagon &operator=(Octagon &&other) noexcept
    {
        if (this != &other)
        {
            for (int i = 0; i < 8; ++i)
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
        return Point<T>(x / 8, y / 8);
    }

    double area() const override
    {
        double area = 0;
        for (int i = 0; i < 8; ++i)
        {
            int j = (i + 1) % 8;
            area += vertices[i]->x * vertices[j]->y - vertices[j]->x * vertices[i]->y;
        }
        return std::abs(area) / 2.0;
    }

    void print_vertices() const override
    {
        for (int i = 0; i < 8; ++i)
            std::cout << *vertices[i] << " ";
        std::cout << std::endl;
    }

    void print(std::ostream &os) const override
    {
        os << "Octagon vertices: ";
        for (int i = 0; i < 8; ++i)
            os << *vertices[i] << " ";
        os << "| Geocenter: " << geocenter() << " | Area: " << area();
    }

    void read(std::istream &is) override
    {
        std::cout << "Enter 8 points for Octagon (x y for each point):" << std::endl;
        for (int i = 0; i < 8; ++i)
        {
            std::cout << "Point " << (i + 1) << ": ";
            is >> *vertices[i];
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Octagon<T> &oct)
    {
        oct.print(os);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Octagon<T> &oct)
    {
        oct.read(is);
        return is;
    }
};