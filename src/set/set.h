#ifndef SET_H
#define SET_H

#define SET_NODE_PTR std::shared_ptr<SetNode<K>>
#define SET_NODE_SHARED std::make_shared<SetNode<K>>
#define SET_ITERATOR typename set<K, Compare>::iterator

#include "../rbTree/rbTree.h"
#include "../s21_containers.h"
#include "../vector/vector.h"

namespace s21 {

template <typename K>
class SetNode : public treeNode<SetNode<K>> {
 private:
  const K data;

 public:
  SetNode(K key) : treeNode<SetNode<K>>(), data(key) {}

  K getKey() { return data; }
  const K& getData() { return data; };
  K* getPtr() { return &data; }
};

template <typename K, typename Compare>
class setIterator {
 private:
  std::shared_ptr<RBTree<SetNode<K>, Compare>> tree;
  SET_NODE_PTR node;

 public:
  setIterator(std::shared_ptr<RBTree<SetNode<K>, Compare>> tree,
              SET_NODE_PTR node)
      : tree(tree), node(node) {}

  const K& operator*() { return node->getData(); }

  const K* operator->() { return &(node->getData()); }

  bool operator==(const setIterator& other) const {
    return this->node == other.node;
  }

  bool operator!=(const setIterator& other) const {
    return this->node != other.node;
  }

  setIterator& operator++() {
    node = tree->nextElement(node);
    return *this;
  }

  setIterator operator++(int) {
    setIterator temp = *this;
    node = tree->nextElement(node);
    return temp;
  }

  setIterator& operator--() {
    node = tree->prevElement(node);
    return *this;
  }

  setIterator operator--(int) {
    setIterator temp = *this;
    node = tree->prevElement(node);
    return temp;
  }
};

template <typename K, typename Compare = std::less<K>>
class set {
 private:
  size_t m_size;
  std::shared_ptr<RBTree<SetNode<K>, Compare>> tree;

 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = setIterator<K, Compare>;
  using const_iterator = const setIterator<K, Compare>;
  using size_type = size_t;

 private:
  void allocateIfNull();

 public:
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();
  set& operator=(set&& s);

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
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  bool contains(const K& key);
  iterator find(const K& key);
};

}  // namespace s21

#include "setImpl.tpp"

#endif