#include "set.h"

using namespace s21;

template <typename K, typename Compare>
void set<K, Compare>::allocateIfNull() {
  if (tree == nullptr) {
    tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
  }
}

template <typename K, typename Compare>
set<K, Compare>::set() {
  m_size = 0;
  tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
}

template <typename K, typename Compare>
set<K, Compare>::set(std::initializer_list<value_type> const &items) {
  m_size = 0;
  tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->insert(*it);
  }
}

template <typename K, typename Compare>
set<K, Compare>::set(const set &m) {
  tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
  m_size = 0;
  for (auto iter = m.begin(); iter != m.end(); ++iter) {
    this->insert(*iter);
  }
}

template <typename K, typename Compare>
set<K, Compare>::set(set &&m) : m_size(m.m_size), tree(m.tree) {
  m.tree = nullptr;
  m.m_size = 0;
}

template <typename K, typename Compare>
set<K, Compare>::~set() {
  m_size = 0;
  tree = nullptr;
}

template <typename K, typename Compare>
set<K, Compare> &set<K, Compare>::operator=(set &&m) {
  if (this != &m) {
    tree = m.tree;
    m_size = m.m_size;
    m.tree = nullptr;
    m.m_size = 0;
  }
  return *this;
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::begin() {
  return setIterator<K, Compare>(tree, tree->minimum(tree->getRoot()));
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::end() {
  return setIterator<K, Compare>(nullptr, nullptr);
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::begin() const {
  return setIterator<K, Compare>(tree, tree->minimum(tree->getRoot()));
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::end() const {
  return setIterator<K, Compare>(nullptr, nullptr);
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::rbegin() {
  return setIterator<K, Compare>(tree, tree->maximum(tree->getRoot()));
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::rend() {
  return setIterator<K, Compare>(nullptr, nullptr);
}

template <typename K, typename Compare>
bool set<K, Compare>::empty() {
  return m_size == 0;
}

template <typename K, typename Compare>
typename set<K, Compare>::size_type set<K, Compare>::size() {
  return m_size;
}

template <typename K, typename Compare>
typename set<K, Compare>::size_type set<K, Compare>::max_size() {
  // how should be
  return std::numeric_limits<size_type>::max() /
         (sizeof(value_type) + sizeof(SetNode<K>));
  // like original
  // return std::numeric_limits<size_type>::max() / (sizeof(value_type) * 10);
}

template <typename K, typename Compare>
void set<K, Compare>::clear() {
  tree = nullptr;
  m_size = 0;
}

template <typename K, typename Compare>
std::pair<SET_ITERATOR, bool> set<K, Compare>::insert(const value_type &value) {
  allocateIfNull();
  SET_NODE_PTR s = tree->search(SET_NODE_SHARED(value));
  SET_ITERATOR iter(tree, s);
  std::pair<SET_ITERATOR, bool> ret(iter, false);
  if (s == nullptr) {
    SET_NODE_PTR n = SET_NODE_SHARED(value);
    tree->insert(n);
    ++m_size;
    ret.first = SET_ITERATOR(tree, n);
    ret.second = true;
  }
  return ret;
}

template <typename K, typename Compare>
void set<K, Compare>::erase(iterator pos) {
  SET_NODE_PTR s = SET_NODE_SHARED(*pos);
  if (tree->del(s)) {
    --m_size;
  }
}

template <typename K, typename Compare>
void set<K, Compare>::swap(set &other) {
  std::swap(other, *this);
}

template <typename K, typename Compare>
void set<K, Compare>::merge(set &other) {
  for (auto iter = other.begin(); iter != other.end(); ++iter) {
    this->insert(*iter);
  }
  other.clear();
}

template <typename K, typename Compare>
bool set<K, Compare>::contains(const K &key) {
  bool ret = true;
  SET_NODE_PTR s = tree->search(SET_NODE_SHARED(key));
  if (s == nullptr) {
    ret = false;
  }
  return ret;
}

template <typename K, typename Compare>
SET_ITERATOR set<K, Compare>::find(const K &key) {
  iterator it = this->end();
  SET_NODE_PTR s = tree->search(SET_NODE_SHARED(key));
  if (s != nullptr) {
    it = setIterator<K, Compare>(tree, s);
  }
  return it;
}

template <typename K, typename Compare>
template <typename... Args>
vector<std::pair<SET_ITERATOR, bool>> set<K, Compare>::insert_many(
    Args &&...args) {
  s21::vector<std::pair<iterator, bool>> res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}
