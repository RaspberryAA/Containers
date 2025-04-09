#include "tests.h"

TEST(SetTest2, SetTest) {
  s21::set<std::string> set;
  std::set<std::string> std_set;
  for (int i = 20; i >= 0; i--) {
    std::pair p = set.insert(std::to_string(i));
    std::pair std_p = std_set.insert(std::to_string(i));
    EXPECT_EQ(*p.first, *std_p.first);
    EXPECT_EQ(p.second, std_p.second);
  }
  auto std_iter = std_set.begin();
  for (auto iter = set.begin(); iter != set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  auto std_iter2 = std_set.rbegin();
  for (auto iter = set.rbegin(); iter != set.rend(); ++iter) {
    EXPECT_EQ(*iter, *std_iter2);
    ++std_iter2;
  }
  auto iter = set.begin();
  auto std_iter3 = std_set.begin();
  iter++;
  std_iter3++;
  iter++;
  std_iter3++;
  --iter;
  iter--;
  --std_iter3;
  std_iter3--;
  EXPECT_EQ(*iter, *std_iter3);
}

TEST(SetTest3, SetTest) {
  s21::set<int> set;
  std::set<int> std_set;
  for (int i = 20; i >= 0; i--) {
    std::pair p = set.insert(i);
    std::pair std_p = std_set.insert(i);
    EXPECT_EQ(*p.first, *std_p.first);
    EXPECT_EQ(p.second, std_p.second);
  }
  for (int i = 20; i >= 0; i--) {
    std::pair p = set.insert(i);
    std::pair std_p = std_set.insert(i);
    EXPECT_EQ(*p.first, *std_p.first);
    EXPECT_EQ(p.second, std_p.second);
  }
  auto std_iter = std_set.begin();
  for (auto iter = set.begin(); iter != set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(SetTest4, SetTest) {
  s21::set<int> set;
  std::set<int> std_set;
  for (int i = 20; i >= 0; i--) {
    std::pair p = set.insert(i);
    std::pair std_p = std_set.insert(i);
    EXPECT_EQ(*p.first, *std_p.first);
    EXPECT_EQ(p.second, std_p.second);
  }
  EXPECT_EQ(set.size(), std_set.size());
  auto iter = set.begin();
  auto std_iter = std_set.begin();
  while (iter != set.end()) {
    if (*iter % 2 == 0) {
      iter++;
      std_iter++;
    } else {
      auto erase_iter = iter++;
      auto std_erase_iter = std_iter++;
      set.erase(erase_iter);
      std_set.erase(std_erase_iter);
    }
  }
  EXPECT_EQ(set.size(), std_set.size());
  auto std_iter2 = std_set.begin();
  for (auto iter2 = set.begin(); iter2 != set.end(); ++iter2) {
    EXPECT_EQ(*iter2, *std_iter2);
    ++std_iter2;
  }
}

TEST(SetTest5, SetTest) {
  s21::set<int> set;
  std::set<int> std_set;
  for (int i = 20; i >= 0; i--) {
    std::pair p = set.insert(i);
    std::pair std_p = std_set.insert(i);
    EXPECT_EQ(*p.first, *std_p.first);
    EXPECT_EQ(p.second, std_p.second);
  }
  std_set.clear();
  set.clear();
  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_LE(set.max_size(), std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(SetTest6, SetTest) {
  s21::set<int> set;
  s21::set<int> set2;
  std::set<int> std_set;
  std::set<int> std_set2;
  for (int i = 5; i >= 0; i--) {
    set.insert(i);
    std_set.insert(i);
  }
  for (int i = 10; i >= 6; i--) {
    set2.insert(i);
    std_set2.insert(i);
  }
  std_set.merge(std_set2);
  set.merge(set2);
  EXPECT_EQ(std_set.size(), set.size());
  EXPECT_EQ(std_set2.size(), set2.size());
  auto std_iter = std_set.begin();
  for (auto iter = set.begin(); iter != set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(SetTest7, SetTest) {
  s21::set<int> set = {33, 31, 765, 789, 2, 2342, 66, 33};
  std::set<int> std_set = {33, 31, 765, 789, 2, 2342, 66, 33};
  EXPECT_EQ(set.empty(), std_set.empty());
  auto mi = set.begin();
  auto mo = std_set.begin();
  for (int i = 0; i < 4; ++mi, ++mo, ++i);
  set.erase(mi);
  std_set.erase(mo);
  EXPECT_EQ(set.contains(765), false);
  auto std_iter = std_set.begin();
  for (auto iter = set.begin(); iter != set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(SetTest8, CopyConstructor) {
  std::set<int> std_original_set;
  std_original_set.insert(1);
  std_original_set.insert(2);
  std_original_set.insert(3);

  s21::set<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);

  std::set<int> std_copied_set(std_original_set);
  s21::set<int> copied_set(set);

  EXPECT_EQ(std_copied_set.size(), copied_set.size());
  auto std_iter = std_copied_set.begin();
  for (auto iter = copied_set.begin(); iter != copied_set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(SetTest9, MoveConstructor) {
  std::set<int> std_original_set;
  std_original_set.insert(1);
  std_original_set.insert(2);
  std_original_set.insert(3);

  s21::set<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);

  std::set<int> std_moved_set(std::move(std_original_set));
  s21::set<int> moved_set(std::move(set));

  EXPECT_EQ(std_moved_set.size(), moved_set.size());
  auto std_iter = std_moved_set.begin();
  for (auto iter = moved_set.begin(); iter != moved_set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(SetTest10, MoveAssignmentOperator) {
  s21::set<int> set1;
  set1.insert(1);
  set1.insert(2);
  set1.insert(3);
  std::set<int> std_set1;
  std_set1.insert(1);
  std_set1.insert(2);
  std_set1.insert(3);

  s21::set<int> set2;
  set2 = std::move(set1);
  std::set<int> std_set2;
  std_set2 = std::move(std_set1);

  EXPECT_EQ(set2.size(), std_set2.size());
  EXPECT_EQ(set1.size(), std_set1.size());
  auto std_iter = std_set2.begin();
  for (auto iter = set2.begin(); iter != set2.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  set1.insert(1);
}

TEST(SetTest11, setSwap) {
  s21::set<int> set1;
  set1.insert(1);
  set1.insert(2);
  set1.insert(3);
  s21::set<int> std_set1;
  std_set1.insert(1);
  std_set1.insert(2);
  std_set1.insert(3);

  s21::set<int> set2;
  set2.insert(4);
  set2.insert(5);
  s21::set<int> std_set2;
  std_set2.insert(4);
  std_set2.insert(5);

  set1.swap(set2);
  std_set1.swap(std_set2);

  EXPECT_EQ(set1.size(), std_set1.size());
  EXPECT_EQ(set2.size(), std_set2.size());
  auto std_iter = std_set2.begin();
  for (auto iter = set2.begin(); iter != set2.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  EXPECT_EQ(*(set1.find(4)), *(std_set1.find(4)));
}

TEST(setTest12, insert_many) {
  s21::set<int> set;
  auto v = set.insert_many(1, 2, 3, 3);
  std::set<int> std_set;
  std_set.insert(1);
  std_set.insert(2);
  std_set.insert(3);
  std_set.insert(3);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[3].second, false);
  auto std_iter = std_set.begin();
  for (auto iter = set.begin(); iter != set.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  set.clear();
  v = set.insert_many(1);
  EXPECT_EQ(v.size(), 1);
  set.clear();
  v = set.insert_many();
  EXPECT_EQ(v.size(), 0);
}
