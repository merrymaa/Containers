#include <gtest/gtest.h>

#include "../src/s21_vector/s21_vector.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor) {
  s21::vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  EXPECT_FALSE(v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, CopyAssignment) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = v1;
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(VectorTest, MoveAssignment) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, AtMethod) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, AccessOperators) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  v[1] = 10;
  EXPECT_EQ(v[1], 10);
}

TEST(VectorTest, FrontBackMethods) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, DataMethod) {
  s21::vector<int> v = {1, 2, 3};
  int* data = v.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[2], 3);
}

TEST(VectorTest, Iterators) {
  s21::vector<int> v = {1, 2, 3};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

TEST(VectorTest, EmptySizeCapacity) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);

  v.push_back(1);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 1);
  EXPECT_GE(v.capacity(), 1);
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(VectorTest, Reserve) {
  s21::vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_EQ(v.size(), 0);

  v.push_back(1);
  v.push_back(2);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_EQ(v.size(), 2);
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> v;
  v.reserve(10);
  v.push_back(1);
  v.push_back(2);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_EQ(v.size(), 2);

  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 2);
  EXPECT_EQ(v.size(), 2);
}

TEST(VectorTest, Clear) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Insert) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert(v.begin() + 1, 10);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 10);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
  EXPECT_EQ(*it, 10);

  it = v.insert(v.begin(), 0);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(*it, 0);
}

TEST(VectorTest, Erase) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin() + 2);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);

  v.erase(v.begin());
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, PushBack) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 1);

  v.push_back(2);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[1], 2);

  for (int i = 3; i <= 10; ++i) {
    v.push_back(i);
  }
  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v[9], 10);
}

TEST(VectorTest, PopBack) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);

  v.pop_back();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.back(), 1);

  v.pop_back();
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Swap) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6, 7};

  v1.swap(v2);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, LargeVector) {
  s21::vector<int> v;
  const int N = 1000;
  for (int i = 0; i < N; ++i) {
    v.push_back(i);
  }
  EXPECT_EQ(v.size(), N);
  EXPECT_GE(v.capacity(), N);
  for (int i = 0; i < N; ++i) {
    EXPECT_EQ(v[i], i);
  }
}

TEST(VectorTest, SelfAssignment) {
  s21::vector<int> v = {1, 2, 3};
  v = v;
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, ReserveWithSmallerCapacity) {
  s21::vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);

  v.reserve(5);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, InsertAtBeginning) {
  s21::vector<int> v = {2, 3, 4};
  v.insert(v.begin(), 1);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, InsertAtEnd) {
  s21::vector<int> v = {1, 2, 3};
  v.insert(v.end(), 4);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, InsertMultipleWithReallocation) {
  s21::vector<int> v;
  v.reserve(2);
  v.push_back(1);
  v.push_back(2);

  EXPECT_EQ(v.capacity(), 2);
  v.insert(v.begin() + 1, 99);
  EXPECT_GT(v.capacity(), 2);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 99);
  EXPECT_EQ(v[2], 2);
}

TEST(VectorTest, EraseLastElement) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.end() - 1);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, EraseAllElements) {
  s21::vector<int> v = {1, 2, 3};
  v.erase(v.begin());
  v.erase(v.begin());
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, PushBackWithReallocation) {
  s21::vector<int> v;
  v.reserve(2);

  v.push_back(1);
  v.push_back(2);
  EXPECT_EQ(v.capacity(), 2);

  v.push_back(3);
  EXPECT_GT(v.capacity(), 2);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBackOnEmptyVector) {
  s21::vector<int> v;
  v.pop_back();
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SwapEmptyWithNonEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};

  v1.swap(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, SwapSelf) {
  s21::vector<int> v = {1, 2, 3};
  v.swap(v);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, MoveConstructorFromEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v1.empty());
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, CopyAssignmentToSelf) {
  s21::vector<int> v = {1, 2, 3};
  s21::vector<int>& ref = v;
  v = ref;
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, ConstMethods) {
  const s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
  EXPECT_FALSE(v.empty());

  const int* data = v.data();
  EXPECT_EQ(data[1], 2);

  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

TEST(VectorTest, DifferentTypes) {
  s21::vector<double> v_double = {1.1, 2.2, 3.3};
  EXPECT_EQ(v_double.size(), 3);
  EXPECT_DOUBLE_EQ(v_double[0], 1.1);

  s21::vector<std::string> v_string = {"hello", "world"};
  EXPECT_EQ(v_string.size(), 2);
  EXPECT_EQ(v_string[0], "hello");
  EXPECT_EQ(v_string[1], "world");

  v_string.push_back("test");
  EXPECT_EQ(v_string.size(), 3);
  EXPECT_EQ(v_string[2], "test");
}

TEST(VectorTest, ShrinkToFitEmptyVector) {
  s21::vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);

  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, ShrinkToFitAlreadyFitted) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.capacity(), 3);

  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

TEST(VectorTest, ClearPreservesCapacity) {
  s21::vector<int> v;
  v.reserve(10);
  v.push_back(1);
  v.push_back(2);

  size_t old_capacity = v.capacity();
  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), old_capacity);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, IteratorArithmetic) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  auto it1 = v.begin();
  auto it2 = v.end();

  EXPECT_EQ(it2 - it1, 5);
  EXPECT_EQ(*(it1 + 2), 3);
  EXPECT_EQ(*(it2 - 1), 5);

  it1 += 2;
  EXPECT_EQ(*it1, 3);

  it1 -= 1;
  EXPECT_EQ(*it1, 2);
}

TEST(VectorTest, IteratorComparison) {
  s21::vector<int> v = {1, 2, 3};

  auto begin = v.begin();
  auto end = v.end();

  EXPECT_TRUE(begin != end);
  EXPECT_FALSE(begin == end);

  auto begin2 = v.begin();
  EXPECT_TRUE(begin == begin2);
}

TEST(VectorTest, FrontBackOnEmptyVector) {
  s21::vector<int> v;

  EXPECT_THROW(v.front(), std::out_of_range);
  EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(VectorTest, ReserveZero) {
  s21::vector<int> v;
  v.reserve(0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, MaxSizeForDifferentTypes) {
  s21::vector<char> v_char;
  s21::vector<int> v_int;
  s21::vector<double> v_double;

  EXPECT_GT(v_char.max_size(), 0);
  EXPECT_GT(v_int.max_size(), 0);
  EXPECT_GT(v_double.max_size(), 0);

  EXPECT_GT(v_char.max_size(), v_double.max_size());
}

TEST(VectorTest, InitializerListEmpty) {
  s21::vector<int> v = {};
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, InsertIntoEmptyVector) {
  s21::vector<int> v;
  v.insert(v.begin(), 42);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 42);
}

TEST(VectorTest, EraseFromEmptyVector) {
  s21::vector<int> v;
  EXPECT_THROW(v.erase(v.begin()), std::out_of_range);
}

TEST(VectorTest, ShrinkToFitAfterClear) {
  s21::vector<int> v;
  v.reserve(10);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 10);

  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, MoveAssignmentFromEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};

  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, DataOnEmptyVector) {
  s21::vector<int> v;
  EXPECT_EQ(v.data(), nullptr);

  const s21::vector<int> cv;
  EXPECT_EQ(cv.data(), nullptr);
}

TEST(VectorTest, BeginEndOnEmptyVector) {
  s21::vector<int> v;
  EXPECT_EQ(v.begin(), v.end());

  const s21::vector<int> cv;
  EXPECT_EQ(cv.begin(), cv.end());
}

TEST(VectorTest, InitializerListWithDuplicates) {
  s21::vector<int> v = {1, 1, 2, 2, 3, 3};
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[5], 3);
}

TEST(VectorTest, CopyAndModifyOriginal) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = v1;

  v1[0] = 99;
  EXPECT_EQ(v1[0], 99);
  EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, VectorOfVectors) {
  s21::vector<s21::vector<int>> v;
  v.push_back({1, 2, 3});
  v.push_back({4, 5});
  v.push_back({6});

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0].size(), 3);
  EXPECT_EQ(v[1].size(), 2);
  EXPECT_EQ(v[2].size(), 1);
  EXPECT_EQ(v[0][2], 3);
  EXPECT_EQ(v[1][1], 5);
  EXPECT_EQ(v[2][0], 6);
}

TEST(VectorTest, StressTest) {
  s21::vector<int> v;
  const int N = 10000;

  for (int i = 0; i < N; ++i) {
    v.push_back(i * 2);
  }

  EXPECT_EQ(v.size(), N);

  for (int i = 0; i < N; ++i) {
    EXPECT_EQ(v[i], i * 2);
  }

  for (int i = 0; i < N / 2; ++i) {
    v.pop_back();
  }

  EXPECT_EQ(v.size(), N / 2);

  for (int i = 0; i < N / 2; ++i) {
    v.push_back(i * 3);
  }

  EXPECT_EQ(v.size(), N);
}

TEST(VectorTest, InsertManyEmpty) {
  s21::vector<int> v;
  v.insert_many(v.begin(), 1, 2, 3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyAtBeginning) {
  s21::vector<int> v = {4, 5, 6};
  v.insert_many(v.begin(), 1, 2, 3);

  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, InsertManyAtMiddle) {
  s21::vector<int> v = {1, 2, 5, 6};
  v.insert_many(v.begin() + 2, 3, 4);

  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, InsertManyAtEnd) {
  s21::vector<int> v = {1, 2, 3};
  v.insert_many(v.end(), 4, 5, 6);

  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, InsertManySingleElement) {
  s21::vector<int> v = {1, 3, 4};
  auto it = v.insert_many(v.begin() + 1, 2);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, InsertManyNoElements) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert_many(v.begin() + 1);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(it, v.begin() + 1);
}

TEST(VectorTest, InsertManyWithReallocation) {
  s21::vector<int> v;
  v.reserve(3);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.capacity(), 3);
  v.insert_many(v.begin() + 1, 99, 100);

  EXPECT_GT(v.capacity(), 3);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 99);
  EXPECT_EQ(v[2], 100);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);
}

TEST(VectorTest, InsertManyBackEmpty) {
  s21::vector<int> v;
  v.insert_many_back(1, 2, 3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyBackNonEmpty) {
  s21::vector<int> v = {1, 2, 3};
  v.insert_many_back(4, 5, 6);

  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, InsertManyBackSingleElement) {
  s21::vector<int> v = {1, 2};
  v.insert_many_back(3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyBackNoElements) {
  s21::vector<int> v = {1, 2, 3};
  v.insert_many_back();

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyWithMoveSemantics) {
  s21::vector<std::string> v = {"a", "d", "e"};
  std::string s1 = "b";
  std::string s2 = "c";

  v.insert_many(v.begin() + 1, std::move(s1), std::move(s2));

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], "a");
  EXPECT_EQ(v[1], "b");
  EXPECT_EQ(v[2], "c");
  EXPECT_EQ(v[3], "d");
  EXPECT_EQ(v[4], "e");
  EXPECT_TRUE(s1.empty());  // s1 был перемещен
  EXPECT_TRUE(s2.empty());  // s2 был перемещен
}

TEST(VectorTest, InsertManyWithDifferentTypes) {
  s21::vector<double> v = {1.1, 4.4};
  v.insert_many(v.begin() + 1, 2.2, 3.3);

  EXPECT_EQ(v.size(), 4);
  EXPECT_DOUBLE_EQ(v[0], 1.1);
  EXPECT_DOUBLE_EQ(v[1], 2.2);
  EXPECT_DOUBLE_EQ(v[2], 3.3);
  EXPECT_DOUBLE_EQ(v[3], 4.4);
}

TEST(VectorTest, InsertManyComplexObjects) {
  s21::vector<s21::vector<int>> v;
  v.push_back({1, 2});
  v.push_back({5, 6});

  v.insert_many(v.begin() + 1, s21::vector<int>{3, 4});

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0].size(), 2);
  EXPECT_EQ(v[1].size(), 2);
  EXPECT_EQ(v[2].size(), 2);
  EXPECT_EQ(v[0][1], 2);
  EXPECT_EQ(v[1][0], 3);
  EXPECT_EQ(v[2][1], 6);
}

TEST(VectorTest, InsertManyIteratorValidity) {
  s21::vector<int> v = {1, 2, 3};
  auto it_before = v.begin();
  auto it_insert = v.begin() + 1;

  int value_before = *it_before;

  v.insert_many(it_insert, 99, 100);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], value_before);
  EXPECT_EQ(v[1], 99);
  EXPECT_EQ(v[2], 100);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);
}

TEST(VectorTest, InsertManyLargeNumberOfElements) {
  s21::vector<int> v = {100, 200};
  std::vector<int> to_insert;
  for (int i = 1; i <= 50; ++i) {
    to_insert.push_back(i);
  }

  v.insert_many(v.begin() + 1, to_insert[0], to_insert[1], to_insert[2],
                to_insert[3], to_insert[4]);

  EXPECT_EQ(v.size(), 7);
  EXPECT_EQ(v[0], 100);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
  EXPECT_EQ(v[4], 4);
  EXPECT_EQ(v[5], 5);
  EXPECT_EQ(v[6], 200);
}

TEST(VectorTest, InsertManyReturnIterator) {
  s21::vector<int> v = {1, 4, 5};
  auto it = v.insert_many(v.begin() + 1, 2, 3);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(*(it + 1), 3);

  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorTest, InsertManyAtInvalidPosition) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_THROW(v.insert_many(v.begin() + 10, 4, 5), std::out_of_range);
  EXPECT_THROW(v.insert_many(v.end() + 1, 4, 5), std::out_of_range);
}

TEST(VectorTest, InsertManyBackWithReallocation) {
  s21::vector<int> v;
  v.reserve(3);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.capacity(), 3);
  v.insert_many_back(4, 5, 6);

  EXPECT_GT(v.capacity(), 3);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, InsertManyChaining) {
  s21::vector<int> v = {1};
  v.insert_many(v.end(), 2, 3);
  v.insert_many(v.end(), 4, 5);
  v.insert_many(v.end(), 6);

  EXPECT_EQ(v.size(), 6);
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(v[i], i + 1);
  }
}

TEST(VectorTest, InsertManyWithConstReferences) {
  s21::vector<int> v = {1, 5};
  const int a = 2, b = 3, c = 4;

  v.insert_many(v.begin() + 1, a, b, c);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], a);
  EXPECT_EQ(v[2], b);
  EXPECT_EQ(v[3], c);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, InsertManyMixedTypesConvertible) {
  s21::vector<double> v = {1.5, 4.5};

  v.insert_many(v.begin() + 1, 2, 3.5);

  EXPECT_EQ(v.size(), 4);
  EXPECT_DOUBLE_EQ(v[0], 1.5);
  EXPECT_DOUBLE_EQ(v[1], 2.0);
  EXPECT_DOUBLE_EQ(v[2], 3.5);
  EXPECT_DOUBLE_EQ(v[3], 4.5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}