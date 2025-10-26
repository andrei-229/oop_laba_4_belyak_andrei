#include <gtest/gtest.h>
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include <cmath>

TEST(FigureTest, TriangleArea)
{
    std::vector<Point<double>> points = {
        {0.0, 0.0},
        {4.0, 0.0},
        {0.0, 3.0}};
    Triangle<double> triangle(points);

    EXPECT_DOUBLE_EQ(triangle.area(), 6.0);
}

TEST(FigureTest, TriangleGeocenter)
{
    std::vector<Point<double>> points = {
        {0.0, 0.0},
        {6.0, 0.0},
        {0.0, 6.0}};
    Triangle<double> triangle(points);
    Point<double> center = triangle.geocenter();

    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(FigureTest, HexagonArea)
{
    // Правильный шестиугольник со стороной 1
    std::vector<Point<double>> points;
    for (int i = 0; i < 6; ++i)
    {
        double angle = i * M_PI / 3.0;
        points.emplace_back(std::cos(angle), std::sin(angle));
    }
    Hexagon<double> hexagon(points);

    double expected_area = (3.0 * std::sqrt(3.0)) / 2.0; // Площадь правильного шестиугольника
    EXPECT_NEAR(hexagon.area(), expected_area, 1e-10);
}

TEST(FigureTest, HexagonGeocenter)
{
    std::vector<Point<double>> points = {
        {1.0, 0.0}, {0.5, 0.866}, {-0.5, 0.866}, {-1.0, 0.0}, {-0.5, -0.866}, {0.5, -0.866}};
    Hexagon<double> hexagon(points);
    Point<double> center = hexagon.geocenter();

    EXPECT_NEAR(center.x, 0.0, 1e-10);
    EXPECT_NEAR(center.y, 0.0, 1e-10);
}

TEST(FigureTest, OctagonArea)
{
    // Правильный восьмиугольник
    std::vector<Point<double>> points;
    for (int i = 0; i < 8; ++i)
    {
        double angle = i * M_PI / 4.0;
        points.emplace_back(std::cos(angle), std::sin(angle));
    }
    Octagon<double> octagon(points);

    double side = std::sqrt(2.0 - std::sqrt(2.0)); // Сторона правильного восьмиугольника
    double expected_area = 2.0 * (1.0 + std::sqrt(2.0)) * side * side;
    EXPECT_NEAR(octagon.area(), expected_area, 1e-10);
}

TEST(FigureTest, DoubleConversion)
{
    std::vector<Point<double>> points = {
        {0.0, 0.0},
        {2.0, 0.0},
        {0.0, 2.0}};
    Triangle<double> triangle(points);

    double area = static_cast<double>(triangle);
    EXPECT_DOUBLE_EQ(area, 2.0);
}

TEST(FigureTest, EqualityOperator)
{
    std::vector<Point<double>> points1 = {{0, 0}, {2, 0}, {0, 2}};
    std::vector<Point<double>> points2 = {{0, 0}, {2, 0}, {0, 2}};

    Triangle<double> tri1(points1);
    Triangle<double> tri2(points2);

    EXPECT_TRUE(tri1 == tri2);
}

TEST(FigureTest, CopyAndMove)
{
    std::vector<Point<double>> points = {{0, 0}, {4, 0}, {0, 3}};
    Triangle<double> original(points);

    // Тест копирования
    Triangle<double> copy(original);
    EXPECT_DOUBLE_EQ(original.area(), copy.area());

    // Тест перемещения
    Triangle<double> moved(std::move(copy));
    EXPECT_DOUBLE_EQ(original.area(), moved.area());
}