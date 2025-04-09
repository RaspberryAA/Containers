#include "list.h"
namespace s21 {

template <typename T>
list<T>::list() : m_size(0), head(nullptr), tail(nullptr) {}

template <typename T>
list<T>::list(size_type n) : list() {
  while (n-- > 0) push_back(T());
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items)
    : m_size(0), head(nullptr), tail(nullptr) {
  for (auto const& item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& other) : m_size(0), head(nullptr), tail(nullptr) {
  for (auto const& item : other) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(list&& other)
    : m_size(other.m_size), head(other.head), tail(other.tail) {
  other.m_size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (empty()) throw std::out_of_range("list::front(): empty list");
  return head->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (empty()) throw std::out_of_range("list::back(): empty list");
  return tail->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() const {
  return Iterator<T>(head);
}

template <typename T>
typename list<T>::iterator list<T>::end() const {
  return Iterator<T>(nullptr);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == begin()) {
    push_front(value);
    pos = begin();
  } else if (pos == end()) {
    push_back(value);
    pos = end();
  } else {
    auto newNode = new listNode<T>{value, nullptr, nullptr};
    newNode->prev = pos.getNode()->prev;
    newNode->next = pos.getNode();
    pos.getNode()->prev->next = newNode;
    pos.getNode()->prev = newNode;
    ++m_size;
  }
  return pos;
}

template <typename T>
bool list<T>::empty() {
  return m_size == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return m_size;
}

template <typename T>
void list<T>::clear() {
  auto current = head;
  while (current) {
    auto next = current->next;
    delete current;
    current = next;
  }
  head = tail = nullptr;
  m_size = 0;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == end()) return;

  listNode<T>* nodeToRemove = pos.getNode();

  if (nodeToRemove->prev) {
    nodeToRemove->prev->next = nodeToRemove->next;
  } else {
    head = nodeToRemove->next;
  }

  if (nodeToRemove->next) {
    nodeToRemove->next->prev = nodeToRemove->prev;
  } else {
    tail = nodeToRemove->prev;
  }

  delete nodeToRemove;
  --m_size;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  auto newNode = new listNode<T>{value, nullptr, tail};
  if (tail) {
    tail->next = newNode;
  } else {
    head = newNode;
  }
  tail = newNode;
  ++m_size;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) throw std::out_of_range("list::pop_back(): empty list");
  erase(tail);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  auto newNode = new listNode<T>{value, head, nullptr};
  if (head) {
    head->prev = newNode;
  } else {
    tail = newNode;
  }
  head = newNode;
  ++m_size;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) throw std::out_of_range("list::pop_front(): empty list");
  erase(head);
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(m_size, other.m_size);
}

template <typename T>
void list<T>::merge(list& other) {
  if (&other == this) return;
  if (other.empty()) return;
  if (empty()) {
    swap(other);
    return;
  }
  tail->next = other.head;
  other.head->prev = tail;
  tail = other.tail;
  m_size += other.m_size;
  other.head = other.tail = nullptr;
  other.m_size = 0;
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
  }
}

template <typename T>
void list<T>::reverse() {
  listNode<T>* current = head;
  listNode<T>* prev = nullptr;
  listNode<T>* next = nullptr;
  while (current) {
    next = current->next;
    current->next = prev;
    current->prev = next;
    prev = current;
    current = next;
  }
  std::swap(head, tail);
}

template <typename T>
void list<T>::unique() {
  if (m_size < 2) return;
  auto current = head;
  while (current->next) {
    if (current->data == current->next->data) {
      erase(current->next);
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (m_size < 2) return;
  for (auto i = begin(); i != end(); ++i) {
    for (auto j = i; j != end(); ++j) {
      if (*i > *j) std::swap(*i, *j);
    }
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it = iterator(pos.getNode());
  ((void)insert(it++, std::forward<Args>(args)), ...);
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  (push_front(std::forward<Args>(args)), ...);
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    listNode<T>* current = other.head;
    while (current) {
      push_back(current->data);
      current = current->next;
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    m_size = other.m_size;
    head = other.head;
    tail = other.tail;
    other.m_size = 0;
    other.head = nullptr;
    other.tail = nullptr;
  }
  return *this;
}

}  // namespace s21