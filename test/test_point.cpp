#include <gtest/gtest.h>
#include "../include/Point.h"

TEST(PointTest, DefaultConstructor)
{
    Point<int> p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor)
{
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 4.2);
}

TEST(PointTest, OutputOperator)
{
    Point<int> p(10, 20);
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(10, 20)");
}

TEST(PointTest, InputOperator)
{
    Point<int> p;
    std::istringstream iss("15 25");
    iss >> p;
    EXPECT_EQ(p.x, 15);
    EXPECT_EQ(p.y, 25);
}

TEST(PointTest, ArithmeticOperations)
{
    Point<double> p1(2.0, 3.0);
    Point<double> p2(1.0, 1.0);

    Point<double> sum = p1 + p2;
    EXPECT_DOUBLE_EQ(sum.x, 3.0);
    EXPECT_DOUBLE_EQ(sum.y, 4.0);

    Point<double> div = p1 / 2.0;
    EXPECT_DOUBLE_EQ(div.x, 1.0);
    EXPECT_DOUBLE_EQ(div.y, 1.5);
}

TEST(PointTest, ScalarTypeCheck)
{
    // Должно компилироваться для скалярных типов
    Point<int> p1;
    Point<double> p2;
    Point<float> p3;

    // Не должно компилироваться для нескалярных типов (тестируется статически)
    EXPECT_TRUE((std::is_scalar_v<int>));
    EXPECT_TRUE((std::is_scalar_v<double>));
}