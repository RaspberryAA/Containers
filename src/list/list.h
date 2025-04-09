#ifndef LIST_H
#define LIST_H

#include "../s21_containers.h"

namespace s21 {

template <typename T>
struct listNode {
  T data;
  listNode *next;
  listNode *prev;
};

template <typename T>
class Iterator {
 private:
  listNode<T> *node;

 public:
  Iterator() : node(nullptr){};
  Iterator(listNode<T> *node) : node(node){};

  bool operator==(const Iterator &other) const {
    return this->node == other.node;
  }

  bool operator!=(const Iterator &other) const {
    return this->node != other.node;
  }

  Iterator &operator++() {
    node = node->next;
    return *this;
  }

  Iterator operator++(int) {
    Iterator temp = *this;
    node = node->next;
    return temp;
  }

  Iterator &operator--() {
    node = node->prev;
    return *this;
  }

  Iterator operator--(int) {
    Iterator temp = *this;
    node = node->prev;
    return temp;
  }

  T &operator*() { return node->data; }

  listNode<T> *getNode() const { return node; }
};

template <typename T>
class list {
 private:
  size_t m_size;
  listNode<T> *head;
  listNode<T> *tail;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Iterator<T>;
  using const_iterator = const Iterator<T>;
  using size_type = size_t;

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();

  iterator begin() const;
  iterator end() const;
  iterator insert(iterator pos, const_reference value);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size() const;
  size_type max_size();

  void clear();
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

  list &operator=(const list &other);
  list &operator=(list &&other) noexcept;
};

}  // namespace s21

#include "list.tpp"

#endif