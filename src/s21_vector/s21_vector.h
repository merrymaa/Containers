#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;
  using size_type = std::size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();
  vector& operator=(const vector& v);
  vector& operator=(vector&& v);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  value_type* data();
  const value_type* data() const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(const_iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  value_type* _data;
  size_type _size;
  size_type _capacity;
};

template <typename T>
class vector<T>::VectorIterator {
 private:
  T* ptr_;
  friend class VectorConstIterator;

 public:
  VectorIterator() : ptr_(nullptr) {}
  explicit VectorIterator(T* ptr) : ptr_(ptr) {}

  T& operator*() const { return *ptr_; }

  VectorIterator& operator++() {
    ++ptr_;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator temp = *this;
    ++ptr_;
    return temp;
  }

  VectorIterator& operator+=(int n) {
    ptr_ += n;
    return *this;
  }

  VectorIterator& operator--() {
    --ptr_;
    return *this;
  }

  VectorIterator operator--(int) {
    VectorIterator temp = *this;
    --ptr_;
    return temp;
  }

  VectorIterator& operator-=(int n) {
    ptr_ -= n;
    return *this;
  }

  bool operator==(const VectorIterator& other) const {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const VectorIterator& other) const {
    return ptr_ != other.ptr_;
  }

  std::ptrdiff_t operator-(const VectorIterator& other) const {
    return ptr_ - other.ptr_;
  }

  operator T*() const { return ptr_; }

  VectorIterator operator+(int n) const { return VectorIterator(ptr_ + n); }
  VectorIterator operator-(int n) const { return VectorIterator(ptr_ - n); }
};

template <typename T>
class vector<T>::VectorConstIterator {
 private:
  const T* ptr_;

 public:
  VectorConstIterator() : ptr_(nullptr) {}
  explicit VectorConstIterator(const T* ptr) : ptr_(ptr) {}
  VectorConstIterator(const VectorIterator& other) : ptr_(other.ptr_) {}

  const T& operator*() const { return *ptr_; }

  VectorConstIterator& operator++() {
    ++ptr_;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator temp = *this;
    ++ptr_;
    return temp;
  }

  VectorConstIterator& operator+=(int n) {
    ptr_ += n;
    return *this;
  }

  VectorConstIterator& operator--() {
    --ptr_;
    return *this;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator temp = *this;
    --ptr_;
    return temp;
  }

  VectorConstIterator& operator-=(int n) {
    ptr_ -= n;
    return *this;
  }

  bool operator==(const VectorConstIterator& other) const {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const VectorConstIterator& other) const {
    return ptr_ != other.ptr_;
  }

  std::ptrdiff_t operator-(const VectorConstIterator& other) const {
    return ptr_ - other.ptr_;
  }

  operator const T*() const { return ptr_; }

  VectorConstIterator operator+(int n) const {
    return VectorConstIterator(ptr_ + n);
  }
  VectorConstIterator operator-(int n) const {
    return VectorConstIterator(ptr_ - n);
  }
};

}  // namespace s21

#include "s21_vector.tpp"

#endif
