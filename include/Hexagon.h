#pragma once
#include "Figure.h"
#include <vector>
#include <cmath>
#include <stdexcept>

template <Scalar T>
class Hexagon : public Figure<T>
{
    std::unique_ptr<Point<T>> vertices[6];

public:
    Hexagon()
    {
        for (int i = 0; i < 6; ++i)
            vertices[i] = std::make_unique<Point<T>>();
    }

    Hexagon(const std::vector<Point<T>> &points)
    {
        if (points.size() != 6)
            throw std::invalid_argument("Hexagon requires exactly 6 points");
        for (int i = 0; i < 6; ++i)
            vertices[i] = std::make_unique<Point<T>>(points[i]);
    }

    Hexagon(const Hexagon &other) : Hexagon()
    {
        for (int i = 0; i < 6; ++i)
        {
            *vertices[i] = *other.vertices[i];
        }
    }

    Hexagon &operator=(const Hexagon &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < 6; ++i)
            {
                *vertices[i] = *other.vertices[i];
            }
        }
        return *this;
    }

    Hexagon(Hexagon &&other) noexcept
    {
        for (int i = 0; i < 6; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Hexagon &operator=(Hexagon &&other) noexcept
    {
        if (this != &other)
        {
            for (int i = 0; i < 6; ++i)
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
            if (v)
            {
                x += v->x;
                y += v->y;
            }
        }
        return Point<T>(x / 6, y / 6);
    }

    double area() const override
    {
        double area = 0;
        for (int i = 0; i < 6; ++i)
        {
            int j = (i + 1) % 6;
            if (vertices[i] && vertices[j])
            {
                area += vertices[i]->x * vertices[j]->y - vertices[j]->x * vertices[i]->y;
            }
        }
        return std::abs(area) / 2.0;
    }

    void print_vertices() const override
    {
        for (int i = 0; i < 6; ++i)
        {
            if (vertices[i])
            {
                std::cout << *vertices[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    void print(std::ostream &os) const override
    {
        os << "Hexagon vertices: ";
        for (int i = 0; i < 6; ++i)
        {
            if (vertices[i])
            {
                os << *vertices[i] << " ";
            }
        }
        os << "| Geocenter: " << geocenter() << " | Area: " << area();
    }

    void read(std::istream &is) override
    {
        std::cout << "Enter 6 points for Hexagon (x y for each point):" << std::endl;
        for (int i = 0; i < 6; ++i)
        {
            std::cout << "Point " << (i + 1) << ": ";
            if (!vertices[i])
            {
                vertices[i] = std::make_unique<Point<T>>();
            }
            is >> *vertices[i];
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Hexagon<T> &hex)
    {
        hex.print(os);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Hexagon<T> &hex)
    {
        hex.read(is);
        return is;
    }
};