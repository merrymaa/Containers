#ifndef S21_SET_H
#define S21_SET_H

#include <cstddef>
#include <initializer_list>
#include <utility>

#include "../s21_vector/s21_vector.h"

namespace s21 {

template <typename Key>
class set {
 public:
  class SetIterator;
  class SetConstIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using size_type = std::size_t;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();
  set& operator=(set&& s);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const Key& key);
  bool contains(const Key& key) const;

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  s21::vector<value_type> data_;

  iterator manual_find(const Key& key);
  const_iterator manual_find(const Key& key) const;
  iterator manual_find_position(const value_type& value);
  const_iterator manual_find_position(const value_type& value) const;
  void manual_sort_and_unique();
};

template <typename Key>
class set<Key>::SetIterator {
 private:
  typename s21::vector<value_type>::iterator ptr_;
  friend class set<Key>;
  friend class SetConstIterator;

 public:
  SetIterator() : ptr_() {}
  explicit SetIterator(typename s21::vector<value_type>::iterator ptr)
      : ptr_(ptr) {}

  const value_type& operator*() const { return *ptr_; }

  SetIterator& operator++() {
    ++ptr_;
    return *this;
  }

  SetIterator operator++(int) {
    SetIterator temp = *this;
    ++ptr_;
    return temp;
  }

  SetIterator& operator--() {
    --ptr_;
    return *this;
  }

  SetIterator operator--(int) {
    SetIterator temp = *this;
    --ptr_;
    return temp;
  }

  bool operator==(const SetIterator& other) const { return ptr_ == other.ptr_; }

  bool operator!=(const SetIterator& other) const { return ptr_ != other.ptr_; }

  bool operator==(const SetConstIterator& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const SetConstIterator& other) const {
    return ptr_ != other.ptr_;
  }

  SetIterator operator+(int n) const {
    auto temp = ptr_;
    for (int i = 0; i < n; ++i) ++temp;
    return SetIterator(temp);
  }

  SetIterator operator-(int n) const {
    auto temp = ptr_;
    for (int i = 0; i < n; ++i) --temp;
    return SetIterator(temp);
  }
};

template <typename Key>
class set<Key>::SetConstIterator {
 private:
  typename s21::vector<value_type>::const_iterator ptr_;
  friend class set<Key>;

 public:
  SetConstIterator() : ptr_() {}
  explicit SetConstIterator(
      typename s21::vector<value_type>::const_iterator ptr)
      : ptr_(ptr) {}
  SetConstIterator(const SetIterator& other) : ptr_(other.ptr_) {}

  const value_type& operator*() const { return *ptr_; }

  SetConstIterator& operator++() {
    ++ptr_;
    return *this;
  }

  SetConstIterator operator++(int) {
    SetConstIterator temp = *this;
    ++ptr_;
    return temp;
  }

  SetConstIterator& operator--() {
    --ptr_;
    return *this;
  }

  SetConstIterator operator--(int) {
    SetConstIterator temp = *this;
    --ptr_;
    return temp;
  }

  bool operator==(const SetConstIterator& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const SetConstIterator& other) const {
    return ptr_ != other.ptr_;
  }

  bool operator==(const SetIterator& other) const { return ptr_ == other.ptr_; }

  bool operator!=(const SetIterator& other) const { return ptr_ != other.ptr_; }
};

}  // namespace s21

#include "s21_set.tpp"

#endif
