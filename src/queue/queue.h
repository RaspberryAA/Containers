#ifndef QUEUE_H
#define QUEUE_H

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class queue {
 private:
  size_t m_size;
  list<T> data;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  queue &operator=(queue &&q);
  queue &operator=(const queue &q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "queue.tpp"

#endif