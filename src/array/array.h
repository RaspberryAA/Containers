#ifndef ARRAY_H
#define ARRAY_H

#include "../s21_containersplus.h"

namespace s21 {

template <typename T, std::size_t N>
class array {
 private:
  T *arr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array &operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();
  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();
  void swap(array &other);
  void fill(const_reference value);
};

}  // namespace s21

#include "arrayImpl.tpp"

#endif