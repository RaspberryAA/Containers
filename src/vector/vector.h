#ifndef VECTOR_H
#define VECTOR_H

#define INIT_SIZE 16

#include "../s21_containers.h"

namespace s21 {

template <typename T, typename Allocator = std::allocator<T>>
class vector {
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;
  Allocator m_allocator;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  void reserve_more_capacity(size_t size);
  void new_arr();

 public:
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  explicit vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);
  reference at(size_type i);
  const_reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();
  // vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  // vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  iterator begin();
  iterator end();
};

}  // namespace s21

#include "access.tpp"
#include "capacity.tpp"
#include "iterators.tpp"
#include "member.tpp"
#include "modifiers.tpp"
#include "reserve_capasity.tpp"

#endif