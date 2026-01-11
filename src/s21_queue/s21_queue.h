#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../s21_list/s21_list.h"

namespace s21 {

template <typename T>
class S21Queue {
 private:
  S21List<T> list_;

 public:
  S21Queue();

  S21Queue(const S21Queue& other);

  S21Queue(std::initializer_list<T> const& items);

  S21Queue& operator=(const S21Queue& other);

  S21Queue(S21Queue&& other) noexcept;

  T& back() noexcept;

  const T& back() const noexcept;

  T& front() noexcept;

  const T& front() const noexcept;

  bool empty() noexcept;

  size_t size();

  void push(const T& value);

  void pop();

  void swap(S21Queue& other);

  template <class... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "s21_queue.tpp"

#endif
