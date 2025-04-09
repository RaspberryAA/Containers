#include "multiset.h"

using namespace s21;

template <typename K, typename Compare>
void multiset<K, Compare>::allocateIfNull() {
  if (tree == nullptr) {
    tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
  }
}

template <typename K, typename Compare>
multiset<K, Compare>::multiset() {
  m_size = 0;
  tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
}

template <typename K, typename Compare>
multiset<K, Compare>::multiset(std::initializer_list<value_type> const &items) {
  m_size = 0;
  tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->insert(*it);
  }
}

template <typename K, typename Compare>
multiset<K, Compare>::multiset(const multiset &m) {
  tree = std::make_shared<RBTree<SetNode<K>, Compare>>();
  m_size = 0;
  for (auto iter = m.begin(); iter != m.end(); ++iter) {
    this->insert(*iter);
  }
}

template <typename K, typename Compare>
multiset<K, Compare>::multiset(multiset &&m) : m_size(m.m_size), tree(m.tree) {
  m.tree = nullptr;
  m.m_size = 0;
}

template <typename K, typename Compare>
multiset<K, Compare>::~multiset() {
  m_size = 0;
  tree = nullptr;
}

template <typename K, typename Compare>
multiset<K, Compare> &multiset<K, Compare>::operator=(multiset &&m) {
  if (this != &m) {
    tree = m.tree;
    m_size = m.m_size;
    m.tree = nullptr;
    m.m_size = 0;
  }
  return *this;
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::begin() {
  return setIterator<K, Compare>(tree, tree->minimum(tree->getRoot()));
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::end() {
  return setIterator<K, Compare>(nullptr, nullptr);
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::begin() const {
  return setIterator<K, Compare>(tree, tree->minimum(tree->getRoot()));
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::end() const {
  return setIterator<K, Compare>(nullptr, nullptr);
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::rbegin() {
  return setIterator<K, Compare>(tree, tree->maximum(tree->getRoot()));
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::rend() {
  return setIterator<K, Compare>(nullptr, nullptr);
}

template <typename K, typename Compare>
bool multiset<K, Compare>::empty() {
  return m_size == 0;
}

template <typename K, typename Compare>
typename multiset<K, Compare>::size_type multiset<K, Compare>::size() {
  return m_size;
}

template <typename K, typename Compare>
typename multiset<K, Compare>::size_type multiset<K, Compare>::max_size() {
  // how should be
  return std::numeric_limits<size_type>::max() /
         (sizeof(value_type) + sizeof(SetNode<K>));
  // like original
  // return std::numeric_limits<size_type>::max() / (sizeof(value_type) * 10);
}

template <typename K, typename Compare>
void multiset<K, Compare>::clear() {
  tree = nullptr;
  m_size = 0;
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::insert(const value_type &value) {
  allocateIfNull();
  SET_NODE_PTR n = SET_NODE_SHARED(value);
  tree->insert(n);
  ++m_size;
  MULTISET_ITERATOR iter(tree, n);
  return iter;
}

template <typename K, typename Compare>
void multiset<K, Compare>::erase(iterator pos) {
  SET_NODE_PTR s = SET_NODE_SHARED(*pos);
  if (tree->del(s)) {
    --m_size;
  }
}

template <typename K, typename Compare>
void multiset<K, Compare>::swap(multiset &other) {
  std::swap(other, *this);
}

template <typename K, typename Compare>
void multiset<K, Compare>::merge(multiset &other) {
  for (auto iter = other.begin(); iter != other.end(); ++iter) {
    this->insert(*iter);
  }
  other.clear();
}

template <typename K, typename Compare>
bool multiset<K, Compare>::contains(const K &key) {
  bool ret = true;
  SET_NODE_PTR s = tree->search(SET_NODE_SHARED(key));
  if (s == nullptr) {
    ret = false;
  }
  return ret;
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::find(const K &key) {
  iterator it = this->end();
  SET_NODE_PTR s = tree->search(SET_NODE_SHARED(key));
  if (s != nullptr) {
    it = setIterator<K, Compare>(tree, s);
  }
  return it;
}

template <typename K, typename Compare>
typename multiset<K, Compare>::size_type multiset<K, Compare>::count(
    const K &key) {
  size_type ret = 0;
  iterator s = find(key);
  while (s != this->end() && !compare_(*s, key) && !compare_(key, *s)) {
    ++s;
    ++ret;
  }
  return ret;
}

template <typename K, typename Compare>
std::pair<MULTISET_ITERATOR, MULTISET_ITERATOR>
multiset<K, Compare>::equal_range(const K &key) {
  iterator s1 = find(key);
  iterator s2 = s1;
  while (s2 != this->end() && !(compare_(*s1, *s2) || compare_(*s2, *s1))) {
    ++s2;
  }
  auto ret = std::make_pair(s1, s2);
  return ret;
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::lower_bound(const K &key) {
  iterator it = this->begin();
  while (it != this->end() &&
         !(compare_(key, *it) || !(compare_(*it, key) || compare_(key, *it)))) {
    ++it;
  }
  return it;
}

template <typename K, typename Compare>
MULTISET_ITERATOR multiset<K, Compare>::upper_bound(const K &key) {
  iterator it = this->begin();
  while (it != this->end() &&
         (compare_(*it, key) || !(compare_(*it, key) || compare_(key, *it)))) {
    ++it;
  }
  return it;
}

template <typename K, typename Compare>
template <typename... Args>
vector<MULTISET_ITERATOR> multiset<K, Compare>::insert_many(Args &&...args) {
  s21::vector<iterator> res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}
