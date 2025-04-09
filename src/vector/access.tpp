#include "vector.h"

using namespace s21;

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type i) {
  if (i >= m_size) {
    throw std::out_of_range("Index out of range");
  }
  return arr[i];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](
    size_type i) {
  return arr[i];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() {
  return arr[0];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() {
  return arr[m_size - 1];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::data() {
  return arr;
}
