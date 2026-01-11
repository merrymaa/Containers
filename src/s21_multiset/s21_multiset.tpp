#ifndef S21_MULTISET_TPP_
#define S21_MULTISET_TPP_

#include <algorithm>
#include <iostream>

#include "s21_multiset.h"

namespace s21 {

// ==================== КОНСТРУКТОРЫ И ДЕСТРУКТОР ====================

template <typename Key>
multiset<Key>::multiset() : root_(nullptr), size_(0) {
  initialize_nil();
  root_ = nil_;
}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : multiset() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& other) : multiset() {
  copy_tree(other);
}

template <typename Key>
multiset<Key>::multiset(multiset&& other) noexcept
    : root_(other.root_), nil_(other.nil_), size_(other.size_) {
  other.root_ = nullptr;
  other.nil_ = nullptr;
  other.size_ = 0;
}

template <typename Key>
multiset<Key>::~multiset() {
  clear();
  delete nil_;
}

// ==================== ОПЕРАТОРЫ ПРИСВАИВАНИЯ ====================

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& other) {
  if (this != &other) {
    clear();
    copy_tree(other);
  }
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& other) noexcept {
  if (this != &other) {
    clear();
    delete nil_;

    root_ = other.root_;
    nil_ = other.nil_;
    size_ = other.size_;

    other.root_ = nullptr;
    other.nil_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================

template <typename Key>
void multiset<Key>::initialize_nil() {
  nil_ = new Node(value_type{}, nullptr, false);  // черный узел
  nil_->left = nil_;
  nil_->right = nil_;
  nil_->parent = nil_;
}

template <typename Key>
void multiset<Key>::copy_tree(const multiset& other) {
  if (other.root_ != other.nil_) {
    // Рекурсивное копирование дерева
    auto copy_recursive = [&](auto& self, Node* other_node,
                              Node* parent) -> Node* {
      if (other_node == other.nil_) return nil_;

      Node* new_node = new Node(other_node->value, parent, other_node->color);
      new_node->count = other_node->count;
      new_node->left = self(self, other_node->left, new_node);
      new_node->right = self(self, other_node->right, new_node);
      return new_node;
    };

    root_ = copy_recursive(copy_recursive, other.root_, nil_);
    size_ = other.size_;
  }
}

template <typename Key>
void multiset<Key>::destroy_tree(Node* node) {
  if (node && node != nil_) {
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}

// ==================== ИТЕРАТОРЫ ====================

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return iterator(minimum(root_), this);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return iterator(nil_, this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::begin() const {
  return const_iterator(minimum(root_), this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::end() const {
  return const_iterator(nil_, this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cbegin() const {
  return const_iterator(minimum(root_), this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cend() const {
  return const_iterator(nil_, this);
}

// ==================== ЕМКОСТЬ ====================

template <typename Key>
bool multiset<Key>::empty() const noexcept {
  return size_ == 0;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() const noexcept {
  return size_;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

// ==================== МОДИФИКАТОРЫ ====================

template <typename Key>
void multiset<Key>::clear() {
  destroy_tree(root_);
  root_ = nil_;
  size_ = 0;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  Node* y = nil_;
  Node* x = root_;

  // Находим место для вставки
  while (x != nil_) {
    y = x;
    if (value < x->value) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  // Создаем новый узел
  Node* z = new Node(value, y);
  z->left = nil_;
  z->right = nil_;

  // Вставляем узел
  if (y == nil_) {
    root_ = z;
  } else if (value < y->value) {
    y->left = z;
  } else {
    y->right = z;
  }

  // Балансировка
  insert_fixup(z);
  size_++;
  return iterator(z, this);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  if (pos.node_ == nil_ || pos.node_ == nullptr) return;

  Node* z = pos.node_;
  Node* y = z;
  Node* x = nullptr;
  bool y_original_color = y->color;

  if (z->left == nil_) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == nil_) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;

    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  delete z;
  size_--;

  if (y_original_color == false) {
    erase_fixup(x);
  }
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  std::swap(root_, other.root_);
  std::swap(nil_, other.nil_);
  std::swap(size_, other.size_);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  if (this == &other) return;

  // Собираем все элементы из other
  std::vector<value_type> elements;
  for (auto it = other.begin(); it != other.end(); ++it) {
    elements.push_back(*it);
  }

  // Очищаем other
  other.clear();

  // Вставляем элементы в текущий multiset
  for (const auto& elem : elements) {
    insert(elem);
  }
}

// ==================== ПОИСК ====================

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  Node* node = find_node(key);
  return iterator(node == nil_ ? nil_ : node, this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::find(
    const Key& key) const {
  Node* node = find_node(key);
  return const_iterator(node == nil_ ? nil_ : node, this);
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) const {
  return find_node(key) != nil_;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) const {
  size_type cnt = 0;
  Node* current = lower_bound_node(key);

  while (current != nil_ && !(key < current->value) &&
         !(current->value < key)) {
    cnt += current->count;
    // Переходим к следующему узлу с тем же ключом
    if (current->right != nil_) {
      current = minimum(current->right);
    } else {
      Node* parent = current->parent;
      while (parent != nil_ && current == parent->right) {
        current = parent;
        parent = parent->parent;
      }
      current = parent;
    }
  }

  return cnt;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  return iterator(lower_bound_node(key), this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::lower_bound(
    const Key& key) const {
  return const_iterator(lower_bound_node(key), this);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return iterator(upper_bound_node(key), this);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::upper_bound(
    const Key& key) const {
  return const_iterator(upper_bound_node(key), this);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key>
std::pair<typename multiset<Key>::const_iterator,
          typename multiset<Key>::const_iterator>
multiset<Key>::equal_range(const Key& key) const {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

// ==================== INSERT_MANY (ТРЕБОВАНИЕ ИЗ ЗАДАНИЯ) ====================

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  results.reserve(sizeof...(Args));

  // Вспомогательная функция для вставки одного элемента
  auto insert_one = [&](auto&& arg) {
    iterator it = insert(std::forward<decltype(arg)>(arg));
    results.emplace_back(it, true);  // Всегда true для multiset
  };

  // Распаковка пакета параметров
  (insert_one(std::forward<Args>(args)), ...);

  return results;
}

// ==================== ПРИВАТНЫЕ ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================

template <typename Key>
typename multiset<Key>::Node* multiset<Key>::minimum(Node* node) const {
  if (node == nil_ || node == nullptr) return nil_;
  while (node->left != nil_) {
    node = node->left;
  }
  return node;
}

template <typename Key>
typename multiset<Key>::Node* multiset<Key>::maximum(Node* node) const {
  if (node == nil_ || node == nullptr) return nil_;
  while (node->right != nil_) {
    node = node->right;
  }
  return node;
}

template <typename Key>
typename multiset<Key>::Node* multiset<Key>::find_node(const Key& key) const {
  Node* current = root_;
  while (current != nil_) {
    if (key < current->value) {
      current = current->left;
    } else if (current->value < key) {
      current = current->right;
    } else {
      return current;  // Найден
    }
  }
  return nil_;  // Не найден
}

template <typename Key>
typename multiset<Key>::Node* multiset<Key>::lower_bound_node(
    const Key& key) const {
  Node* current = root_;
  Node* result = nil_;

  while (current != nil_) {
    if (!(current->value < key)) {  // current->value >= key
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return result;
}

template <typename Key>
typename multiset<Key>::Node* multiset<Key>::upper_bound_node(
    const Key& key) const {
  Node* current = root_;
  Node* result = nil_;

  while (current != nil_) {
    if (key < current->value) {  // current->value > key
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return result;
}

// ==================== МЕТОДЫ КРАСНО-ЧЕРНОГО ДЕРЕВА ====================

template <typename Key>
void multiset<Key>::rotate_left(Node* x) {
  Node* y = x->right;
  x->right = y->left;

  if (y->left != nil_) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nil_) {
    root_ = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

template <typename Key>
void multiset<Key>::rotate_right(Node* y) {
  Node* x = y->left;
  y->left = x->right;

  if (x->right != nil_) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == nil_) {
    root_ = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else {
    y->parent->left = x;
  }

  x->right = y;
  y->parent = x;
}

template <typename Key>
void multiset<Key>::insert_fixup(Node* z) {
  while (z->parent->color == true) {  // Пока родитель красный
    if (z->parent == z->parent->parent->left) {
      Node* y = z->parent->parent->right;  // Дядя

      if (y->color == true) {  // Случай 1: дядя красный
        z->parent->color = false;
        y->color = false;
        z->parent->parent->color = true;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {  // Случай 2: z - правый ребенок
          z = z->parent;
          rotate_left(z);
        }
        // Случай 3: z - левый ребенок
        z->parent->color = false;
        z->parent->parent->color = true;
        rotate_right(z->parent->parent);
      }
    } else {  // Симметричный случай
      Node* y = z->parent->parent->left;

      if (y->color == true) {
        z->parent->color = false;
        y->color = false;
        z->parent->parent->color = true;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotate_right(z);
        }
        z->parent->color = false;
        z->parent->parent->color = true;
        rotate_left(z->parent->parent);
      }
    }
  }
  root_->color = false;  // Корень всегда черный
}

template <typename Key>
void multiset<Key>::transplant(Node* u, Node* v) {
  if (u->parent == nil_) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename Key>
void multiset<Key>::erase_fixup(Node* x) {
  while (x != root_ && x->color == false) {
    if (x == x->parent->left) {
      Node* w = x->parent->right;

      if (w->color == true) {  // Случай 1
        w->color = false;
        x->parent->color = true;
        rotate_left(x->parent);
        w = x->parent->right;
      }

      if (w->left->color == false && w->right->color == false) {  // Случай 2
        w->color = true;
        x = x->parent;
      } else {
        if (w->right->color == false) {  // Случай 3
          w->left->color = false;
          w->color = true;
          rotate_right(w);
          w = x->parent->right;
        }
        // Случай 4
        w->color = x->parent->color;
        x->parent->color = false;
        w->right->color = false;
        rotate_left(x->parent);
        x = root_;
      }
    } else {  // Симметричный случай
      Node* w = x->parent->left;

      if (w->color == true) {
        w->color = false;
        x->parent->color = true;
        rotate_right(x->parent);
        w = x->parent->left;
      }

      if (w->right->color == false && w->left->color == false) {
        w->color = true;
        x = x->parent;
      } else {
        if (w->left->color == false) {
          w->right->color = false;
          w->color = true;
          rotate_left(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = false;
        w->left->color = false;
        rotate_right(x->parent);
        x = root_;
      }
    }
  }
  x->color = false;
}

// ==================== МЕТОДЫ ИТЕРАТОРА ====================

template <typename Key>
typename multiset<Key>::iterator& multiset<Key>::iterator::operator++() {
  if (node_ == nullptr || node_ == container_->nil_) return *this;

  if (node_->right != container_->nil_) {
    // Есть правый ребенок - идем к минимальному в правом поддереве
    node_ = container_->minimum(node_->right);
  } else {
    // Поднимаемся вверх, пока не найдем узел, который является левым ребенком
    Node* parent = node_->parent;
    while (parent != container_->nil_ && node_ == parent->right) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key>
typename multiset<Key>::iterator& multiset<Key>::iterator::operator--() {
  if (node_ == nullptr) return *this;

  if (node_ == container_->nil_) {
    // end() -> last element
    node_ = container_->maximum(container_->root_);
  } else if (node_->left != container_->nil_) {
    // Есть левый ребенок - идем к максимальному в левом поддереве
    node_ = container_->maximum(node_->left);
  } else {
    // Поднимаемся вверх, пока не найдем узел, который является правым ребенком
    Node* parent = node_->parent;
    while (parent != container_->nil_ && node_ == parent->left) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::iterator::operator--(int) {
  iterator temp = *this;
  --(*this);
  return temp;
}

// Аналогичные методы для const_iterator
template <typename Key>
typename multiset<Key>::const_iterator&
multiset<Key>::const_iterator::operator++() {
  if (node_ == nullptr || node_ == container_->nil_) return *this;

  if (node_->right != container_->nil_) {
    node_ = container_->minimum(node_->right);
  } else {
    Node* parent = node_->parent;
    while (parent != container_->nil_ && node_ == parent->right) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::const_iterator
multiset<Key>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key>
typename multiset<Key>::const_iterator&
multiset<Key>::const_iterator::operator--() {
  if (node_ == nullptr) return *this;

  if (node_ == container_->nil_) {
    node_ = container_->maximum(container_->root_);
  } else if (node_->left != container_->nil_) {
    node_ = container_->maximum(node_->left);
  } else {
    Node* parent = node_->parent;
    while (parent != container_->nil_ && node_ == parent->left) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::const_iterator
multiset<Key>::const_iterator::operator--(int) {
  const_iterator temp = *this;
  --(*this);
  return temp;
}

}  // namespace s21

#endif  // S21_MULTISET_TPP_