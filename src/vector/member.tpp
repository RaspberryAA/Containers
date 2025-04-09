namespace s21 {
template <typename T, typename Allocator>
vector<T, Allocator>::vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type n) {
  arr = m_allocator.allocate(n);
  m_capacity = n;
  m_size = 0;
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector &v) {
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  arr = m_allocator.allocate(m_capacity);
  for (size_type i = 0; i < m_size; ++i) {
    m_allocator.construct(arr + i, v.arr[i]);
  }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector &&v)
    : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
  v.arr = nullptr;
  v.m_size = 0;
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector() {
  this->clear();
  m_allocator.deallocate(arr, m_capacity);
  arr = nullptr;
  m_capacity = 0U;
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<value_type> const &items) {
  m_size = items.size();
  m_capacity = items.size() * 2;
  arr = m_allocator.allocate(m_capacity);
  auto it = items.begin();
  for (size_type i = 0; i < m_size; ++i) {
    m_allocator.construct(arr + i, *(it++));
  }
}

template <typename T, typename Allocator>
vector<T, Allocator> &vector<T, Allocator>::operator=(vector &&v) {
  if (this != &v) {
    for (size_type i = 0; i < m_size; ++i) {
      m_allocator.destroy(&arr[i]);
    }
    m_allocator.deallocate(arr, m_capacity);
    this->m_capacity = v.m_capacity;
    this->m_size = v.m_size;
    this->arr = v.arr;
    v.arr = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }
  return *this;
}
}  // namespace s21