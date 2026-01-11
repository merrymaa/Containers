#ifndef S21_STACK_H
#define S21_STACK_H

#include "../s21_list/s21_list.h"

namespace s21 {
template <typename T>
class S21Stack {
 private:
  S21List<T> list_;

 public:
  S21Stack();

  S21Stack(const S21Stack& other);

  S21Stack(S21Stack&& other) noexcept;

  S21Stack(std::initializer_list<T> const& items);

  S21Stack& operator=(const S21Stack& other);

  S21Stack& operator=(S21Stack&& other) noexcept;

  T& top() noexcept;
  const T& top() const noexcept;
  bool empty() noexcept;

  size_t size();

  void push(const T& value);

  void pop();

  void swap(S21Stack& other);

  template <class... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "s21_stack.tpp"

#endif