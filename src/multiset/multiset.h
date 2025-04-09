#ifndef MULTISET_H
#define MULTISET_H

#define MULTISET_ITERATOR typename multiset<K, Compare>::iterator

#include "../rbTree/rbTree.h"
#include "../s21_containersplus.h"
#include "../vector/vector.h"

namespace s21 {

template <typename K, typename Compare = std::less<K>>
class multiset {
 private:
  size_t m_size;
  std::shared_ptr<RBTree<SetNode<K>, Compare>> tree;
  Compare compare_;

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
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  multiset& operator=(multiset&& ms);

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
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  template <typename... Args>
  vector<iterator> insert_many(Args&&... args);

  bool contains(const K& key);
  iterator find(const K& key);
  size_type count(const K& key);
  std::pair<iterator, iterator> equal_range(const K& key);
  iterator lower_bound(const K& key);
  iterator upper_bound(const K& key);
};

}  // namespace s21

#include "multisetImpl.tpp"

#endif