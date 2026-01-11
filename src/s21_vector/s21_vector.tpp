#include <algorithm>
#include <cstring>
#include <limits>
#include <stdexcept>

#include "s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() : _data(nullptr), _size(0), _capacity(0) {}

template <typename T>
vector<T>::vector(size_type n) : _size(n), _capacity(n) {
  if (n > 0) {
    _data = new value_type[n]();
  } else {
    _data = nullptr;
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : _size(items.size()), _capacity(items.size()) {
  if (_size > 0) {
    _data = new value_type[_capacity];
    std::copy(items.begin(), items.end(), _data);
  } else {
    _data = nullptr;
  }
}

template <typename T>
vector<T>::vector(const vector& v) : _size(v._size), _capacity(v._capacity) {
  if (_capacity > 0) {
    _data = new value_type[_capacity];
    std::copy(v._data, v._data + _size, _data);
  } else {
    _data = nullptr;
  }
}

template <typename T>
vector<T>::vector(vector&& v)
    : _data(v._data), _size(v._size), _capacity(v._capacity) {
  v._data = nullptr;
  v._size = 0;
  v._capacity = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] _data;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& v) {
  if (this != &v) {
    delete[] _data;
    _size = v._size;
    _capacity = v._capacity;
    if (_capacity > 0) {
      _data = new value_type[_capacity];
      std::copy(v._data, v._data + _size, _data);
    } else {
      _data = nullptr;
    }
  }
  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) {
  if (this != &v) {
    delete[] _data;
    _data = v._data;
    _size = v._size;
    _capacity = v._capacity;
    v._data = nullptr;
    v._size = 0;
    v._capacity = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return _data[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return _data[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return _data[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return _data[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (_size == 0) throw std::out_of_range("Vector is empty");
  return _data[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (_size == 0) throw std::out_of_range("Vector is empty");
  return _data[_size - 1];
}

template <typename T>
typename vector<T>::value_type* vector<T>::data() {
  return _data;
}

template <typename T>
const typename vector<T>::value_type* vector<T>::data() const {
  return _data;
}

template <typename T>
vector<T>::iterator vector<T>::begin() {
  return iterator(_data);
}

template <typename T>
vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(_data);
}

template <typename T>
vector<T>::iterator vector<T>::end() {
  return iterator(_data + _size);
}

template <typename T>
vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(_data + _size);
}

template <typename T>
bool vector<T>::empty() const {
  return _size == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return _size;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > _capacity) {
    value_type* new_data = new value_type[new_capacity];
    if (_data) {
      std::copy(_data, _data + _size, new_data);
      delete[] _data;
    }
    _data = new_data;
    _capacity = new_capacity;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return _capacity;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (_capacity > _size) {
    if (_size == 0) {
      delete[] _data;
      _data = nullptr;
      _capacity = 0;
    } else {
      value_type* new_data = new value_type[_size];
      std::copy(_data, _data + _size, new_data);
      delete[] _data;
      _data = new_data;
      _capacity = _size;
    }
  }
}

template <typename T>
void vector<T>::clear() {
  _size = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  size_type index = pos - _data;
  if (index > _size) {
    throw std::out_of_range("Iterator out of range");
  }

  if (_size == _capacity) {
    size_type new_capacity = _capacity == 0 ? 1 : _capacity * 2;
    reserve(new_capacity);
  }

  for (size_type i = _size; i > index; --i) {
    _data[i] = _data[i - 1];
  }

  _data[index] = value;
  ++_size;
  return iterator(_data + index);
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = static_cast<size_type>(pos - begin());
  if (index >= _size) {
    throw std::out_of_range("Iterator out of range");
  }

  for (size_type i = index; i < _size - 1; ++i) {
    _data[i] = _data[i + 1];
  }
  --_size;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (_size == _capacity) {
    size_type new_capacity = _capacity == 0 ? 1 : _capacity * 2;
    reserve(new_capacity);
  }
  _data[_size++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (_size > 0) {
    --_size;
  }
}

template <typename T>
void vector<T>::swap(vector& other) {
  value_type* temp_data = _data;
  _data = other._data;
  other._data = temp_data;

  size_type temp_size = _size;
  _size = other._size;
  other._size = temp_size;

  size_type temp_capacity = _capacity;
  _capacity = other._capacity;
  other._capacity = temp_capacity;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  size_type insert_pos = pos - _data;
  if (insert_pos > _size) {
    throw std::out_of_range("Iterator out of range");
  }

  size_type num_new_elements = sizeof...(Args);

  if (num_new_elements == 0) {
    return iterator(_data + insert_pos);
  }

  if (_size + num_new_elements > _capacity) {
    size_type new_capacity = std::max(_capacity * 2, _size + num_new_elements);
    reserve(new_capacity);
  }

  if (insert_pos < _size) {
    for (size_type i = _size; i > insert_pos; --i) {
      _data[i + num_new_elements - 1] = std::move(_data[i - 1]);
    }
  }

  size_type i = 0;
  ((_data[insert_pos + i++] = std::forward<Args>(args)), ...);

  _size += num_new_elements;
  return iterator(_data + insert_pos);
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  size_type num_new_elements = sizeof...(Args);

  if (num_new_elements == 0) {
    return;
  }

  if (_size + num_new_elements > _capacity) {
    size_type new_capacity = std::max(_capacity * 2, _size + num_new_elements);
    reserve(new_capacity);
  }

  size_type i = 0;
  ((_data[_size + i++] = std::forward<Args>(args)), ...);

  _size += num_new_elements;
}

}  // namespace s21
