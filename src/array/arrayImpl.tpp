#include "array.h"

template <typename T, std::size_t N>
array<T, N>::array() {
  arr = new value_type[N]{};
}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("List size more than array size");
  }
  arr = new value_type[N]{};
  auto it = items.begin();
  for (size_type i = 0; i < items.size(); ++i) {
    arr[i] = *(it++);
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  arr = new value_type[N]{};
  std::copy(a.begin(), a.end(), arr);
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  arr = new value_type[N]{};
  std::move(a.begin(), a.end(), arr);
}

template <typename T, std::size_t N>
array<T, N>::~array() {
  delete[] arr;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  std::copy(a.begin(), a.end(), arr);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos > N) {
    throw std::out_of_range("Wrong size");
  }
  return arr[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return arr[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return *arr;
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return arr[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return arr + N;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() const {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() const {
  return arr + N;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return N;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap(arr, other.arr);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    arr[i] = value;
  }
}
