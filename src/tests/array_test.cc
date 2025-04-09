#include "tests.h"

TEST(arrayTest1, accessTest) {
  std::array<int, 10> original = {1, 2, 3, 4, 5};
  s21::array<int, 10> s21 = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21.front(), original.front());
  EXPECT_EQ(s21.back(), original.back());
  int *a = s21.data();
  int *b = original.data();
  for (size_t i = 0; i < s21.size(); i++) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(arrayTest2, accessTest) {
  std::array<int, 10> original = {0};
  s21::array<int, 10> s21;
  EXPECT_EQ(original.size(), s21.size());
  for (size_t i = 0; i < s21.size(); i++) {
    EXPECT_EQ(s21.at(i), original.at(i));
  }
}

TEST(arrayTest3, accessTest) {
  std::array<int, 20> original2 = {20, 20};
  std::array<int, 20> original;
  s21::array<int, 20> s21;
  s21::array<int, 20> s212 = {20, 20};
  original.swap(original2);
  s21.swap(s212);
  EXPECT_EQ(original[0], s21[0]);
  for (size_t i = 0; i < s21.size(); i++) {
    EXPECT_EQ(s21.at(i), original.at(i));
  }
}

TEST(arrayTest4, accessTest) {
  std::array<int, 20> original2 = {20, 20};
  std::array<int, 20> original = original2;
  s21::array<int, 20> s212 = {20, 20};
  s21::array<int, 20> s21 = s212;
  for (size_t i = 0; i < s21.size(); i++) {
    EXPECT_EQ(s21.at(i), original.at(i));
  }
}

TEST(arrayTest5, accessTest) {
  std::array<int, 20> original2 = {20, 20};
  std::array<int, 20> original(std::move(original2));
  s21::array<int, 20> s212 = {20, 20};
  s21::array<int, 20> s21(std::move(s212));
  for (size_t i = 0; i < s21.size(); i++) {
    EXPECT_EQ(s21.at(i), original.at(i));
  }
}

TEST(arrayTest6, accessTest) {
  std::array<int, 20> original;
  s21::array<int, 20> s21;
  EXPECT_EQ(s21.max_size(), original.max_size());
  std::array<int, 0> original2;
  s21::array<int, 0> s212;
  EXPECT_EQ(s212.empty(), original2.empty());
}

TEST(arrayTest7, accessTest) {
  std::array<int, 5> original2;
  std::array<int, 5> original;
  s21::array<int, 5> s212;
  s21::array<int, 5> s21;
  original2.fill(5);
  s212.fill(5);
  s21 = std::move(s212);
  original = std::move(original2);
  for (size_t i = 0; i < s21.size(); i++) {
    EXPECT_EQ(s21.at(i), original.at(i));
  }
}

TEST(arrayTest8, accessTest) {
  s21::array<int, 5> s21;
  try {
    s21.at(6);
  } catch (const std::out_of_range &e) {
    std::string error = e.what();
    EXPECT_EQ("Wrong size", error);
  }
  try {
    s21::array<int, 5> s212 = {1, 2, 3, 4, 5, 6, 7, 8};
  } catch (const std::out_of_range &e) {
    std::string error = e.what();
    EXPECT_EQ("List size more than array size", error);
  }
}
