#include <algorithm>
#include <cstring>
#include <limits>
#include <stdexcept>

#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set() : data_() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key>::set(const set& s) : data_(s.data_) {
  manual_sort_and_unique();
}

template <typename Key>
set<Key>::set(set&& s) : data_(std::move(s.data_)) {}

template <typename Key>
set<Key>::~set() {}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) {
  if (this != &s) {
    data_ = std::move(s.data_);
  }
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return iterator(data_.begin());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const {
  return const_iterator(data_.begin());
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return iterator(data_.end());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const {
  return const_iterator(data_.end());
}

template <typename Key>
bool set<Key>::empty() const {
  return data_.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const {
  return data_.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const {
  return data_.max_size();
}

template <typename Key>
void set<Key>::clear() {
  data_.clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  auto it = manual_find(value);
  if (it != end()) {
    return std::pair<iterator, bool>(it, false);
  }

  auto pos = manual_find_position(value);

  size_type index = 0;
  for (auto temp_it = begin(); temp_it != pos && temp_it != end(); ++temp_it) {
    ++index;
  }

  data_.insert(data_.begin() + index, value);

  it = manual_find(value);
  return std::pair<iterator, bool>(it, true);
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (pos == end()) {
    return;
  }

  size_type index = 0;
  for (auto it = begin(); it != pos && it != end(); ++it) {
    ++index;
  }

  if (index < data_.size()) {
    data_.erase(data_.begin() + index);
  }
}

template <typename Key>
void set<Key>::swap(set& other) {
  data_.swap(other.data_);
}

template <typename Key>
void set<Key>::merge(set& other) {
  if (this == &other) {
    return;
  }

  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }

  other.clear();
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return manual_find(key);
}

template <typename Key>
bool set<Key>::contains(const Key& key) const {
  return manual_find(key) != end();
}

template <typename Key>
typename set<Key>::iterator set<Key>::manual_find(const Key& key) {
  size_type left = 0;
  size_type right = data_.size();

  while (left < right) {
    size_type mid = left + (right - left) / 2;
    if (data_[mid] == key) {
      return iterator(data_.begin() + mid);
    } else if (data_[mid] < key) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return end();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::manual_find(const Key& key) const {
  size_type left = 0;
  size_type right = data_.size();

  while (left < right) {
    size_type mid = left + (right - left) / 2;
    if (data_[mid] == key) {
      return const_iterator(data_.begin() + mid);
    } else if (data_[mid] < key) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return end();
}

template <typename Key>
typename set<Key>::iterator set<Key>::manual_find_position(
    const value_type& value) {
  size_type left = 0;
  size_type right = data_.size();

  while (left < right) {
    size_type mid = left + (right - left) / 2;
    if (data_[mid] < value) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return iterator(data_.begin() + left);
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::manual_find_position(
    const value_type& value) const {
  size_type left = 0;
  size_type right = data_.size();

  while (left < right) {
    size_type mid = left + (right - left) / 2;
    if (data_[mid] < value) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return const_iterator(data_.begin() + left);
}

template <typename Key>
void set<Key>::manual_sort_and_unique() {
  for (size_type i = 0; i < data_.size(); ++i) {
    for (size_type j = 0; j < data_.size() - i - 1; ++j) {
      if (data_[j + 1] < data_[j]) {
        value_type temp = data_[j];
        data_[j] = data_[j + 1];
        data_[j + 1] = temp;
      }
    }
  }

  if (data_.size() > 1) {
    size_type write_index = 1;
    for (size_type i = 1; i < data_.size(); ++i) {
      if (data_[i] != data_[i - 1]) {
        data_[write_index] = data_[i];
        ++write_index;
      }
    }

    while (data_.size() > write_index) {
      data_.pop_back();
    }
  }
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  s21::vector<std::pair<iterator, bool>> results;

  results.reserve(sizeof...(args));

  (results.push_back(insert(std::forward<Args>(args))), ...);

  return results;
}

}  // namespace s21