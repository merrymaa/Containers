#include <gtest/gtest.h>

#include <set>
#include <vector>

#include "../src/s21_multiset/s21_multiset.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3};
  EXPECT_EQ(ms.size(), 6);
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1 = {1, 2, 2, 3};
  s21::multiset<int> ms2(ms1);

  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_EQ(ms2.count(2), 2);
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));

  EXPECT_TRUE(ms1.empty());
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
}

TEST(MultisetTest, AssignmentOperators) {
  s21::multiset<int> ms1 = {1, 2, 2, 3};
  s21::multiset<int> ms2;

  ms2 = ms1;
  EXPECT_EQ(ms2.size(), 4);
  EXPECT_EQ(ms2.count(2), 2);

  s21::multiset<int> ms3;
  ms3 = std::move(ms2);
  EXPECT_EQ(ms3.size(), 4);
  EXPECT_TRUE(ms2.empty());
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> ms;
  auto result = ms.insert(10);

  EXPECT_EQ(*result, 10);
  EXPECT_EQ(ms.size(), 1);

  ms.insert(10);
  EXPECT_EQ(ms.size(), 2);
  EXPECT_EQ(ms.count(10), 2);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3};

  auto it = ms.find(2);
  ms.erase(it);

  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(ms.count(2), 1);

  ms.erase(ms.find(3));
  EXPECT_EQ(ms.count(3), 2);
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5};
  ms.clear();

  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> ms1 = {1, 2, 2};
  s21::multiset<int> ms2 = {3, 4, 4, 5};

  ms1.swap(ms2);

  EXPECT_EQ(ms1.size(), 4);
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_EQ(ms1.count(4), 2);
  EXPECT_EQ(ms2.count(2), 2);
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {2, 3, 4};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 6);
  EXPECT_EQ(ms2.size(), 0);
  EXPECT_EQ(ms1.count(2), 2);
  EXPECT_EQ(ms1.count(3), 2);
}

TEST(MultisetTest, Find) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3};

  auto it1 = ms.find(2);
  EXPECT_NE(it1, ms.end());
  EXPECT_EQ(*it1, 2);

  auto it2 = ms.find(99);
  EXPECT_EQ(it2, ms.end());
}

TEST(MultisetTest, Contains) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(5));
}

TEST(MultisetTest, Count) {
  s21::multiset<int> ms = {1, 2, 2, 3, 3, 3, 3};

  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 4);
  EXPECT_EQ(ms.count(5), 0);
}

TEST(MultisetTest, LowerBound) {
  s21::multiset<int> ms = {10, 20, 20, 30, 40};

  auto it = ms.lower_bound(20);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 20);

  auto it2 = ms.lower_bound(25);
  EXPECT_EQ(*it2, 30);
}

TEST(MultisetTest, UpperBound) {
  s21::multiset<int> ms = {10, 20, 20, 30, 40};

  auto it = ms.upper_bound(20);
  EXPECT_EQ(*it, 30);

  auto it2 = ms.upper_bound(35);
  EXPECT_EQ(*it2, 40);
}

TEST(MultisetTest, EqualRange) {
  s21::multiset<int> ms = {10, 20, 20, 20, 30};

  auto range = ms.equal_range(20);

  size_t count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(*it, 20);
    count++;
  }
  EXPECT_EQ(count, 3);
}

TEST(MultisetTest, Iterators) {
  s21::multiset<int> ms = {3, 1, 2, 2, 4};
  std::vector<int> expected = {1, 2, 2, 3, 4};
  std::vector<int> actual;

  for (auto it = ms.begin(); it != ms.end(); ++it) {
    actual.push_back(*it);
  }

  EXPECT_EQ(actual, expected);
}

TEST(MultisetTest, ReverseIteration) {
  s21::multiset<int> ms = {1, 2, 3, 4};
  std::vector<int> expected = {4, 3, 2, 1};
  std::vector<int> actual;

  auto it = ms.end();
  --it;  // Переходим к последнему элементу

  while (it != ms.begin()) {
    actual.push_back(*it);
    --it;
  }
  actual.push_back(*it);  // Первый элемент

  EXPECT_EQ(actual, expected);
}

TEST(MultisetTest, InsertMany) {
  s21::multiset<int> ms;

  auto results = ms.insert_many(5, 3, 5, 1, 3, 3);

  EXPECT_EQ(ms.size(), 6);
  EXPECT_EQ(ms.count(3), 3);
  EXPECT_EQ(ms.count(5), 2);
  EXPECT_EQ(results.size(), 6);
}

TEST(MultisetTest, MaxSize) {
  s21::multiset<int> ms;
  EXPECT_GT(ms.max_size(), 0);
}

TEST(MultisetTest, StringMultiset) {
  s21::multiset<std::string> ms = {"apple", "banana", "apple", "cherry"};

  EXPECT_EQ(ms.size(), 4);
  EXPECT_EQ(ms.count("apple"), 2);
  EXPECT_TRUE(ms.contains("banana"));

  ms.insert("banana");
  EXPECT_EQ(ms.count("banana"), 2);
}

TEST(MultisetTest, LargeMultiset) {
  s21::multiset<int> ms;
  const int N = 1000;

  for (int i = 0; i < N; ++i) {
    ms.insert(i % 100);  // Много дубликатов
  }

  EXPECT_EQ(ms.size(), N);
  EXPECT_TRUE(ms.contains(0));
  EXPECT_TRUE(ms.contains(99));

  // Проверяем сортировку
  int prev = -1;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    EXPECT_GE(*it, prev);
    prev = *it;
  }
}
