#ifndef MAP_H
#define MAP_H

#define MAP_NODE_PTR std::shared_ptr<MapNode<K, V>>
#define MAP_NODE_SHARED std::make_shared<MapNode<K, V>>
#define MAP_ITERATOR typename map<K, V, Compare>::iterator
#define MAP_TEMPLATE template <typename K, typename V, typename Compare>

#include "../rbTree/rbTree.h"
#include "../s21_containers.h"
#include "../vector/vector.h"

namespace s21 {

template <typename K, typename V>
class MapNode : public treeNode<MapNode<K, V>> {
 private:
  std::pair<const K, V> data;

 public:
  MapNode(K key, V value) : treeNode<MapNode<K, V>>(), data(key, value) {}

  V getValue() { return data.second; }
  K getKey() { return data.first; }
  std::pair<const K, V>& getData() { return data; };
  V* getPtr() { return &data.second; }
  void setValue(V v) { data.second = v; }
};

template <typename K, typename V, typename Compare>
class mapIterator {
 private:
  std::shared_ptr<RBTree<MapNode<K, V>, Compare>> tree;
  MAP_NODE_PTR node;

 public:
  mapIterator(std::shared_ptr<RBTree<MapNode<K, V>, Compare>> tree,
              MAP_NODE_PTR node)
      : tree(tree), node(node) {}

  std::pair<const K, V>& operator*() { return node->getData(); }

  std::pair<const K, V>* operator->() { return &(node->getData()); }

  bool operator==(const mapIterator& other) const {
    return this->node == other.node;
  }

  bool operator!=(const mapIterator& other) const {
    return this->node != other.node;
  }

  mapIterator& operator++() {
    node = tree->nextElement(node);
    return *this;
  }

  mapIterator operator++(int) {
    mapIterator temp = *this;
    node = tree->nextElement(node);
    return temp;
  }

  mapIterator& operator--() {
    node = tree->prevElement(node);
    return *this;
  }

  mapIterator operator--(int) {
    mapIterator temp = *this;
    node = tree->prevElement(node);
    return temp;
  }
};

template <typename K, typename V, typename Compare = std::less<K>>
class map {
 private:
  size_t m_size;
  std::shared_ptr<RBTree<MapNode<K, V>, Compare>> tree;

 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = mapIterator<K, V, Compare>;
  using const_iterator = const mapIterator<K, V, Compare>;
  using size_type = size_t;

 private:
  void allocateIfNull();

 public:
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(map&& m);

  V& at(const K& key);
  V& operator[](const K& key);

  iterator begin();
  iterator end();
  iterator begin() const;
  iterator end() const;
  iterator rbegin();
  iterator rend();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert_or_assign(const K& key, const V& obj);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const K& key, const V& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  vector<std::pair<iterator, bool>> insert_many(
      std::initializer_list<std::pair<K, V>> args);

  bool contains(const K& key);
};

}  // namespace s21

#include "mapImpl.tpp"

#endif