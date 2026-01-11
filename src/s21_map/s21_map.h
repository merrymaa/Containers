#ifndef S21_MAP_H
#define S21_MAP_H

#include <initializer_list>
#include <stdexcept>

namespace s21 {

using std::pair;

template <typename Key, typename T>
class S21Map {
 private:
  struct MapNode {
    Key key;
    T value;
    MapNode* left;
    MapNode* right;
    MapNode* parent;
    bool is_red;

    MapNode(const pair<Key, T>& item, MapNode* p = nullptr)
        : key(item.first),
          value(item.second),
          left(nullptr),
          right(nullptr),
          parent(p),
          is_red(true){};
  };

  MapNode* root_;
  size_t size_;

  class MapIterator {
   private:
    MapNode* iter_;

   public:
    friend class S21Map<Key, T>;

    MapIterator(MapNode* ptr = nullptr) : iter_(ptr) {}

    MapIterator& operator++() {
      if (!iter_) return *this;

      if (iter_->right) {
        iter_ = iter_->right;
        while (iter_->left) iter_ = iter_->left;
      } else {
        MapNode* parent = iter_->parent;
        while (parent && iter_ == parent->right) {
          iter_ = parent;
          parent = parent->parent;
        }
        iter_ = parent;
      }
      return *this;
    }

    MapIterator operator++(int) {
      MapIterator old = *this;
      ++(*this);
      return old;
    }

    MapIterator& operator--() {
      if (!iter_) return *this;

      if (iter_->left) {
        iter_ = iter_->left;
        while (iter_->right) iter_ = iter_->right;
      } else {
        MapNode* parent = iter_->parent;
        while (parent && iter_ == parent->left) {
          iter_ = parent;
          parent = parent->parent;
        }
        iter_ = parent;
      }
      return *this;
    }

    MapIterator operator--(int) {
      MapIterator old = *this;
      --(*this);
      return old;
    }

    pair<const Key&, T&> operator*() const {
      return {iter_->key, iter_->value};
    }

    bool operator==(const MapIterator& other) const {
      return (iter_ == other.iter_);
    }

    bool operator!=(const MapIterator& other) const {
      return !(iter_ == other.iter_);
    }

    // void printIt() {
    //   std::cout << "key: " << iter_->key << " value: " << iter_->value
    //             << std::endl;
    // }
    // // FOR DEBUG
  };  // class MapIterator

  class MapConstIterator {
   private:
    const MapNode* iter_;

   public:
    friend class S21Map<Key, T>;

    MapConstIterator(const MapNode* ptr = nullptr) : iter_(ptr) {}

    MapConstIterator(const MapIterator& it) : iter_(it.iter_) {}

    MapConstIterator& operator++() {
      if (!iter_) return *this;

      if (iter_->right) {
        iter_ = iter_->right;
        while (iter_->left) iter_ = iter_->left;
      } else {
        const MapNode* parent = iter_->parent;
        while (parent && iter_ == parent->right) {
          iter_ = parent;
          parent = parent->parent;
        }
        iter_ = parent;
      }
      return *this;
    }

    MapConstIterator operator++(int) {
      MapConstIterator old = *this;
      ++(*this);
      return old;
    }

    MapConstIterator& operator--() {
      if (!iter_) return *this;

      if (iter_->left) {
        iter_ = iter_->left;
        while (iter_->right) iter_ = iter_->right;
      } else {
        const MapNode* parent = iter_->parent;
        while (parent && iter_ == parent->left) {
          iter_ = parent;
          parent = parent->parent;
        }
        iter_ = parent;
      }
      return *this;
    }

    MapConstIterator operator--(int) {
      MapConstIterator old = *this;
      --(*this);
      return old;
    }

    pair<const Key&, const T&> operator*() const {
      return {iter_->key, iter_->value};
    }

    bool operator==(const MapConstIterator& other) const {
      return iter_ == other.iter_;
    }

    bool operator!=(const MapConstIterator& other) const {
      return !(*this == other);
    }
  };

  /**
   * @brief левосторонее вращение
   * правый ребенок - красный
   */
  MapNode* leftRotate(MapNode* current);

  /**
   * @brief правостороннее вращение
   * левый ребенок - красный
   */
  MapNode* rightRotate(MapNode* current);

  /**
   * @brief меняет цвета родителя и потомков
   */
  void flipColors(MapNode* node);

  /**
   * @brief balance leftRBT
   * если правая нода красная и левая нода черная - левосторонний поворот
   * если левая нода красная и левая нода левой ноды красная - правосторонний
   * поворот если левая нода красная и правосторонняя нода красная - свап цвета
   */
  MapNode* balanceTree(MapNode* node);

  /**
   * @brief return bool - true is red color
   */
  bool isRed(MapNode* node) const;

  MapNode* moveRedLeft(MapNode* node);

  MapNode* moveRedRight(MapNode* node);

  MapNode* eraseMin(MapNode* node);

  MapNode* eraseRecursive(MapNode* node, const Key& key);

  void clearRecursive(MapNode* node);

  MapNode* insert_recursive(MapNode* node, MapNode* parent,
                            const pair<Key, T>& value, bool& inserted);

  MapNode* copyTreeRecursive(MapNode* node, MapNode* parent);

 public:
  using key_type = Key;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

  /**
   * @brief default constructor, creates empty map
   */
  S21Map();

  /**
   * @brief initializer list constructor, creates the map initizialized using
   * std::initializer_list
   */
  S21Map(std::initializer_list<std::pair<const Key, T>> const& items);

  /**
   * @brief copy constructor
   */
  S21Map(const S21Map& other);

  /**
   * @brief move constructor
   */
  S21Map(S21Map&& m) noexcept;

  /**
   * @brief Destructor
   */
  ~S21Map() noexcept;

  /**
   * @brief clears the contents
   */
  void clear();

  /**
   * @brief assignment operator overload for moving object
   */
  S21Map& operator=(S21Map&& m) noexcept;

  /**
   * @brief returns an iterator to the beginnin
   */
  MapIterator begin();

  /**
   * @brief returns an iterator to the end
   */
  MapIterator end();

  /**
   * @brief returns an const iterator to the beginnin
   */
  MapConstIterator begin() const;

  /**
   * @brief returns an const iterator to the end
   */
  MapConstIterator end() const;

  /**
   * @brief inserts node and returns iterator to where the element is in the
   * container and bool denoting whether the insertion took place
   */
  pair<MapIterator, bool> insert(const pair<const Key, T>& value);

  /**
   * @brief inserts value by key and returns iterator to where the element is in
   * the container and bool denoting whether the insertion took place
   */
  pair<MapIterator, bool> insert(const Key& key, const T& obj);

  /**
   * @brief inserts an element or assigns to the current element if the key
   * already exists
   */
  pair<MapIterator, bool> insert_or_assign(const Key& key, const T& obj);

  /**
   * @brief finds an element by key
   */
  MapIterator find(const Key& key);

  /**
   * @brief erases element at pos
   * 1. спуск к ноде и балансировка
   * 1.1. если дерево пустое - возврат
   * 1.2 - создание красного пути к цели
   * - при движении влево:
   * если текущий узел и его левый ребенок черные && левый ребенок левого
   * ребенка черный - moveRedLeft инверсия цветов текущего узла и его детей если
   * у правого ребенка  есть красный левый ребенок: правый попорот правого
   * ребенка, левый поворот текущего узла, восстановление цветов
   *- при движении вправо:
   * если левый ребенок красный - правый поворот текущего узла
   * если текущий узел и его правый ребенок черные && левый ребенок правого
   * ребенка черные - moveRedRight: инверсия цветов текущего узла и его детей
   * если у левого ребенка есть красный левый ребенок - правый поворот текущего
   * узла и восстановление исходных цветов
   * 1.3 достигли удаляемого узла:
   * Лист или Узел с одним ребенком (лист - удаяем, один ребенок - заменяем)
   * Узел с двумя детьми:
   * находим минимальный узел в правом поддереве (преемник)
   * скопировать ключ и значение преемника в текущий узел
   * удалить преемника (delMinimum)
   * 2. Удаление минимума (delMinimum)
   * если левого ребенка нет - удалитьтекущий узел
   * если текущий узел и его левый ребенок черные && левый ребенок левого
   ребенка черные - MoveRedLeft
   * рекурсивный спуск влево, обратно - балансировка
   * 3. восходящая балансировка
   * после удаления на каждом уровне при подъеме из рекурсии
   3.1 восстановление левосторонности (если правый ребенок красный - левый
   поворот текущего узла)
   * 3.2 исправление двух красных слева (если левый ребенок и левый ребенок
   левого ребенка красные - правый поворот текущего узла)
   * 3.3 ликвидация временной 4-ноды:
   * если оба ребенка красные - перекрасить: текущий узел красный, оба ребенка
   черные
   * 4. финализация
   * проверка корня
   */
  void erase(MapIterator pos);

  /**
   * @brief swaps the contents
   */
  void swap(S21Map& other) noexcept;

  /**
   * @brief splices nodes from another container
   */
  void merge(S21Map& other);

  /**
   * @brief checks if there is an element with key equivalent to key in the
   * container
   */
  bool contains(const Key& key);

  /**
   * @brief checks whether the container is empty
   */
  bool empty();

  /**
   * @brief returns the number of elements
   */
  size_type size();

  /**
   * @brief returns the maximum possible number of elements
   */
  size_type max_size() const noexcept;

  /**
   * @brief access specified element with bounds checkin
   */
  T& at(const Key& key);

  /**
   * @brief access or insert specified element
   */
  T& operator[](const Key& key);

  // FOR DEBUG

  // void printTree() const;

  // void printTreeRecursive(MapNode* node, const std::string& prefix,
  //                         bool is_left) const;

  // FOR DEBUG

};  // class S21Map

}  // namespace s21

#include "s21_map.tpp"

#endif
