#include "vector.h"

using namespace s21;

template <typename T, typename Allocator>
bool vector<T, Allocator>::empty() {
  return m_size == 0;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() {
  return m_size;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type size) {
  reserve_more_capacity(size);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() {
  return m_capacity;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
  if (m_capacity > m_size) {
    value_type *buff = m_allocator.allocate(m_size);
    for (size_type i = 0; i < m_size; ++i) {
      m_allocator.construct(buff + i, *(arr + i));
    }
    m_allocator.deallocate(arr, m_capacity);
    arr = buff;
    m_capacity = m_size;
  }
}
