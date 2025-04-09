#include "tests.h"

TEST(multisetTest2, multisetTest) {
  s21::multiset<std::string> multiset;
  std::multiset<std::string> std_multiset;
  for (int i = 20; i >= 0; i--) {
    auto p = multiset.insert(std::to_string(i));
    auto std_p = std_multiset.insert(std::to_string(i));
    EXPECT_EQ(*p, *std_p);
  }
  auto std_iter = std_multiset.begin();
  for (auto iter = multiset.begin(); iter != multiset.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  auto std_iter2 = std_multiset.rbegin();
  for (auto iter = multiset.rbegin(); iter != multiset.rend(); ++iter) {
    EXPECT_EQ(*iter, *std_iter2);
    ++std_iter2;
  }
  auto iter = multiset.begin();
  auto std_iter3 = std_multiset.begin();
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

TEST(multisetTest3, multisetTest) {
  s21::multiset<int> multiset;
  std::multiset<int> std_multiset;
  for (int i = 20; i >= 0; i--) {
    auto p = multiset.insert(i);
    auto std_p = std_multiset.insert(i);
    EXPECT_EQ(*p, *std_p);
  }
  for (int i = 20; i >= 0; i--) {
    auto p = multiset.insert(i);
    auto std_p = std_multiset.insert(i);
    EXPECT_EQ(*p, *std_p);
  }
  auto std_iter = std_multiset.begin();
  for (auto iter = multiset.begin(); iter != multiset.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(multisetTest4, multisetTest) {
  s21::multiset<int> multiset;
  std::multiset<int> std_multiset;
  for (int i = 20; i >= 0; i--) {
    auto p = multiset.insert(i);
    auto std_p = std_multiset.insert(i);
    EXPECT_EQ(*p, *std_p);
  }
  EXPECT_EQ(multiset.size(), std_multiset.size());
  auto iter = multiset.begin();
  auto std_iter = std_multiset.begin();
  while (iter != multiset.end()) {
    if (*iter % 2 == 0) {
      iter++;
      std_iter++;
    } else {
      auto erase_iter = iter++;
      auto std_erase_iter = std_iter++;
      multiset.erase(erase_iter);
      std_multiset.erase(std_erase_iter);
    }
  }
  EXPECT_EQ(multiset.size(), std_multiset.size());
  auto std_iter2 = std_multiset.begin();
  for (auto iter2 = multiset.begin(); iter2 != multiset.end(); ++iter2) {
    EXPECT_EQ(*iter2, *std_iter2);
    ++std_iter2;
  }
}

TEST(multisetTest5, multisetTest) {
  s21::multiset<int> multiset;
  std::multiset<int> std_multiset;
  for (int i = 20; i >= 0; i--) {
    auto p = multiset.insert(i);
    auto std_p = std_multiset.insert(i);
    EXPECT_EQ(*p, *std_p);
  }
  std_multiset.clear();
  multiset.clear();
  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_LE(multiset.max_size(),
            std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(multisetTest6, multisetTest) {
  s21::multiset<int> multiset;
  s21::multiset<int> multiset2;
  std::multiset<int> std_multiset;
  std::multiset<int> std_multiset2;
  for (int i = 5; i >= 0; i--) {
    multiset.insert(i);
    std_multiset.insert(i);
  }
  for (int i = 10; i >= 6; i--) {
    multiset2.insert(i);
    std_multiset2.insert(i);
  }
  std_multiset.merge(std_multiset2);
  multiset.merge(multiset2);
  EXPECT_EQ(std_multiset.size(), multiset.size());
  EXPECT_EQ(std_multiset2.size(), multiset2.size());
  auto std_iter = std_multiset.begin();
  for (auto iter = multiset.begin(); iter != multiset.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(multisetTest7, multisetTest) {
  s21::multiset<int> multiset = {33, 31, 765, 789, 2, 2342, 66, 33};
  std::multiset<int> std_multiset = {33, 31, 765, 789, 2, 2342, 66, 33};
  EXPECT_EQ(multiset.empty(), std_multiset.empty());
  auto mi = multiset.begin();
  auto mo = std_multiset.begin();
  for (int i = 0; i < 4; ++mi, ++mo, ++i);
  multiset.erase(mi);
  std_multiset.erase(mo);
  EXPECT_EQ(multiset.contains(66), false);
  auto std_iter = std_multiset.begin();
  for (auto iter = multiset.begin(); iter != multiset.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(multisetTest8, CopyConstructor) {
  std::multiset<int> std_original_multiset;
  std_original_multiset.insert(1);
  std_original_multiset.insert(2);
  std_original_multiset.insert(3);

  s21::multiset<int> multiset;
  multiset.insert(1);
  multiset.insert(2);
  multiset.insert(3);

  std::multiset<int> std_copied_multiset(std_original_multiset);
  s21::multiset<int> copied_multiset(multiset);

  EXPECT_EQ(std_copied_multiset.size(), copied_multiset.size());
  auto std_iter = std_copied_multiset.begin();
  for (auto iter = copied_multiset.begin(); iter != copied_multiset.end();
       ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(multisetTest9, MoveConstructor) {
  std::multiset<int> std_original_multiset;
  std_original_multiset.insert(1);
  std_original_multiset.insert(2);
  std_original_multiset.insert(3);

  s21::multiset<int> multiset;
  multiset.insert(1);
  multiset.insert(2);
  multiset.insert(3);

  std::multiset<int> std_moved_multiset(std::move(std_original_multiset));
  s21::multiset<int> moved_multiset(std::move(multiset));

  EXPECT_EQ(std_moved_multiset.size(), moved_multiset.size());
  auto std_iter = std_moved_multiset.begin();
  for (auto iter = moved_multiset.begin(); iter != moved_multiset.end();
       ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST(multisetTest10, MoveAssignmentOperator) {
  s21::multiset<int> multiset1;
  multiset1.insert(1);
  multiset1.insert(2);
  multiset1.insert(3);
  std::multiset<int> std_multiset1;
  std_multiset1.insert(1);
  std_multiset1.insert(2);
  std_multiset1.insert(3);

  s21::multiset<int> multiset2;
  multiset2 = std::move(multiset1);
  std::multiset<int> std_multiset2;
  std_multiset2 = std::move(std_multiset1);

  EXPECT_EQ(multiset2.size(), std_multiset2.size());
  EXPECT_EQ(multiset1.size(), std_multiset1.size());
  auto std_iter = std_multiset2.begin();
  for (auto iter = multiset2.begin(); iter != multiset2.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  multiset1.insert(1);
}

TEST(multisetTest11, multisetSwap) {
  s21::multiset<int> multiset1;
  multiset1.insert(1);
  multiset1.insert(2);
  multiset1.insert(3);
  std::multiset<int> std_multiset1;
  std_multiset1.insert(1);
  std_multiset1.insert(2);
  std_multiset1.insert(3);

  s21::multiset<int> multiset2;
  multiset2.insert(4);
  multiset2.insert(5);
  std::multiset<int> std_multiset2;
  std_multiset2.insert(4);
  std_multiset2.insert(5);

  multiset1.swap(multiset2);
  std_multiset1.swap(std_multiset2);

  EXPECT_EQ(multiset1.size(), std_multiset1.size());
  EXPECT_EQ(multiset2.size(), std_multiset2.size());
  auto std_iter = std_multiset2.begin();
  for (auto iter = multiset2.begin(); iter != multiset2.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  EXPECT_EQ(*(multiset1.find(4)), *(std_multiset1.find(4)));
}

TEST(multisetTest12, multisetFuncs) {
  s21::multiset<int> multiset1 = {0, 1, 2, 1, 1, 1, 5};
  std::multiset<int> std_multiset1 = {0, 1, 2, 1, 1, 1, 5};
  EXPECT_EQ(multiset1.count(1), std_multiset1.count(1));
  auto p = multiset1.equal_range(1);
  auto std_p = std_multiset1.equal_range(1);
  EXPECT_EQ(*p.first, *std_p.first);
  EXPECT_EQ(*p.second, *std_p.second);
  EXPECT_EQ(*multiset1.lower_bound(3), *std_multiset1.lower_bound(3));
  EXPECT_EQ(*multiset1.upper_bound(1), *std_multiset1.upper_bound(1));
}

TEST(multisetTest13, insert_many) {
  s21::multiset<int> multiset;
  auto v = multiset.insert_many(1, 2, 3, 3);
  std::multiset<int> std_multiset;
  std_multiset.insert(1);
  std_multiset.insert(2);
  std_multiset.insert(3);
  std_multiset.insert(3);
  EXPECT_EQ(v.size(), 4);
  auto std_iter = std_multiset.begin();
  for (auto iter = multiset.begin(); iter != multiset.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
  multiset.clear();
  v = multiset.insert_many(1);
  EXPECT_EQ(v.size(), 1);
  multiset.clear();
  v = multiset.insert_many();
  EXPECT_EQ(v.size(), 0);
}
