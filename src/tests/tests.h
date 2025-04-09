#ifndef VECTOR_TESTS_H
#define VECTOR_TESTS_H

#include <gtest/gtest.h>

#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

template <typename T>
void assert_vectors(s21::vector<T>& s21_, std::vector<T>& original) {
  for (size_t i = 0; i < original.size(); i++) {
    EXPECT_EQ(s21_.at(i), original.at(i));
  }
}

#endif