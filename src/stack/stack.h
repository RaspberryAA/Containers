#ifndef STACK_H
#define STACK_H

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class stack {
 private:
  size_t m_size;
  list<T> data;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  stack &operator=(const stack &s);
  stack &operator=(stack &&s);

  // access
  const_reference top();
  // capacity
  bool empty();
  size_type size();
  // modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21

#include "stack.tpp"

#endif