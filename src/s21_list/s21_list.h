#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
// #include <iostream>  // for debug
#include <limits>

using std::size_t;

namespace s21 {
template <typename T>
class S21List {
 private:
  struct Node {
    T data;
    Node* prev;
    Node* next;

    // constructor for struct Node
    Node(T d, Node* p = nullptr, Node* n = nullptr)
        : data(d), prev(p), next(n) {}
  };

  Node* head;
  Node* tail;
  size_t size_;

 public:
  class ListIterator {
   private:
    Node* node_;
    friend class S21List<T>;

   public:
    // constructor for iterator
    ListIterator(Node* node = nullptr) : node_(node) {}

    T& operator*() { return node_->data; }
    T* operator->() { return &(node_->data); }

    const T& operator*() const { return node_->data; }
    const T* operator->() const { return &(node_->data); }

    // ++it
    ListIterator& operator++() {
      if (node_) node_ = node_->next;
      return *this;
    }

    // it++
    ListIterator operator++(int) {
      ListIterator old = *this;
      ++(*this);
      return old;
    }

    // --it
    ListIterator& operator--() {
      if (node_) node_ = node_->prev;
      return *this;
    }

    // it--
    ListIterator operator--(int) {
      ListIterator old = *this;
      --(*this);
      return old;
    }

    bool operator==(const ListIterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ListIterator& other) const {
      return !(*this == other);
    }
  };

  class ListConstIterator {
   private:
    Node* node_;
    friend class S21List<T>;

   public:
    // constructor for iterator
    ListConstIterator(Node* node = nullptr) : node_(node) {}

    const T& operator*() const { return node_->data; }
    const T* operator->() const { return &(node_->data); }

    // ++it
    ListConstIterator& operator++() {
      if (node_) node_ = node_->next;
      return *this;
    }

    // it++
    ListConstIterator operator++(int) {
      ListConstIterator old = *this;
      ++(*this);
      return old;
    }

    // --it
    ListConstIterator& operator--() {
      if (node_) node_ = node_->prev;
      return *this;
    }

    // it--
    ListConstIterator operator--(int) {
      ListConstIterator old = *this;
      --(*this);
      return old;
    }

    bool operator==(const ListConstIterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ListConstIterator& other) const {
      return !(*this == other);
    }
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  ListIterator begin();
  ListIterator end();

  ListConstIterator begin() const;
  ListConstIterator end() const;

  // constructor default
  S21List();

  // constructor with one parameter size_
  S21List(size_t n);

  // constructor with initializer_list
  S21List(std::initializer_list<T> const& items);

  // copy constructor
  S21List(const S21List& other);

  // constructor move
  S21List(S21List&& other) noexcept;

  // destructor
  ~S21List();

  void clear() noexcept;

  /**
   * @brief inserts element into concrete pos and returns the iterator that
   * points to the new element
   */
  ListIterator insert(ListIterator pos, const T& value);

  /**
   * @brief erases element at pos
   */
  void erase(ListIterator pos);

  /**
   * @brief removes the first element
   */
  void pop_front();

  /**
   * @brief removes the first element
   */
  void pop_back();

  /**
   * @brief add element in front
   */
  void push_front(const T& value);

  /**
   * @brief add element in back
   */
  void push_back(const T& value);

  /**
   * @brief swaps the contents
   */
  void swap(S21List& other) noexcept;

  /**
   * @brief sorts the elements
   */
  void sort();

  /**
   * @brief removes consecutive duplicate elements
   */
  void unique();

  /**
   * @brief reverses the order of the elements
   */
  void reverse() noexcept;

  /**
   * @brief transfers elements from list other starting from pos
   */
  void splice(const ListIterator pos, S21List& other);

  /**
   * @brief merges two sorted lists
   */
  void merge(S21List& other);

  /**
   * @brief checks whether the container is empty
   */
  bool empty();

  /**
   * @brief returns the number of elements
   */
  size_t size();

  /**
   * @brief returns the maximum possible number of elements
   */
  size_t max_size() const noexcept;

  /**
   * @brief access the first element
   */
  T& front() noexcept;

  /**
   * @brief access the last element
   */
  T& back() noexcept;

  /**
   * @brief access the first element
   */
  const T& front() const;

  /**
   * @brief access the last element
   */
  const T& back() const;

  S21List& operator=(const S21List& other);

  S21List& operator=(S21List&& other) noexcept;

  /**
   * @brief inserts new elements into the container directly before pos
   */
  template <class... Args>
  ListIterator insert_many(ListIterator pos, Args&&... args);

  /**
   * @brief appends new elements to the end of the container
   */
  template <class... Args>
  void insert_many_back(Args&&... args);

  /**
   * @brief appends new elements to the top of the container.
   */
  template <class... Args>
  void insert_many_front(Args&&... args);

  // FOR DEBUG
  // print from head to tail
  // void printForward();

  // print from tail to head
  void printBackward();
  // FOR DEBUG
};

}  // namespace s21

#include "s21_list.tpp"

#endif