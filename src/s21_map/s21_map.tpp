#ifndef S21_MAP_TPP
#define S21_MAP_TPP

#include "../s21_list/s21_list.h"
#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::moveRedLeft(MapNode* node) {
  flipColors(node);
  if (node->right && isRed(node->right->left)) {
    node->right = rightRotate(node->right);
    node = leftRotate(node);
    flipColors(node);
  }
  return node;
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::moveRedRight(MapNode* node) {
  flipColors(node);
  if (node->left && isRed(node->left->left)) {
    node = rightRotate(node);
    flipColors(node);
  }
  return node;
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::eraseMin(MapNode* node) {
  if (!node->left) {
    delete node;
    return nullptr;
  }

  // рекурсивно спускаемся вниз
  if (!isRed(node->left) && !isRed(node->left->left)) {
    node = moveRedLeft(node);
  }

  node->left = eraseMin(node->left);
  return balanceTree(node);
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::eraseRecursive(MapNode* node,
                                                        const Key& key) {
  if (!node) return nullptr;

  // 1. Спуск влево
  if (key < node->key) {
    if (!isRed(node->left) && !isRed(node->left->left)) {
      node = moveRedLeft(node);
    }
    node->left = eraseRecursive(node->left, key);
  }

  // 2. Спуск вправо (или найден узел)
  else {
    if (isRed(node->left)) {
      node = rightRotate(node);
    }

    if (key == node->key && !node->right) {
      delete node;
      return nullptr;
    }

    if (!isRed(node->right) && !isRed(node->right->left)) {
      node = moveRedRight(node);
    }

    if (key == node->key) {
      if (node->right != nullptr) {
        MapNode* minNode = node->right;
        while (minNode->left) minNode = minNode->left;
        node->key = minNode->key;
        node->value = minNode->value;
        node->right = eraseMin(node->right);
      }
    } else {
      node->right = eraseRecursive(node->right, key);
    }
  }

  return balanceTree(node);
}

template <typename Key, typename T>
void S21Map<Key, T>::clearRecursive(MapNode* node) {
  if (!node) return;

  clearRecursive(node->left);
  clearRecursive(node->right);

  delete node;
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::insert_recursive(
    MapNode* node, MapNode* parent, const pair<Key, T>& value, bool& inserted) {
  // базовый случай: node == nullptr
  if (!node) {
    inserted = true;
    return new MapNode(value, parent);
    // std::cout << "элемент " << value.first << " вставлен" << std::endl;
  }

  if (value.first < node->key) {
    node->left = insert_recursive(node->left, node, value, inserted);
    if (node->left) node->left->parent = node;
  }

  else if (value.first > node->key) {
    node->right = insert_recursive(node->right, node, value, inserted);
    if (node->right) node->right->parent = node;
  }

  else {
    inserted = false;
    return balanceTree(node);
  }

  return balanceTree(node);
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::copyTreeRecursive(MapNode* node,
                                                           MapNode* parent) {
  if (!node) return nullptr;

  MapNode* newNode =
      new MapNode(std::pair<Key, T>(node->key, node->value), parent);
  newNode->is_red = node->is_red;

  newNode->left = copyTreeRecursive(node->left, newNode);
  newNode->right = copyTreeRecursive(node->right, newNode);

  return newNode;
}

template <typename Key, typename T>
bool S21Map<Key, T>::isRed(MapNode* node) const {
  return node && node->is_red;
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::balanceTree(MapNode* node) {
  //  правая нода красная и левая нода черная - левосторонний поворот
  if (node->right && node->right->is_red &&
      (!node->left || !node->left->is_red)) {
    node = leftRotate(node);
  }
  // левая нода красная и левая нода левой ноды красная - правосторонний
  // поворот
  if (node->left && node->left->is_red && node->left->left &&
      node->left->left->is_red) {
    node = rightRotate(node);
  }

  // левая нода красная и правосторонняя нода красная - делаем свап цвета
  if (node->left && node->left->is_red && node->right && node->right->is_red) {
    flipColors(node);
  }

  return node;
}

template <typename Key, typename T>
void S21Map<Key, T>::flipColors(MapNode* node) {
  if (!node || !node->left || !node->right) return;

  node->is_red = !node->is_red;
  node->left->is_red = !node->left->is_red;
  node->right->is_red = !node->right->is_red;
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::rightRotate(MapNode* current) {
  MapNode* leftChild = current->left;

  current->left = leftChild->right;
  if (leftChild->right) leftChild->right->parent = current;

  leftChild->right = current;
  leftChild->parent = current->parent;
  current->parent = leftChild;

  leftChild->is_red = current->is_red;
  current->is_red = true;

  return leftChild;
}

template <typename Key, typename T>
S21Map<Key, T>::MapNode* S21Map<Key, T>::leftRotate(MapNode* current) {
  MapNode* rightChild = current->right;
  if (!rightChild) return current;

  current->right = rightChild->left;
  if (rightChild->left) rightChild->left->parent = current;

  rightChild->left = current;
  rightChild->parent = current->parent;
  current->parent = rightChild;

  rightChild->is_red = current->is_red;
  current->is_red = true;

  return rightChild;
}

template <typename Key, typename T>
S21Map<Key, T>::S21Map() : root_(nullptr), size_(0) {}

template <typename Key, typename T>
S21Map<Key, T>::S21Map(
    std::initializer_list<std::pair<const Key, T>> const& items)
    : root_(nullptr), size_(0) {
  for (auto i = items.begin(); i != items.end(); ++i) insert(*i);
}

template <typename Key, typename T>
S21Map<Key, T>::S21Map(const S21Map& other) : root_(nullptr), size_(0) {
  if (other.root_) {
    root_ = copyTreeRecursive(other.root_, nullptr);
    size_ = other.size_;
  }
}

template <typename Key, typename T>
S21Map<Key, T>::S21Map(S21Map&& m) noexcept : root_(m.root_), size_(m.size_) {
  m.root_ = nullptr;
  m.size_ = 0;
}

template <typename Key, typename T>
S21Map<Key, T>::~S21Map() noexcept {
  clear();
}

template <typename Key, typename T>
void S21Map<Key, T>::clear() {
  clearRecursive(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T>
S21Map<Key, T>& S21Map<Key, T>::operator=(S21Map&& m) noexcept {
  if (this != &m) {
    clear();
    root_ = m.root_;
    size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;
  }
  return *this;
}

template <typename Key, typename T>
typename S21Map<Key, T>::iterator S21Map<Key, T>::begin() {
  if (!root_) return end();
  MapNode* node = root_;
  while (node->left) node = node->left;
  return MapIterator(node);
}

template <typename Key, typename T>
typename S21Map<Key, T>::iterator S21Map<Key, T>::end() {
  return MapIterator(nullptr);
}

template <typename Key, typename T>
typename S21Map<Key, T>::const_iterator S21Map<Key, T>::begin() const {
  if (!root_) return end();
  const MapNode* node = root_;
  while (node->left) node = node->left;
  return MapConstIterator(node);
}

template <typename Key, typename T>
typename S21Map<Key, T>::const_iterator S21Map<Key, T>::end() const {
  return MapConstIterator(nullptr);
}

template <typename Key, typename T>
pair<typename S21Map<Key, T>::iterator, bool> S21Map<Key, T>::insert(
    const pair<const Key, T>& value) {
  bool inserted = false;
  root_ = insert_recursive(root_, nullptr, value, inserted);
  if (inserted) {
    ++size_;
    if (root_) root_->is_red = false;
  }
  return {find(value.first), inserted};
}

template <typename Key, typename T>
pair<typename S21Map<Key, T>::iterator, bool> S21Map<Key, T>::insert(
    const Key& key, const T& obj) {
  return insert(pair<const Key, T>(key, obj));
}

template <typename Key, typename T>
pair<typename S21Map<Key, T>::iterator, bool> S21Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  MapIterator it = find(key);

  if (it != end()) {
    it.iter_->value = obj;
    return pair<MapIterator, bool>(it, false);
  } else {
    auto res = insert(key, obj);
    return pair<MapIterator, bool>(res.first, true);
  }
}

template <typename Key, typename T>
typename S21Map<Key, T>::iterator S21Map<Key, T>::find(const Key& key) {
  MapNode* node = root_;
  while (node) {
    if (key == node->key) {
      return MapIterator(node);
    } else if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return end();
}

template <typename Key, typename T>
void S21Map<Key, T>::erase(MapIterator pos) {
  if (pos.iter_ == nullptr) return;
  Key key = pos.iter_->key;
  root_ = eraseRecursive(root_, key);
  --size_;
  if (root_) root_->is_red = false;
}

template <typename Key, typename T>
void S21Map<Key, T>::swap(S21Map& other) noexcept {
  MapNode* tmp = root_;
  root_ = other.root_;
  other.root_ = tmp;

  size_t tmp_size = size_;
  size_ = other.size_;
  other.size_ = tmp_size;
}

template <typename Key, typename T>
void S21Map<Key, T>::merge(S21Map& other) {
  if (this == &other) return;

  S21List<Key> keys_to_move;

  for (auto it = other.begin(); it != other.end(); ++it) {
    const Key& key = it.iter_->key;
    if (find(key) == this->end()) {
      keys_to_move.push_back(key);
    }
  }

  for (auto list_it = keys_to_move.begin(); list_it != keys_to_move.end();
       ++list_it) {
    const Key& key = *list_it;

    auto it_other = other.find(key);
    if (it_other != other.end()) {
      insert(pair<const Key, T>(key, it_other.iter_->value));

      other.erase(it_other);
    }
  }
}

template <typename Key, typename T>
bool S21Map<Key, T>::contains(const Key& key) {
  // if (find(key))
  //   return true;
  // else
  //   return false;
  return find(key) != end();
}

template <typename Key, typename T>
bool S21Map<Key, T>::empty() {
  if (!size_)
    return true;
  else
    return false;
}

template <typename Key, typename T>
typename S21Map<Key, T>::size_type S21Map<Key, T>::size() {
  return size_;
}

template <typename Key, typename T>
typename S21Map<Key, T>::size_type S21Map<Key, T>::max_size() const noexcept {
  const size_t node_size = sizeof(MapNode);
  const size_t max_size_t = std::numeric_limits<T>::max();
  if (node_size == 0) return max_size_t;

  return max_size_t / node_size;
};

template <typename Key, typename T>
T& S21Map<Key, T>::at(const Key& key) {
  MapIterator it = find(key);
  if (it == end()) {
    throw std::out_of_range("s21::S21Map::at: key not found");
  }
  return it.iter_->value;
}

template <typename Key, typename T>
T& S21Map<Key, T>::operator[](const Key& key) {
  MapIterator it = find(key);
  if (it != end()) {
    return it.iter_->value;
  }
  auto res = insert(pair<const Key, T>(key, T()));
  return res.first.iter_->value;
}

// template <typename Key, typename T>
// void S21Map<Key, T>::printTree() const {
//   if (!root_) {
//     std::cout << "(empty)\n";
//     return;
//   }
//   std::cout << "=== LLRB Tree (root at top) ===\n";
//   printTreeRecursive(root_, "", true);
//   std::cout << "================================\n";
// }

// template <typename Key, typename T>
// void S21Map<Key, T>::printTreeRecursive(MapNode* node,
//                                         const std::string& prefix,
//                                         bool is_left) const {
//   if (!node) return;

//   std::cout << prefix;
//   std::cout << (is_left ? "├── " : "└── ");

//   // Цвет: R — красный, B — чёрный
//   char color = node->is_red ? 'R' : 'B';
//   std::cout << "[" << color << "] " << node->key << " → " << node->value;

//   if (node->left || node->right) {
//     std::cout << " (";
//     if (node->left) std::cout << "L:" << node->left->key;
//     if (node->right) {
//       if (node->left) std::cout << ", ";
//       std::cout << "R:" << node->right->key;
//     }
//     std::cout << ")";
//   }
//   std::cout << "\n";

//   if (node->left || node->right) {
//     std::string next_prefix = prefix + (is_left ? "│   " : "    ");

//     if (node->left) {
//       printTreeRecursive(node->left, next_prefix, true);
//     } else {
//     }

//     if (node->right) {
//       printTreeRecursive(node->right, next_prefix, false);
//     }
//   }
// }

}  // namespace s21
#endif