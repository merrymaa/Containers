#ifndef S21_STACK_TPP
#define S21_STACK_TPP

#include "s21_stack.h"

namespace s21 {

template <typename T>
S21Stack<T>::S21Stack() : list_{} {}

template <typename T>
S21Stack<T>::S21Stack(const S21Stack& other) : list_(other.list_) {}

template <typename T>
S21Stack<T>::S21Stack(S21Stack&& other) noexcept
    : list_(static_cast<S21List<T>&&>(other.list_)) {}

template <typename T>
S21Stack<T>::S21Stack(std::initializer_list<T> const& items) : list_(items) {}

template <typename T>
S21Stack<T>& S21Stack<T>::operator=(const S21Stack& other) {
  if (this != &other) list_ = other.list_;
  return *this;
}

template <typename T>
S21Stack<T>& S21Stack<T>::operator=(S21Stack&& other) noexcept {
  if (this != &other) {
    list_ = static_cast<S21List<T>&&>(other.list_);
  }
  return *this;
}

template <typename T>
T& S21Stack<T>::top() noexcept {
  return list_.back();
}

template <typename T>
const T& S21Stack<T>::top() const noexcept {
  return list_.back();
}

template <typename T>
bool S21Stack<T>::empty() noexcept {
  return list_.empty();
}

template <typename T>
size_t S21Stack<T>::size() {
  return list_.size();
}

template <typename T>
void S21Stack<T>::push(const T& value) {
  list_.push_back(value);
}

template <typename T>
void S21Stack<T>::pop() {
  list_.pop_back();
}

template <typename T>
void S21Stack<T>::swap(S21Stack& other) {
  list_.swap(other.list_);
}

template <typename T>
template <class... Args>
void S21Stack<T>::insert_many_back(Args&&... args) {
  list_.insert_many_back(args...);
}

}  // namespace s21

#endif