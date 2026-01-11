#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

#include "s21_queue.h"

namespace s21 {

template <typename T>
S21Queue<T>::S21Queue() : list_{} {}

template <typename T>
S21Queue<T>::S21Queue(const S21Queue& other) : list_(other.list_) {}

template <typename T>
S21Queue<T>::S21Queue(std::initializer_list<T> const& items) : list_(items) {}

template <typename T>
S21Queue<T>::S21Queue(S21Queue&& other) noexcept : list_() {
  list_.swap(other.list_);
}

template <typename T>
S21Queue<T>& S21Queue<T>::operator=(const S21Queue& other) {
  if (this != &other) list_ = other.list_;
  return *this;
}

template <typename T>
T& S21Queue<T>::back() noexcept {
  return list_.back();
}

template <typename T>
const T& S21Queue<T>::back() const noexcept {
  return list_.back();
}

template <typename T>
T& S21Queue<T>::front() noexcept {
  return list_.front();
}

template <typename T>
const T& S21Queue<T>::front() const noexcept {
  return list_.front();
}

template <typename T>
bool S21Queue<T>::empty() noexcept {
  return list_.empty();
}

template <typename T>
size_t S21Queue<T>::size() {
  return list_.size();
}

template <typename T>
void S21Queue<T>::push(const T& value) {
  list_.push_back(value);
}

template <typename T>
void S21Queue<T>::pop() {
  list_.pop_front();
}

template <typename T>
void S21Queue<T>::swap(S21Queue& other) {
  list_.swap(other.list_);
}

template <typename T>
template <class... Args>
void S21Queue<T>::insert_many_back(Args&&... args) {
  list_.insert_many_back(args...);
}

}  // namespace s21

#endif