#include <gtest/gtest.h>

#include "../src/s21_set/s21_set.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3, 4, 5};
  EXPECT_EQ(s.size(), 5);
  EXPECT_FALSE(s.empty());
}

TEST(SetTest, InitializerListConstructorWithDuplicates) {
  s21::set<int> s = {1, 1, 2, 2, 3, 3};
  EXPECT_EQ(s.size(), 3);
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.size(), 3);
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));

  EXPECT_EQ(s1.size(), 0);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
}

TEST(SetTest, MoveAssignment) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2;

  s2 = std::move(s1);

  EXPECT_EQ(s1.size(), 0);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
}

TEST(SetTest, Empty) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());

  s.insert(1);
  EXPECT_FALSE(s.empty());

  s.clear();
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, Size) {
  s21::set<int> s;
  EXPECT_EQ(s.size(), 0);

  s.insert(1);
  EXPECT_EQ(s.size(), 1);

  s.insert(2);
  EXPECT_EQ(s.size(), 2);

  s.insert(2);
  EXPECT_EQ(s.size(), 2);

  s.erase(s.find(1));
  EXPECT_EQ(s.size(), 1);
}

TEST(SetTest, MaxSize) {
  s21::set<int> s;
  EXPECT_GT(s.max_size(), 0);
}

TEST(SetTest, Clear) {
  s21::set<int> s = {1, 2, 3, 4, 5};
  EXPECT_EQ(s.size(), 5);

  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, Insert) {
  s21::set<int> s;

  auto result1 = s.insert(10);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(*result1.first, 10);
  EXPECT_EQ(s.size(), 1);

  auto result2 = s.insert(20);
  EXPECT_TRUE(result2.second);
  EXPECT_EQ(*result2.first, 20);
  EXPECT_EQ(s.size(), 2);

  auto result3 = s.insert(10);
  EXPECT_FALSE(result3.second);
  EXPECT_EQ(*result3.first, 10);
  EXPECT_EQ(s.size(), 2);
}

TEST(SetTest, InsertMaintainsSortedOrder) {
  s21::set<int> s;

  s.insert(30);
  s.insert(10);
  s.insert(20);
  s.insert(5);
  s.insert(25);

  auto it = s.begin();
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 25);
  ++it;
  EXPECT_EQ(*it, 30);
}

TEST(SetTest, Erase) {
  s21::set<int> s = {1, 2, 3, 4, 5};

  EXPECT_EQ(s.size(), 5);

  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));

  it = s.find(1);
  s.erase(it);
  EXPECT_EQ(s.size(), 3);
  EXPECT_FALSE(s.contains(1));

  it = s.find(5);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(5));
}

TEST(SetTest, EraseInvalidIterator) {
  s21::set<int> s = {1, 2, 3};

  s.erase(s.end());
  EXPECT_EQ(s.size(), 3);
}

TEST(SetTest, Swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6, 7};

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 4);

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 4);
  EXPECT_EQ(s2.size(), 3);

  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s1.contains(7));

  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {3, 4, 5, 6};

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 4);

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 6);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));

  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeWithDuplicates) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {2, 3, 4};

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 4);
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, MergeSelf) {
  s21::set<int> s = {1, 2, 3};

  s.merge(s);

  EXPECT_EQ(s.size(), 3);
}

TEST(SetTest, Find) {
  s21::set<int> s = {10, 20, 30, 40, 50};

  auto it1 = s.find(20);
  EXPECT_NE(it1, s.end());
  EXPECT_EQ(*it1, 20);

  auto it2 = s.find(30);
  EXPECT_NE(it2, s.end());
  EXPECT_EQ(*it2, 30);

  auto it3 = s.find(99);
  EXPECT_EQ(it3, s.end());
}

TEST(SetTest, Contains) {
  s21::set<int> s = {1, 2, 3, 4, 5};

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(5));
  EXPECT_FALSE(s.contains(0));
  EXPECT_FALSE(s.contains(6));
  EXPECT_FALSE(s.contains(10));
}

TEST(SetTest, Iterators) {
  s21::set<int> s = {1, 2, 3, 4, 5};

  int expected = 1;
  for (auto it = s.begin(); it != s.end(); ++it) {
    EXPECT_EQ(*it, expected++);
  }
}

TEST(SetTest, ConstIterators) {
  const s21::set<int> s = {1, 2, 3, 4, 5};

  int sum = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}

TEST(SetTest, IteratorEquality) {
  s21::set<int> s = {1, 2, 3};

  auto it1 = s.begin();
  auto it2 = s.begin();

  EXPECT_EQ(it1, it2);

  ++it1;
  EXPECT_NE(it1, it2);

  ++it2;
  EXPECT_EQ(it1, it2);
}

TEST(SetTest, DifferentTypes) {
  s21::set<std::string> s;

  s.insert("apple");
  s.insert("banana");
  s.insert("cherry");
  s.insert("banana");

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains("apple"));
  EXPECT_TRUE(s.contains("banana"));
  EXPECT_TRUE(s.contains("cherry"));

  auto it = s.begin();
  EXPECT_EQ(*it, "apple");
  ++it;
  EXPECT_EQ(*it, "banana");
  ++it;
  EXPECT_EQ(*it, "cherry");
}

TEST(SetTest, LargeSet) {
  s21::set<int> s;
  const int N = 1000;

  for (int i = 0; i < N; ++i) {
    s.insert(i);
  }

  EXPECT_EQ(s.size(), N);

  for (int i = 0; i < N; ++i) {
    EXPECT_TRUE(s.contains(i));
  }

  int prev = -1;
  for (auto value : s) {
    EXPECT_GT(value, prev);
    prev = value;
  }
}

TEST(SetTest, EraseAndInsert) {
  s21::set<int> s;

  for (int i = 0; i < 10; ++i) {
    s.insert(i);
  }
  EXPECT_EQ(s.size(), 10);

  s.erase(s.find(3));
  s.erase(s.find(5));
  s.erase(s.find(7));

  EXPECT_EQ(s.size(), 7);
  EXPECT_FALSE(s.contains(3));
  EXPECT_FALSE(s.contains(5));
  EXPECT_FALSE(s.contains(7));

  s.insert(11);
  s.insert(12);
  s.insert(13);

  EXPECT_EQ(s.size(), 10);
  EXPECT_TRUE(s.contains(11));
  EXPECT_TRUE(s.contains(12));
  EXPECT_TRUE(s.contains(13));
}

TEST(SetTest, EmptyIterators) {
  s21::set<int> s;

  EXPECT_EQ(s.begin(), s.end());

  const s21::set<int> cs;
  EXPECT_EQ(cs.begin(), cs.end());
}

TEST(SetTest, InitializerListEmpty) {
  s21::set<int> s = {};
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, SelfAssignment) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>& ref = s;
  s = std::move(ref);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, FindInEmptySet) {
  s21::set<int> s;

  auto it = s.find(42);
  EXPECT_EQ(it, s.end());

  EXPECT_FALSE(s.contains(42));
}

TEST(SetTest, MergeEmptySet) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2;

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 0);
}

TEST(SetTest, SwapWithEmpty) {
  s21::set<int> s1;
  s21::set<int> s2 = {1, 2, 3};

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, SwapSelf) {
  s21::set<int> s = {1, 2, 3};

  s.swap(s);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, SortedAfterMultipleOperations) {
  s21::set<int> s;

  s.insert(50);
  s.insert(20);
  s.insert(80);
  s.insert(10);
  s.insert(30);
  s.insert(70);
  s.insert(90);
  s.insert(40);
  s.insert(60);

  int prev = -1;
  for (auto value : s) {
    EXPECT_GT(value, prev);
    prev = value;
  }
}

TEST(SetTest, IteratorOperations) {
  s21::set<int> s = {10, 20, 30, 40, 50};

  auto it = s.begin();
  EXPECT_EQ(*it, 10);

  ++it;
  EXPECT_EQ(*it, 20);

  --it;
  EXPECT_EQ(*it, 10);

  it = s.end();
  --it;
  EXPECT_EQ(*it, 50);
}

TEST(SetTest, InsertMany) {
  s21::set<int> s = {1, 2, 3};

  auto results = s.insert_many(4, 5, 6);

  EXPECT_EQ(s.size(), 6);
  EXPECT_EQ(results.size(), 3);

  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(6));

  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_TRUE(results[i].second) << "Failed at index " << i;
  }
}

TEST(SetTest, InsertManyWithDuplicates) {
  s21::set<int> s = {1, 2, 3};

  auto results = s.insert_many(2, 3, 4, 5);

  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(results.size(), 4);

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
  EXPECT_TRUE(s.contains(5));

  int true_count = 0;
  int false_count = 0;

  for (size_t i = 0; i < results.size(); ++i) {
    if (results[i].second) {
      ++true_count;
    } else {
      ++false_count;
    }
  }

  EXPECT_EQ(true_count, 2);
  EXPECT_EQ(false_count, 2);
}

TEST(SetTest, InsertManyEmptySet) {
  s21::set<int> s;

  auto results = s.insert_many(5, 3, 1, 4, 2);

  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(results.size(), 5);

  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_TRUE(results[i].second) << "Failed at index " << i;
  }

  auto it = s.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(SetTest, InsertManyNoArgs) {
  s21::set<int> s = {1, 2, 3};

  auto results = s.insert_many();

  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(results.size(), 0);
  EXPECT_TRUE(results.empty());
}

TEST(SetTest, InsertManySingleArg) {
  s21::set<int> s = {1, 2, 3};

  auto results = s.insert_many(4);

  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(results.size(), 1);
  EXPECT_TRUE(results[0].second);
  EXPECT_EQ(*(results[0].first), 4);

  auto results2 = s.insert_many(4);

  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(results2.size(), 1);
  EXPECT_FALSE(results2[0].second);
  EXPECT_EQ(*(results2[0].first), 4);
}

TEST(SetTest, InsertManyDifferentTypes) {
  s21::set<std::string> s;

  auto results = s.insert_many("banana", "apple", "cherry", "banana");

  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(results.size(), 4);

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_FALSE(results[3].second);

  auto it = s.begin();
  EXPECT_EQ(*it, "apple");
  ++it;
  EXPECT_EQ(*it, "banana");
  ++it;
  EXPECT_EQ(*it, "cherry");
}

TEST(SetTest, InsertManyLarge) {
  s21::set<int> s;

  auto results = s.insert_many(0, 1, 2, 3, 4);

  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(results.size(), 5);

  for (int i = 0; i < 5; ++i) {
    EXPECT_TRUE(s.contains(i)) << "Missing element " << i;
  }

  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_TRUE(results[i].second) << "Failed at index " << i;
  }
}

TEST(SetTest, InsertManyChaining) {
  s21::set<int> s;

  auto results1 = s.insert_many(3, 1, 5);
  auto results2 = s.insert_many(2, 4, 6);
  auto results3 = s.insert_many(1, 3, 5);

  EXPECT_EQ(s.size(), 6);
  EXPECT_EQ(results1.size(), 3);
  EXPECT_EQ(results2.size(), 3);
  EXPECT_EQ(results3.size(), 3);

  int expected = 1;
  for (auto it = s.begin(); it != s.end(); ++it) {
    EXPECT_EQ(*it, expected++);
  }
}

TEST(SetTest, InsertManyWithMoveSemantics) {
  s21::set<std::string> s;

  std::string str1 = "hello";
  std::string str2 = "world";
  std::string str3 = "test";

  auto results =
      s.insert_many(std::move(str1), std::move(str2), std::move(str3));

  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(results.size(), 3);

  EXPECT_TRUE(s.contains("hello"));
  EXPECT_TRUE(s.contains("world"));
  EXPECT_TRUE(s.contains("test"));

  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_TRUE(results[i].second) << "Failed at index " << i;
  }
}
