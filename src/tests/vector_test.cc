#include "tests.h"

TEST(vectorTest1, accessTest) {
  std::vector<int> original = {1, 2, 3, 4, 5};
  s21::vector<int> s21 = {1, 2, 3, 4, 5};
  assert_vectors(s21, original);
  EXPECT_EQ(s21[0], original[0]);
  EXPECT_EQ(s21.front(), original.front());
  EXPECT_EQ(s21.back(), original.back());
  int *a = s21.data();
  int *b = original.data();
  for (size_t i = 0; i < original.size(); i++) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(vectorTest2, capacityAndModifiersTest) {
  std::vector<std::string> original;
  s21::vector<std::string> s21;
  s21.push_back("a");
  s21.push_back("b");
  s21.push_back("c");
  s21.pop_back();
  original.push_back("a");
  original.push_back("b");
  original.push_back("c");
  original.pop_back();
  assert_vectors(s21, original);
  s21.push_back("d");
  EXPECT_EQ(s21[2], "d");
  EXPECT_EQ(s21.size(), 3);
  s21::vector<std::string> s22 = {"e"};
  s21.swap(s22);
  EXPECT_EQ(s21.size(), 1);
  EXPECT_EQ(s22.size(), 3);
  s21::vector<std::string>::iterator it = s22.begin();
  it++;
  s22.erase(it);
  EXPECT_EQ(s22.at(1), "d");
  it = s22.begin();
  s22.insert(it, "q");
  EXPECT_EQ(s22.at(0), "q");
  s22.reserve(100);
  EXPECT_EQ(s22.capacity(), 100);
  EXPECT_EQ(original.max_size(), s22.max_size());
  s22.shrink_to_fit();
  EXPECT_EQ(s22.capacity(), s22.size());
  s22.clear();
  EXPECT_EQ(true, s22.empty());
}

TEST(vectorTest3, accessTest2) {
  s21::vector<int> s21;
  try {
    s21.at(0);
  } catch (const std::out_of_range &e) {
    std::string error = e.what();
    EXPECT_EQ("Index out of range", error);
  }
  for (int i = 0; i < 32; i++) {
    s21.push_back(i);
  }
  EXPECT_EQ(32, s21.capacity());
}

TEST(vectorTest4, accessTest2) {
  s21::vector<int> s21(20);
  EXPECT_EQ(20, s21.capacity());
  s21.push_back(45);
  s21::vector<int> s22(s21);
  EXPECT_EQ(20, s22.capacity());
  EXPECT_EQ(1, s22.size());
}

TEST(vectorTest5, insert) {
  s21::vector<int> s21 = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  auto it = s21.insert_many(s21.begin(), 1);
  auto std_it = original.insert(original.begin(), {1});
  assert_vectors(s21, original);
  EXPECT_EQ(*it, *std_it);
}

TEST(vectorTest6, insert) {
  s21::vector<int> s21 = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  auto it = s21.insert_many(s21.begin() + 4, 3, 4, 4);
  auto std_it = original.insert(original.begin() + 4, {3, 4, 4});
  assert_vectors(s21, original);
  EXPECT_EQ(*it, *std_it);
}

TEST(vectorTest7, insert) {
  s21::vector<int> s21 = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  s21.insert_many_back(3, 4, 4, 4, 413, 21, 3123, 6);
  original.insert(original.end(), {3, 4, 4, 4, 413, 21, 3123, 6});
  assert_vectors(s21, original);
}

TEST(vectorTest8, insert) {
  s21::vector<int> s21 = {1, 2, 3, 4, 5, 6};
  std::vector<int> original = {1, 2, 3, 4, 5, 6};
  s21.insert_many_back();
  auto it = s21.insert_many(s21.begin());
  auto std_it = original.insert(original.begin(), {});
  original.insert(original.end(), {});
  assert_vectors(s21, original);
  EXPECT_EQ(*it, *std_it);
  EXPECT_EQ(s21.size(), original.size());
}

TEST(vectorTest9, insert) {
  s21::vector<int> s21 = {1, 2};
  std::vector<int> original = {1, 2};
  auto it1 = s21.begin();

  s21.insert(it1, 1);
  it1 = s21.begin();
  s21.insert(it1, 1);
  it1 = s21.begin();
  s21.insert(it1, 1);
  it1 = s21.begin();
  s21.insert(it1, 1);

  auto std_it = original.begin();

  original.insert(std_it, 1);
  std_it = original.begin();
  original.insert(std_it, 1);
  std_it = original.begin();
  original.insert(std_it, 1);
  std_it = original.begin();
  original.insert(std_it, 1);
  assert_vectors(s21, original);
}
