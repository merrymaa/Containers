#include <gtest/gtest.h>

#include <stack>

#include "../src/s21_list/s21_list.h"
#include "../src/s21_stack/s21_stack.h"

TEST(S21Stack, Default_constructor) {
  s21::S21Stack<int> my_s;
  std::stack<int> std_s;

  EXPECT_EQ(my_s.empty(), std_s.empty());
}

TEST(S21Stack, Constructor_List) {
  s21::S21Stack<int> our_stack = {1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(our_stack.top(), std_stack.top());
}

TEST(S21Stack, Constructor_Copy) {
  s21::S21Stack<int> our_stack = {1, 2, 3};
  s21::S21Stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.top(), std_copy.top());
}

TEST(S21Stack, Operator_Copy) {
  s21::S21Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::S21Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = our_stack_int;
  std_stack_empty = std_stack_int;
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(S21Stack, Constructor_Move) {
  s21::S21Stack<int> our_stack = {1, 2, 3};
  s21::S21Stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.top(), std_move.top());
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(S21Stack, Operator_Move) {
  s21::S21Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::S21Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(S21Stack, Top) {
  s21::S21Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::S21Stack<double> our_stack_double = {1.1f, 2.1f, 3.1f};
  std::stack<double> std_stack_double;
  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);
  s21::S21Stack<std::string> our_stack_string = {"abc", "def", "ghf"};
  std::stack<std::string> std_stack_string;
  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  EXPECT_EQ(our_stack_double.top(), std_stack_double.top());
  EXPECT_EQ(our_stack_string.top(), std_stack_string.top());
}

TEST(S21Stack, Empty) {
  s21::S21Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
  s21::S21Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.empty(), std_stack_empty.empty());
}

TEST(Stack, Size) {
  s21::S21Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  s21::S21Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.size(), std_stack_empty.size());
}

TEST(S21Stack, Push) {
  s21::S21Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(S21Stack, Pop) {
  s21::S21Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  our_stack_int.pop();
  our_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(S21Stack, Swap) {
  s21::S21Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::S21Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty.swap(our_stack_int);
  std_stack_empty.swap(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(S21Stack, InitializerList) {
  s21::S21Stack<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
}

TEST(S21Stack, MoveConstructor) {
  s21::S21Stack<int> s1{10, 20, 30};
  s21::S21Stack<int> s2(std::move(s1));

  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 30);

  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s1.size(), 0);
}

TEST(S21Stack, CopyAssignment) {
  s21::S21Stack<int> s1{100, 200};
  s21::S21Stack<int> s2{1, 2, 3, 4};

  s2 = s1;

  EXPECT_EQ(s2.size(), 2);
  EXPECT_EQ(s2.top(), 200);
  EXPECT_EQ(s1.size(), 2);
}

TEST(S21Stack, Pop2) {
  s21::S21Stack<int> s{5, 10, 15};
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 15);

  s.pop();
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 10);

  s.pop();
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(S21Stack, Swap2) {
  s21::S21Stack<int> s1{1, 2};
  s21::S21Stack<int> s2{10, 20, 30};

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s1.top(), 30);
  EXPECT_EQ(s2.size(), 2);
  EXPECT_EQ(s2.top(), 2);
}

TEST(S21Stack, SelfAssignment) {
  s21::S21Stack<int> s{7, 8, 9};
  s = s;

  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 9);
}

TEST(StackMethod, InsertManyBack) {
  s21::S21Stack<std::string> s;
  s.insert_many_back("hello", "world");

  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), "world");
  s.pop();
  EXPECT_EQ(s.top(), "hello");
}