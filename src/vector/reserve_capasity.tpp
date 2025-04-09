#include "vector.h"

using namespace s21;

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve_more_capacity(size_type size) {
  if (size > m_capacity) {
    value_type *buff = m_allocator.allocate(size);
    for (size_type i = 0; i < m_size; ++i) {
      m_allocator.construct(buff + i, arr[i]);
      m_allocator.destroy(arr + i);
    }
    m_allocator.deallocate(arr, m_capacity);
    arr = buff;
    m_capacity = size;
  }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::new_arr() {
  if (arr == nullptr) {
    arr = m_allocator.allocate(INIT_SIZE);
    m_capacity = INIT_SIZE;
    m_size = 0;
  }
}
