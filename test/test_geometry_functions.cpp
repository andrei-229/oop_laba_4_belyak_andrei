#include <gtest/gtest.h>
#include "../include/Array.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include "../src/geometry_functions.cpp"

// Объявляем функции, которые определены в geometry_functions.cpp
// template <typename T>
// double calculate_total_area(const Array<std::shared_ptr<Figure<T>>> &figures);

// template <typename T>
// void print_all_figures(const Array<std::shared_ptr<Figure<T>>> &figures);

// Явное инстанцирование для тестов
// template double calculate_total_area<double>(const Array<std::shared_ptr<Figure<double>>> &);
// template void print_all_figures<double>(const Array<std::shared_ptr<Figure<double>>> &);

TEST(GeometryFunctionsTest, CalculateTotalArea)
{
    Array<std::shared_ptr<Figure<double>>> figures;

    // Добавляем треугольник площадью 2.0
    std::vector<Point<double>> tri_points = {{0, 0}, {2, 0}, {0, 2}};
    figures.push_back(std::make_shared<Triangle<double>>(tri_points));

    // Добавляем еще один треугольник площадью 6.0
    std::vector<Point<double>> tri_points2 = {{0, 0}, {4, 0}, {0, 3}};
    figures.push_back(std::make_shared<Triangle<double>>(tri_points2));

    double total_area = calculate_total_area(figures);
    EXPECT_DOUBLE_EQ(total_area, 8.0); // 2.0 + 6.0
}

TEST(GeometryFunctionsTest, CalculateTotalAreaEmpty)
{
    Array<std::shared_ptr<Figure<double>>> figures;

    double total_area = calculate_total_area(figures);
    EXPECT_DOUBLE_EQ(total_area, 0.0);
}

TEST(GeometryFunctionsTest, CalculateTotalAreaMixedFigures)
{
    Array<std::shared_ptr<Figure<double>>> figures;

    // Треугольник
    std::vector<Point<double>> tri_points = {{0, 0}, {3, 0}, {0, 4}};
    figures.push_back(std::make_shared<Triangle<double>>(tri_points));

    // Шестиугольник (простейший для теста)
    std::vector<Point<double>> hex_points(6, Point<double>(1, 0));
    figures.push_back(std::make_shared<Hexagon<double>>(hex_points));

    double total_area = calculate_total_area(figures);
    // Площадь треугольника = 6.0, шестиугольника = 0 (вырожденный)
    EXPECT_DOUBLE_EQ(total_area, 6.0);
}

TEST(GeometryFunctionsTest, PrintAllFiguresOutput)
{
    Array<std::shared_ptr<Figure<double>>> figures;

    std::vector<Point<double>> tri_points = {{0, 0}, {2, 0}, {0, 2}};
    figures.push_back(std::make_shared<Triangle<double>>(tri_points));

    // Перенаправляем вывод
    testing::internal::CaptureStdout();
    print_all_figures(figures);
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем, что вывод содержит ожидаемые строки
    EXPECT_TRUE(output.find("Triangle") != std::string::npos);
    EXPECT_TRUE(output.find("Area") != std::string::npos);
}