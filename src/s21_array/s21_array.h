#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

// ПРЕДВАРИТЕЛЬНОЕ ОБЪЯВЛЕНИЕ основного шаблона
template <typename T, std::size_t N>
class array;

// СПЕЦИАЛИЗАЦИЯ для N = 0 (должна быть определена ПОСЛЕ объявления основного
// шаблона)
template <typename T>
class array<T, 0> {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  // Конструкторы
  array() noexcept = default;
  array(std::initializer_list<value_type> const& items) {
    if (items.size() != 0) {
      throw std::invalid_argument(
          "Initializer list must be empty for zero-size array");
    }
  }
  array(const array&) = default;
  array(array&&) noexcept = default;
  ~array() = default;

  // Операторы присваивания
  array& operator=(const array&) = default;
  array& operator=(array&&) noexcept = default;

  // Доступ к элементам
  reference at(size_type pos) {
    (void)pos;
    throw std::out_of_range("array<T, 0>::at: index out of range");
  }

  const_reference at(size_type pos) const {
    (void)pos;
    throw std::out_of_range("array<T, 0>::at: index out of range");
  }

  reference operator[](size_type) noexcept {
    static value_type dummy;
    return dummy;
  }

  const_reference operator[](size_type) const noexcept {
    static value_type dummy;
    return dummy;
  }

  reference front() {
    throw std::out_of_range("array<T, 0>::front: empty array");
  }

  const_reference front() const {
    throw std::out_of_range("array<T, 0>::front: empty array");
  }

  reference back() {
    throw std::out_of_range("array<T, 0>::back: empty array");
  }

  const_reference back() const {
    throw std::out_of_range("array<T, 0>::back: empty array");
  }

  iterator data() noexcept { return nullptr; }
  const_iterator data() const noexcept { return nullptr; }

  // Итераторы
  iterator begin() noexcept { return nullptr; }
  iterator end() noexcept { return nullptr; }
  const_iterator begin() const noexcept { return nullptr; }
  const_iterator end() const noexcept { return nullptr; }
  const_iterator cbegin() const noexcept { return nullptr; }
  const_iterator cend() const noexcept { return nullptr; }

  // Емкость
  bool empty() const noexcept { return true; }
  size_type size() const noexcept { return 0; }
  size_type max_size() const noexcept { return 0; }

  // Операции
  void fill(const_reference) noexcept {}

  void swap(array&) noexcept {}
};

// ОСНОВНОЙ ШАБЛОН для N > 0
template <typename T, std::size_t N>
class array {
 public:
  // Типы-члены
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

 private:
  // Массив данных (не создается для N=0 благодаря специализации выше)
  value_type data_[N];

 public:
  // Конструкторы
  array() noexcept : data_{} {}  // value initialization

  array(std::initializer_list<value_type> const& items) {
    if (items.size() != N) {
      throw std::invalid_argument(
          "Initializer list size must be equal to array size");
    }
    std::copy(items.begin(), items.end(), data_);
  }

  array(const array& other) { std::copy(other.data_, other.data_ + N, data_); }

  array(array&& other) noexcept {
    std::move(other.data_, other.data_ + N, data_);
  }

  ~array() = default;

  // Операторы присваивания
  array& operator=(const array& other) {
    if (this != &other) {
      std::copy(other.data_, other.data_ + N, data_);
    }
    return *this;
  }

  array& operator=(array&& other) noexcept {
    if (this != &other) {
      std::move(other.data_, other.data_ + N, data_);
    }
    return *this;
  }

  // Доступ к элементам
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) noexcept { return data_[pos]; }

  const_reference operator[](size_type pos) const noexcept {
    return data_[pos];
  }

  reference front() noexcept { return data_[0]; }

  const_reference front() const noexcept { return data_[0]; }

  reference back() noexcept { return data_[N - 1]; }

  const_reference back() const noexcept { return data_[N - 1]; }

  iterator data() noexcept { return data_; }
  const_iterator data() const noexcept { return data_; }

  // Итераторы
  iterator begin() noexcept { return data_; }
  iterator end() noexcept { return data_ + N; }
  const_iterator begin() const noexcept { return data_; }
  const_iterator end() const noexcept { return data_ + N; }
  const_iterator cbegin() const noexcept { return data_; }
  const_iterator cend() const noexcept { return data_ + N; }

  // Емкость
  bool empty() const noexcept { return N == 0; }
  size_type size() const noexcept { return N; }
  size_type max_size() const noexcept { return N; }

  // Операции
  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

  void swap(array& other) noexcept {
    for (size_type i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }
};

}  // namespace s21

#endif  // S21_ARRAY_H_