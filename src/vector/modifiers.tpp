#include "vector.h"

using namespace s21;

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
    iterator pos, const_reference value) {
  new_arr();
  size_type index = pos - begin();
  if (m_size == m_capacity) {
    reserve_more_capacity(m_capacity * 2);
  }
  m_allocator.construct(arr + m_size, value_type{});
  for (size_type i = m_size; i > index; --i) {
    arr[i] = arr[i - 1];
  }
  arr[index] = value;
  ++m_size;
  return arr + index;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::clear() {
  for (size_type i = 0; i < m_size; ++i) {
    m_allocator.destroy(arr + i);
  }
  m_size = 0U;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const_reference v) {
  new_arr();
  if (m_size == m_capacity) {
    reserve_more_capacity(m_capacity * 2);
  }
  m_allocator.construct(arr + m_size, v);
  ++m_size;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
  m_allocator.destroy(arr + m_size - 1);
  --m_size;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) {
  std::swap(other, *this);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::erase(iterator pos) {
  if (pos >= begin() && pos < end()) {
    for (T* ptr = pos; ptr < end() - 1; ptr++) {
      *ptr = *(ptr + 1);
    }
    --m_size;
  }
}

template <typename T, typename Allocator>
template <typename... Args>
void vector<T, Allocator>::insert_many_back(Args&&... args) {
  (this->push_back(std::forward<Args>(args)), ...);
}

template <typename T, typename Allocator>
template <typename... Args>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert_many(
    const_iterator pos, Args&&... args) {
  size_t offset = pos - this->begin();
  iterator tmp = (iterator)pos;
  if constexpr (sizeof...(args) != 0) {
    for (const auto p : {args...}) {
      this->insert(this->begin() + offset, p);
      ++offset;
    }
    ++tmp;
  }
  return tmp - sizeof...(args);
}
