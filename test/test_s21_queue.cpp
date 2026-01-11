#include <gtest/gtest.h>

#include <queue>

#include "../src/s21_list/s21_list.h"
#include "../src/s21_queue/s21_queue.h"

TEST(S21Queue, Default_constructor) {
  s21::S21Queue<int> my_q;
  std::queue<int> std_q;

  EXPECT_EQ(my_q.empty(), std_q.empty());
}

TEST(S21Queue, Constructor2) {
  s21::S21Queue<int> my_q = {1, 2, 3};
  std::queue<int> std_q;
  std_q.push(1);
  std_q.push(2);
  std_q.push(3);
  EXPECT_EQ(my_q.front(), std_q.front());
  EXPECT_EQ(my_q.back(), std_q.back());
  EXPECT_EQ(my_q.size(), 3);
}

TEST(S21Queue, Constructor3) {
  s21::S21Queue<int> my_q = {1, 2, 3};
  s21::S21Queue<int> our_copy(my_q);
  std::queue<int> std_q;
  std_q.push(1);
  std_q.push(2);
  std_q.push(3);
  std::queue<int> std_copy(std_q);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(S21Queue, Operator_Copy) {
  s21::S21Queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::S21Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = our_queue_int;
  std_queue_empty = std_queue_int;
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(S21Queue, Constructor_Move) {
  s21::S21Queue<int> our_queue = {1, 2, 3};
  s21::S21Queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());
  EXPECT_EQ(our_move.back(), std_move.back());
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(S21Queue, FrontAndBack) {
  s21::S21Queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::S21Queue<double> our_queue_double = {1.1f, 2.1f, 3.1f};
  std::queue<double> std_queue_double;
  std_queue_double.push(1.1f);
  std_queue_double.push(2.1f);
  std_queue_double.push(3.1f);
  s21::S21Queue<std::string> our_queue_string = {"abc", "def", "ghf"};
  std::queue<std::string> std_queue_string;
  std_queue_string.push("abc");
  std_queue_string.push("def");
  std_queue_string.push("ghf");
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_double.front(), std_queue_double.front());
  EXPECT_EQ(our_queue_string.front(), std_queue_string.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  EXPECT_EQ(our_queue_double.back(), std_queue_double.back());
  EXPECT_EQ(our_queue_string.back(), std_queue_string.back());
}

TEST(S21Queue, Empty) {
  s21::S21Queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
  s21::S21Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.empty(), std_queue_empty.empty());
}

TEST(S21Queue, Size) {
  s21::S21Queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.size(), std_queue_int.size());
  s21::S21Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.size(), std_queue_empty.size());
}

TEST(S21Queue, Push) {
  s21::S21Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
}

TEST(S21Queue, Pop) {
  s21::S21Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  our_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  our_queue_int.pop();
  our_queue_int.pop();
  std_queue_int.pop();
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(S21Queue, Swap) {
  s21::S21Queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::S21Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty.swap(our_queue_int);
  std_queue_empty.swap(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(S21Queue, InsertManyBack) {
  s21::S21Queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}