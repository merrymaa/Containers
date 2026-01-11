#ifndef S21_LIST_TPP
#define S21_LIST_TPP

namespace s21 {
template <typename T>
S21List<T>::S21List() : head(nullptr), tail(nullptr), size_(0){};

template <typename T>
S21List<T>::S21List(size_t n) : head(nullptr), tail(nullptr), size_(n){};

template <typename T>
S21List<T>::S21List(std::initializer_list<T> const& items) : S21List{} {
  for (const auto& item : items) {
    push_back(item);
  }
};

template <typename T>
S21List<T>::S21List(const S21List& other)
    : head(nullptr), tail(nullptr), size_(0) {
  Node* current = other.head;
  while (current) {
    push_back(current->data);
    current = current->next;
  }
};

template <typename T>
S21List<T>::S21List(S21List&& other) noexcept
    : head(other.head), tail(other.tail), size_(other.size_) {
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
};

template <typename T>
S21List<T>::~S21List() {
  clear();
};

template <typename T>
void S21List<T>::clear() noexcept {
  while (head) {
    Node* tmp = head;
    head = head->next;
    delete tmp;
  }
  tail = nullptr;
  size_ = 0;
};

template <typename T>
typename S21List<T>::ListIterator S21List<T>::begin() {
  return ListIterator(head);
}
template <typename T>
typename S21List<T>::ListIterator S21List<T>::end() {
  return ListIterator(nullptr);
}

template <typename T>
typename S21List<T>::ListConstIterator S21List<T>::begin() const {
  return ListConstIterator(head);
}
template <typename T>
typename S21List<T>::ListConstIterator S21List<T>::end() const {
  return ListConstIterator(nullptr);
}

template <typename T>
void S21List<T>::erase(ListIterator pos) {
  if (pos == end() || !pos.node_) return;

  Node* nodeToDelete = pos.node_;
  if (nodeToDelete == head && nodeToDelete == tail) {
    head = nullptr;
    tail = nullptr;
  } else if (nodeToDelete == head) {
    head = head->next;
    head->prev = nullptr;
  } else if (nodeToDelete == tail) {
    tail = tail->prev;
    tail->next = nullptr;
  } else {
    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;
  }

  delete nodeToDelete;
  size_--;
};

template <typename T>
typename S21List<T>::ListIterator S21List<T>::insert(ListIterator pos,
                                                     const T& value) {
  if (pos == end()) {
    // insert in back
    push_back(value);
    return ListIterator(tail);
  } else if (pos == begin()) {
    // insert in front
    push_front(value);
    return begin();
  } else {
    // insert between head and tail
    Node* current = pos.node_;

    Node* newNode = new Node(value, current->prev, current);
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    size_++;
    return ListIterator(newNode);
  }
}

template <typename T>
void S21List<T>::pop_front() {
  if (!head) return;

  Node* old = head;
  if (head == tail) {
    head = nullptr;
    tail = nullptr;
  }

  else {
    head = head->next;
    head->prev = nullptr;
  }
  size_--;
  delete old;
};

template <typename T>
void S21List<T>::pop_back() {
  if (!tail) return;

  Node* old = tail;
  if (head == tail) {
    head = nullptr;
    tail = nullptr;
  }

  else {
    tail = tail->prev;
    tail->next = nullptr;
  }
  size_--;
  delete old;
};

template <typename T>
void S21List<T>::push_front(const T& value) {
  Node* newNode = new Node(value, nullptr, head);

  if (head == nullptr) {  // list is empty
    head = newNode;
    tail = newNode;
  } else {
    head->prev = newNode;
    head = newNode;
  }
  size_++;
};

template <typename T>
void S21List<T>::push_back(const T& value) {
  Node* newNode = new Node(value, tail, nullptr);
  if (head == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  size_++;
};

template <typename T>
void S21List<T>::swap(S21List& other) noexcept {
  if (this == &other) {
    return;
  }

  Node* temp_head = head;
  Node* temp_tail = tail;
  size_t temp_size = size_;

  head = other.head;
  tail = other.tail;
  size_ = other.size_;

  other.head = temp_head;
  other.tail = temp_tail;
  other.size_ = temp_size;
};

template <typename T>
void S21List<T>::sort() {
  if (size_ <= 1) return;

  for (ListIterator it_a = begin(); it_a != end(); it_a++) {
    // std::cout << "it = " << *it_min << ": ";
    ListIterator it_min = it_a;
    for (ListIterator it_b = it_a; it_b != end(); it_b++) {
      if (*it_b < *it_min) it_min = it_b;
      // std::cout << *it_next << " ";
    }
    if (it_a != it_min) {
      T tmp = it_a.node_->data;
      it_a.node_->data = it_min.node_->data;
      it_min.node_->data = tmp;
    }
  }
};

template <typename T>
void S21List<T>::unique() {
  if (size_ <= 1) return;

  auto it = begin();
  while (it != end()) {
    auto next_it = it;
    ++next_it;
    if (next_it == end()) break;

    if (*it == *next_it) {
      auto after_next = next_it;
      ++after_next;

      erase(next_it);
    } else {
      ++it;
    }
  }
};

template <typename T>
void S21List<T>::reverse() noexcept {
  if (size_ <= 1) return;
  Node* old_head = head;
  Node* old_tail = tail;
  Node* current = head;
  while (current) {
    Node* tmp = current->prev;
    current->prev = current->next;
    current->next = tmp;
    current = current->prev;
  }

  head = old_tail;
  tail = old_head;
};

template <typename T>
void S21List<T>::splice(const ListIterator pos, S21List& other) {
  if (other.empty() || &other == this) return;

  Node* insert_before = pos.node_;  // если pos == end
  Node* other_head = other.head;
  Node* other_tail = other.tail;

  if (empty()) {
    head = other_head;
    tail = other_tail;
    size_ += other.size_;
  } else {
    if (insert_before == nullptr) {
      tail->next = other_head;
      other_head->prev = tail;
      tail = other_tail;
    } else {
      Node* prev_node = insert_before->prev;
      if (prev_node) {
        prev_node->next = other_head;
      } else {
        head = other_head;
      }
      other_head->prev = prev_node;
      other_tail->next = insert_before;
      insert_before->prev = other_tail;
    }
    size_ += other.size_;
  }

  // очистка other
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}

template <typename T>
void S21List<T>::merge(S21List& other) {
  if (&other == this || other.empty()) return;
  if (empty()) {
    splice(begin(), other);
    return;
  }

  auto it = begin();
  while (!other.empty()) {
    auto other_it = other.begin();
    const T& value = *other_it;

    while (it != end() && *it < value) {
      ++it;
    }

    S21List tmp;
    tmp.splice(tmp.begin(), other);

    splice(it, tmp);
  }
}

template <typename T>
bool S21List<T>::empty() {
  return size_ == 0;
};

template <typename T>
size_t S21List<T>::size() {
  return size_;
};

template <typename T>
size_t S21List<T>::max_size() const noexcept {
  const size_t node_size = sizeof(Node);

  const size_t max_size_t = std::numeric_limits<T>::max();

  if (node_size == 0) return max_size_t;

  return max_size_t / node_size;
};

template <typename T>
T& S21List<T>::front() noexcept {
  return head->data;
};

template <typename T>
T& S21List<T>::back() noexcept {
  return tail->data;
};

template <typename T>
const T& S21List<T>::front() const {
  return head->data;
};

template <typename T>
const T& S21List<T>::back() const {
  return tail->data;
};

template <typename T>
S21List<T>& S21List<T>::operator=(const S21List& other) {
  if (this != &other) {
    clear();

    Node* current = other.head;
    while (current) {
      push_back(current->data);
      current = current->next;
    }
  }
  return *this;
};

template <typename T>
S21List<T>& S21List<T>::operator=(S21List&& other) noexcept {
  if (this != &other) {
    clear();

    head = other.head;
    tail = other.tail;
    size_ = other.size_;

    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }
  return *this;
};

template <typename T>
template <class... Args>
typename S21List<T>::ListIterator S21List<T>::insert_many(ListIterator pos,
                                                          Args&&... args) {
  if constexpr (sizeof...(Args) == 0) {
    return pos;
  }

  S21List<T> tmp;
  for (auto& arg : {args...}) {
    tmp.push_front(arg);
  }

  ListIterator result = end();
  for (auto it = tmp.begin(); it != tmp.end(); ++it) {
    pos = insert(pos, *it);
    if (result == end()) {
      result = pos;
    }
  }

  return result;
}

template <typename T>
template <class... Args>
void S21List<T>::insert_many_back(Args&&... args) {
  for (auto& arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <class... Args>
void S21List<T>::insert_many_front(Args&&... args) {
  for (auto& arg : {args...}) {
    push_front(arg);
  }
}

// FOR DEBUG

// template <typename T>
// void S21List<T>::printForward() {
//   Node* currentNode = head;
//   while (currentNode) {
//     std::cout << currentNode->data << " ";
//     currentNode = currentNode->next;
//   }
//   std::cout << "size = " << size_ << std::endl;
// }

// template <typename T>
// void S21List<T>::printBackward() {
//   Node* currentNode = tail;
//   while (currentNode) {
//     std::cout << currentNode->data << " ";
//     currentNode = currentNode->prev;
//   }
//   std::cout << "size = " << size_ << std::endl;
// }
// FOR DEBUG

}  // namespace s21

#endif