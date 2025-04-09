#include "map.h"

using namespace s21;

MAP_TEMPLATE
void map<K, V, Compare>::allocateIfNull() {
  if (tree == nullptr) {
    tree = std::make_shared<RBTree<MapNode<K, V>, Compare>>();
  }
}

MAP_TEMPLATE
map<K, V, Compare>::map() {
  m_size = 0;
  tree = std::make_shared<RBTree<MapNode<K, V>, Compare>>();
}

MAP_TEMPLATE
map<K, V, Compare>::map(std::initializer_list<value_type> const &items) {
  m_size = 0;
  tree = std::make_shared<RBTree<MapNode<K, V>, Compare>>();
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->insert(*it);
  }
}

MAP_TEMPLATE
map<K, V, Compare>::map(const map &m) {
  tree = std::make_shared<RBTree<MapNode<K, V>, Compare>>();
  m_size = 0;
  for (auto iter = m.begin(); iter != m.end(); ++iter) {
    this->insert(*iter);
  }
}

MAP_TEMPLATE
map<K, V, Compare>::map(map &&m) : m_size(m.m_size), tree(m.tree) {
  m.tree = nullptr;
  m.m_size = 0;
}

MAP_TEMPLATE
map<K, V, Compare>::~map() {
  m_size = 0;
  tree = nullptr;
}

MAP_TEMPLATE
map<K, V, Compare> &map<K, V, Compare>::operator=(map &&m) {
  if (this != &m) {
    tree = m.tree;
    m_size = m.m_size;
    m.tree = nullptr;
    m.m_size = 0;
  }
  return *this;
}

MAP_TEMPLATE
V &map<K, V, Compare>::at(const K &key) {
  MAP_NODE_PTR s = tree->search(MAP_NODE_SHARED(key, V{}));
  if (s == nullptr) {
    throw std::out_of_range("Element not found");
  }
  return *(s->getPtr());
}

MAP_TEMPLATE
V &map<K, V, Compare>::operator[](const K &key) {
  MAP_NODE_PTR t = MAP_NODE_SHARED(key, V{});
  MAP_NODE_PTR s = tree->search(t);
  V *ret = nullptr;
  if (s == nullptr) {
    tree->insert(t);
    m_size++;
    ret = t->getPtr();
  } else {
    ret = s->getPtr();
  }
  return *ret;
}

MAP_TEMPLATE
MAP_ITERATOR map<K, V, Compare>::begin() {
  return mapIterator<K, V, Compare>(tree, tree->minimum(tree->getRoot()));
}

MAP_TEMPLATE
MAP_ITERATOR map<K, V, Compare>::end() {
  return mapIterator<K, V, Compare>(nullptr, nullptr);
}

MAP_TEMPLATE
MAP_ITERATOR map<K, V, Compare>::begin() const {
  return mapIterator<K, V, Compare>(tree, tree->minimum(tree->getRoot()));
}

MAP_TEMPLATE
MAP_ITERATOR map<K, V, Compare>::end() const {
  return mapIterator<K, V, Compare>(nullptr, nullptr);
}

MAP_TEMPLATE
MAP_ITERATOR map<K, V, Compare>::rbegin() {
  return mapIterator<K, V, Compare>(tree, tree->maximum(tree->getRoot()));
}

MAP_TEMPLATE
MAP_ITERATOR map<K, V, Compare>::rend() {
  return mapIterator<K, V, Compare>(nullptr, nullptr);
}

MAP_TEMPLATE
bool map<K, V, Compare>::empty() { return m_size == 0; }

MAP_TEMPLATE
typename map<K, V, Compare>::size_type map<K, V, Compare>::size() {
  return m_size;
}

MAP_TEMPLATE
typename map<K, V, Compare>::size_type map<K, V, Compare>::max_size() {
  // how should be
  return std::numeric_limits<size_type>::max() /
         (sizeof(value_type) + sizeof(MapNode<K, V>));
  // like original
  // return std::numeric_limits<size_type>::max() / (sizeof(value_type) * 10);
}

MAP_TEMPLATE
void map<K, V, Compare>::clear() {
  tree = nullptr;
  m_size = 0;
}

MAP_TEMPLATE
std::pair<MAP_ITERATOR, bool> map<K, V, Compare>::insert(
    const value_type &value) {
  allocateIfNull();
  MAP_NODE_PTR s = tree->search(MAP_NODE_SHARED(value.first, V{}));
  MAP_ITERATOR iter(tree, s);
  std::pair<MAP_ITERATOR, bool> ret(iter, false);
  if (s == nullptr) {
    MAP_NODE_PTR n = MAP_NODE_SHARED(value.first, value.second);
    tree->insert(n);
    ++m_size;
    ret.first = MAP_ITERATOR(tree, n);
    ret.second = true;
  }
  return ret;
}

MAP_TEMPLATE
std::pair<MAP_ITERATOR, bool> map<K, V, Compare>::insert(const K &key,
                                                         const V &obj) {
  return insert(std::make_pair(key, obj));
}

MAP_TEMPLATE
std::pair<MAP_ITERATOR, bool> map<K, V, Compare>::insert_or_assign(
    const K &key, const V &obj) {
  std::pair<MAP_ITERATOR, bool> ret = insert(std::make_pair(key, obj));
  if (!ret.second) {
    ret.first->second = obj;
  }
  return ret;
}

MAP_TEMPLATE
void map<K, V, Compare>::erase(iterator pos) {
  MAP_NODE_PTR s = MAP_NODE_SHARED(pos->first, pos->second);
  if (tree->del(s)) {
    --m_size;
  }
}

MAP_TEMPLATE
void map<K, V, Compare>::swap(map &other) { std::swap(other, *this); }

MAP_TEMPLATE
void map<K, V, Compare>::merge(map &other) {
  for (auto iter = other.begin(); iter != other.end(); ++iter) {
    this->insert(iter->first, iter->second);
  }
  other.clear();
}

MAP_TEMPLATE
bool map<K, V, Compare>::contains(const K &key) {
  bool ret = true;
  MAP_NODE_PTR s = tree->search(MAP_NODE_SHARED(key, V{}));
  if (s == nullptr) {
    ret = false;
  }
  return ret;
}

MAP_TEMPLATE
template <typename... Args>
vector<std::pair<MAP_ITERATOR, bool>> map<K, V, Compare>::insert_many(
    Args &&...args) {
  s21::vector<std::pair<iterator, bool>> res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}

MAP_TEMPLATE
vector<std::pair<MAP_ITERATOR, bool>> map<K, V, Compare>::insert_many(
    std::initializer_list<std::pair<K, V>> args) {
  s21::vector<std::pair<iterator, bool>> res;
  for (const auto &pair : args) {
    res.push_back(this->insert(pair));
  }
  return res;
}
