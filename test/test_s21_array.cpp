#include <gtest/gtest.h>

#include "../src/s21_array/s21_array.h"  // правильный путь из папки tests

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  EXPECT_FALSE(arr.empty());

  // Проверяем, что все элементы инициализированы (для int это 0)
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, AtMethod) {
  s21::array<int, 3> arr = {10, 20, 30};

  EXPECT_EQ(arr.at(0), 10);
  EXPECT_EQ(arr.at(1), 20);
  EXPECT_EQ(arr.at(2), 30);

  // Проверяем исключение при выходе за границы
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(ArrayTest, FrontBack) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 4);
}

TEST(ArrayTest, Iterators) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  // Проверка begin/end
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);

  // Проверка range-based for
  sum = 0;
  for (const auto& val : arr) {
    sum += val;
  }
  EXPECT_EQ(sum, 15);

  // Проверка const итераторов
  const s21::array<int, 3> carr = {10, 20, 30};
  EXPECT_EQ(*carr.begin(), 10);
  EXPECT_EQ(*carr.cbegin(), 10);
}

TEST(ArrayTest, FillMethod) {
  s21::array<int, 4> arr;
  arr.fill(42);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}

TEST(ArrayTest, SwapMethod) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};

  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<std::string, 2> arr1 = {"hello", "world"};
  s21::array<std::string, 2> arr2(arr1);

  EXPECT_EQ(arr2[0], "hello");
  EXPECT_EQ(arr2[1], "world");

  // Изменение оригинала не должно влиять на копию
  arr1[0] = "changed";
  EXPECT_EQ(arr2[0], "hello");  // копия не изменилась
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<std::string, 2> arr1 = {"hello", "world"};
  s21::array<std::string, 2> arr2(std::move(arr1));

  EXPECT_EQ(arr2[0], "hello");
  EXPECT_EQ(arr2[1], "world");
}

TEST(ArrayTest, AssignmentOperators) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};

  // Копирующее присваивание
  arr2 = arr1;
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);

  // Перемещающее присваивание
  s21::array<int, 3> arr3 = {7, 8, 9};
  arr2 = std::move(arr3);
  EXPECT_EQ(arr2[0], 7);
  EXPECT_EQ(arr2[1], 8);
  EXPECT_EQ(arr2[2], 9);
}

TEST(ArrayTest, DataMethod) {
  s21::array<int, 3> arr = {100, 200, 300};
  int* ptr = arr.data();

  EXPECT_EQ(ptr[0], 100);
  EXPECT_EQ(ptr[1], 200);
  EXPECT_EQ(ptr[2], 300);

  // Можно изменять через указатель
  ptr[1] = 999;
  EXPECT_EQ(arr[1], 999);
}

TEST(ArrayTest, SizeMethods) {
  s21::array<int, 0> arr0;
  EXPECT_TRUE(arr0.empty());
  EXPECT_EQ(arr0.size(), 0);
  EXPECT_EQ(arr0.max_size(), 0);

  s21::array<int, 10> arr10;
  EXPECT_FALSE(arr10.empty());
  EXPECT_EQ(arr10.size(), 10);
  EXPECT_EQ(arr10.max_size(), 10);
}

// Тест для проверки работы с пользовательскими типами
struct Point {
  int x, y;
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

TEST(ArrayTest, CustomType) {
  s21::array<Point, 2> points = {Point{1, 2}, Point{3, 4}};
  EXPECT_EQ(points[0].x, 1);
  EXPECT_EQ(points[0].y, 2);
  EXPECT_EQ(points[1].x, 3);
  EXPECT_EQ(points[1].y, 4);
}
