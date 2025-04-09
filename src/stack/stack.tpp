namespace s21 {

template <typename T>
stack<T>::stack() : m_size(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) : m_size(0) {
  for (const auto &item : items) {
    push(item);
  }
}

template <typename T>
stack<T>::stack(const stack &s) : m_size(s.m_size), data(s.data) {}

template <typename T>
stack<T>::stack(stack &&s) : m_size(0), data() {
  swap(s);
}

template <typename T>
stack<T>::~stack() {}

template <typename T>
stack<T> &stack<T>::operator=(const stack &s) {
  if (this != &s) {
    stack temp(s);
    swap(temp);
  }
  return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&s) {
  if (this != &s) {
    swap(s);
  }
  return *this;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  return data.front();
}

template <typename T>
bool stack<T>::empty() {
  return m_size == 0;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return m_size;
}

template <typename T>
void stack<T>::push(const_reference value) {
  data.push_front(value);
  ++m_size;
}

template <typename T>
void stack<T>::pop() {
  if (!empty()) {
    data.pop_front();
    --m_size;
  }
}

template <typename T>
void stack<T>::swap(stack &other) {
  using std::swap;
  swap(m_size, other.m_size);
  data.swap(other.data);
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  data.insert_many_front(std::forward<Args>(args)...);
  m_size += sizeof...(args);
}

}  // namespace s21
