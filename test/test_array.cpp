#include <gtest/gtest.h>
#include "../include/Array.h"
#include "../include/Triangle.h"

TEST(ArrayTest, DefaultConstructor)
{
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PushBack)
{
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, PushBackMove)
{
    Array<std::string> arr;
    std::string str = "test";
    arr.push_back(std::move(str));

    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], "test");
    EXPECT_TRUE(str.empty()); // Проверяем, что исходная строка была перемещена
}

TEST(ArrayTest, Erase)
{
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    arr.erase(1); // Удаляем второй элемент

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, CopyConstructor)
{
    Array<int> original;
    original.push_back(1);
    original.push_back(2);

    Array<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], original[0]);
    EXPECT_EQ(copy[1], original[1]);
}

TEST(ArrayTest, MoveConstructor)
{
    Array<int> original;
    original.push_back(1);
    original.push_back(2);

    Array<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(original.size(), 0); // Исходный массив должен быть пуст
}

TEST(ArrayTest, AssignmentOperator)
{
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);

    Array<int> arr2;
    arr2 = arr1;

    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, MoveAssignmentOperator)
{
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);

    Array<int> arr2;
    arr2 = std::move(arr1);

    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, OutOfBoundsAccess)
{
    Array<int> arr;
    arr.push_back(1);

    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr[100], std::out_of_range);
}

TEST(ArrayTest, OutOfBoundsErase)
{
    Array<int> arr;
    arr.push_back(1);

    EXPECT_THROW(arr.erase(1), std::out_of_range);
    EXPECT_THROW(arr.erase(100), std::out_of_range);
}

TEST(ArrayTest, ResizeAndMoveSemantics)
{
    Array<int> arr;

    // Добавляем много элементов для вызова resize
    for (int i = 0; i < 100; ++i)
    {
        arr.push_back(i);
    }

    EXPECT_EQ(arr.size(), 100);
    for (int i = 0; i < 100; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(ArrayTest, WithFigures)
{
    Array<std::shared_ptr<Figure<double>>> figures;

    std::vector<Point<double>> tri_points = {{0, 0}, {2, 0}, {0, 2}};
    auto triangle = std::make_shared<Triangle<double>>(tri_points);
    figures.push_back(triangle);

    EXPECT_EQ(figures.size(), 1);
    EXPECT_DOUBLE_EQ(figures[0]->area(), 2.0);
}