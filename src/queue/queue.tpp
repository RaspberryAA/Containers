#include "queue.h"

namespace s21 {

template <typename T>
queue<T>::queue() : m_size(0), data() {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : m_size(items.size()), data(items) {}

template <typename T>
queue<T>::queue(const queue &q) : m_size(q.m_size), data(q.data) {}

template <typename T>
queue<T>::queue(queue &&q) : m_size(0), data() {
  swap(q);
}

template <typename T>
queue<T>::~queue() {}

template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {
    swap(q);
  }
  return *this;
}

template <typename T>
queue<T> &queue<T>::operator=(const queue &q) {
  if (this != &q) {
    data = q.data;
    m_size = q.m_size;
  }
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  return data.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  return data.back();
}

template <typename T>
bool queue<T>::empty() {
  return data.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return data.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  data.push_back(value);
  ++m_size;
}

template <typename T>
void queue<T>::pop() {
  if (!empty()) {
    data.pop_front();
    --m_size;
  }
}

template <typename T>
void queue<T>::swap(queue &other) {
  using std::swap;
  swap(m_size, other.m_size);
  data.swap(other.data);
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  data.insert_many_back(std::forward<Args>(args)...);
  m_size += sizeof...(args);
}

}  // namespace s21