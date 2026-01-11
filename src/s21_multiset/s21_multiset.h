#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>
#include <vector>

namespace s21 {

template <typename Key>
class multiset {
 public:
  // Типы-члены
  using key_type = Key;
  using value_type = Key;  // В multiset ключ и значение совпадают
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  // Внутренний класс Node для дерева
  struct Node {
    value_type value;
    Node* parent;
    Node* left;
    Node* right;
    bool color;       // true - красный, false - черный
    size_type count;  // количество одинаковых элементов

    Node(value_type val, Node* p = nullptr, bool col = true)
        : value(val),
          parent(p),
          left(nullptr),
          right(nullptr),
          color(col),
          count(1) {}
  };

  // Класс итератора
  class iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = multiset::value_type;
    using pointer = value_type*;
    using reference = value_type&;

    iterator() : node_(nullptr), container_(nullptr) {}
    iterator(Node* node, const multiset* container)
        : node_(node), container_(container) {}
    iterator(const iterator& other) = default;
    iterator& operator=(const iterator& other) = default;

    reference operator*() const { return node_->value; }
    pointer operator->() const { return &node_->value; }

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    bool operator==(const iterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const iterator& other) const {
      return node_ != other.node_;
    }

   private:
    Node* node_;
    const multiset* container_;
    friend class multiset;
  };

  // Класс константного итератора
  class const_iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = multiset::value_type;
    using pointer = const value_type*;
    using reference = const value_type&;

    const_iterator() : node_(nullptr), container_(nullptr) {}
    const_iterator(Node* node, const multiset* container)
        : node_(node), container_(container) {}
    const_iterator(const iterator& other)
        : node_(other.node_), container_(other.container_) {}
    const_iterator& operator=(const const_iterator& other) = default;

    reference operator*() const { return node_->value; }
    pointer operator->() const { return &node_->value; }

    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);

    bool operator==(const const_iterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const const_iterator& other) const {
      return node_ != other.node_;
    }

   private:
    Node* node_;
    const multiset* container_;
    friend class multiset;
  };

  // Конструкторы
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other) noexcept;
  ~multiset();

  // Операторы присваивания
  multiset& operator=(const multiset& other);
  multiset& operator=(multiset&& other) noexcept;

  // Итераторы
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Емкость
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Модификаторы
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  // Поиск
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  bool contains(const Key& key) const;
  size_type count(const Key& key) const;
  iterator lower_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  iterator upper_bound(const Key& key);
  const_iterator upper_bound(const Key& key) const;
  std::pair<iterator, iterator> equal_range(const Key& key);
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

  // Вставка нескольких элементов (требование из задания)
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  // Приватные вспомогательные методы для красно-черного дерева
  Node* root_;
  Node* nil_;  // Специальный листовой узел
  size_type size_;

  // Вспомогательные методы
  void initialize_nil();
  void copy_tree(const multiset& other);
  void destroy_tree(Node* node);
  void rotate_left(Node* x);
  void rotate_right(Node* y);
  void insert_fixup(Node* z);
  void erase_fixup(Node* x);
  void transplant(Node* u, Node* v);
  Node* minimum(Node* node) const;
  Node* maximum(Node* node) const;
  Node* find_node(const Key& key) const;
  Node* lower_bound_node(const Key& key) const;
  Node* upper_bound_node(const Key& key) const;
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  // S21_MULTISET_H_