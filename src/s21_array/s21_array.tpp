#ifndef S21_ARRAY_TPP_
#define S21_ARRAY_TPP_

#include "s21_array.h"

namespace s21 {

// Конструктор по умолчанию
template <typename T, std::size_t N>
array<T, N>::array() noexcept : data_{} {}

// Конструктор со списком инициализации
template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) {
  if (items.size() != N) {
    throw std::invalid_argument(
        "Initializer list size must be equal to array size");
  }
  std::copy(items.begin(), items.end(), data_);
}

// Конструктор копирования
template <typename T, std::size_t N>
array<T, N>::array(const array& other) {
  std::copy(other.data_, other.data_ + N, data_);
}

// Конструктор перемещения
template <typename T, std::size_t N>
array<T, N>::array(array&& other) noexcept {
  std::move(other.data_, other.data_ + N, data_);
}

// Оператор присваивания копированием
template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array& other) {
  if (this != &other) {
    std::copy(other.data_, other.data_ + N, data_);
  }
  return *this;
}

// Оператор присваивания перемещением
template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array&& other) noexcept {
  if (this != &other) {
    std::move(other.data_, other.data_ + N, data_);
  }
  return *this;
}

// Доступ с проверкой границ
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

// Оператор индексации
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](
    size_type pos) noexcept {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const noexcept {
  return data_[pos];
}

// Первый элемент
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() noexcept {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const noexcept {
  return data_[0];
}

// Последний элемент
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() noexcept {
  return data_[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const noexcept {
  return data_[N - 1];
}

// Указатель на данные
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return data_;
}

// Итераторы
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept {
  return data_ + N;
}

// Емкость
template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}

// Заполнение
template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}

// Обмен
template <typename T, std::size_t N>
void array<T, N>::swap(array& other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

}  // namespace s21

#endif  // S21_ARRAY_TPP_