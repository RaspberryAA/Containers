#include "tests.h"

TEST(mapTest1, mapTest) {
  s21::map<std::string, int> map;
  std::map<std::string, int> std_map;
  map.insert(std::make_pair("1", 1));
  std_map.insert(std::make_pair("1", 1));
  EXPECT_EQ(map.at("1"), std_map.at("1"));
  for (int i = 20; i >= 2; i--) {
    map[std::to_string(i)] = i;
    std_map[std::to_string(i)] = i;
  }
  for (int i = 0; i < 18; ++i) {
    EXPECT_EQ(map[std::to_string(i)], std_map[std::to_string(i)]);
  }
}

TEST(mapTest2, mapTest) {
  s21::map<std::string, int> map;
  std::map<std::string, int> std_map;
  for (int i = 20; i >= 0; i--) {
    std::pair p = map.insert(std::make_pair(std::to_string(i), i));
    std::pair std_p = std_map.insert(std::make_pair(std::to_string(i), i));
    EXPECT_EQ(p.first->first, std_p.first->first);
    EXPECT_EQ(p.first->second, std_p.first->second);
    EXPECT_EQ(p.second, std_p.second);
  }
  auto std_iter = std_map.begin();
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
  auto std_iter2 = std_map.rbegin();
  for (auto iter = map.rbegin(); iter != map.rend(); ++iter) {
    EXPECT_EQ(iter->first, std_iter2->first);
    EXPECT_EQ(iter->second, std_iter2->second);
    ++std_iter2;
  }
  auto iter = map.begin();
  auto std_iter3 = std_map.begin();
  iter++;
  std_iter3++;
  iter++;
  std_iter3++;
  --iter;
  iter--;
  --std_iter3;
  std_iter3--;
  EXPECT_EQ(iter->first, std_iter3->first);
  EXPECT_EQ(iter->second, std_iter3->second);
}

TEST(mapTest3, mapTest) {
  s21::map<int, int> map;
  std::map<int, int> std_map;
  for (int i = 20; i >= 0; i--) {
    std::pair p = map.insert(i, i);
    std::pair std_p = std_map.insert(std::make_pair(i, i));
    EXPECT_EQ(p.first->first, std_p.first->first);
    EXPECT_EQ(p.first->second, std_p.first->second);
    EXPECT_EQ(p.second, std_p.second);
  }
  for (int i = 20; i >= 0; i--) {
    std::pair p = map.insert(i, i);
    std::pair std_p = std_map.insert(std::make_pair(i, i));
    EXPECT_EQ(p.first->first, std_p.first->first);
    EXPECT_EQ(p.first->second, std_p.first->second);
    EXPECT_EQ(p.second, std_p.second);
  }
  auto std_iter = std_map.begin();
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(mapTest4, mapTest) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;
  for (int i = 20; i >= 0; i--) {
    std::pair p = map.insert(i, std::to_string(i));
    std::pair std_p = std_map.insert(std::make_pair(i, std::to_string(i)));
    EXPECT_EQ(p.first->first, std_p.first->first);
    EXPECT_EQ(p.first->second, std_p.first->second);
    EXPECT_EQ(p.second, std_p.second);
  }
  EXPECT_EQ(map.size(), std_map.size());
  auto iter = map.begin();
  auto std_iter = std_map.begin();
  while (iter != map.end()) {
    if (iter->first % 2 == 0) {
      iter++;
      std_iter++;
    } else {
      auto erase_iter = iter++;
      auto std_erase_iter = std_iter++;
      map.erase(erase_iter);
      std_map.erase(std_erase_iter);
    }
  }
  EXPECT_EQ(map.size(), std_map.size());
  auto std_iter2 = std_map.begin();
  for (auto iter2 = map.begin(); iter2 != map.end(); ++iter2) {
    EXPECT_EQ(iter2->first, std_iter2->first);
    EXPECT_EQ(iter2->second, std_iter2->second);
    ++std_iter2;
  }
}

TEST(mapTest5, mapTest) {
  s21::map<int, int> map;
  std::map<int, int> std_map;
  for (int i = 20; i >= 0; i--) {
    std::pair p = map.insert(i, i);
    std::pair std_p = std_map.insert(std::make_pair(i, i));
    EXPECT_EQ(p.first->first, std_p.first->first);
    EXPECT_EQ(p.first->second, std_p.first->second);
    EXPECT_EQ(p.second, std_p.second);
  }
  std_map.clear();
  map.clear();
  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_LE(map.max_size(), std::numeric_limits<size_t>::max() /
                                sizeof(std::pair<const int, int>));
}

TEST(mapTest6, mapTest) {
  s21::map<int, int> map;
  s21::map<int, int> map2;
  std::map<int, int> std_map;
  std::map<int, int> std_map2;
  for (int i = 5; i >= 0; i--) {
    map.insert(i, i);
    std_map.insert(std::make_pair(i, i));
  }
  for (int i = 10; i >= 6; i--) {
    map2.insert(i, i);
    std_map2.insert(std::make_pair(i, i));
  }
  std_map.merge(std_map2);
  map.merge(map2);
  EXPECT_EQ(std_map.size(), map.size());
  EXPECT_EQ(std_map2.size(), map2.size());
  auto std_iter = std_map.begin();
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(mapTest7, mapTest) {
  s21::map<int, int> map = {{33, 33321}, {31, 2},   {765, 56}, {789, 3},
                            {2, 9},      {2342, 0}, {66, 77},  {33, 2}};
  std::map<int, int> std_map = {{33, 33321}, {31, 2},   {765, 56}, {789, 3},
                                {2, 9},      {2342, 0}, {66, 77},  {33, 2}};
  EXPECT_EQ(map.empty(), std_map.empty());
  auto mi = map.begin();
  auto mo = std_map.begin();
  for (int i = 0; i < 4; ++mi, ++mo, ++i);
  map.erase(mi);
  std_map.erase(mo);
  EXPECT_EQ(map.contains(765), false);
  auto std_iter = std_map.begin();
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(MapTest8, CopyConstructor) {
  std::map<int, int> std_original_map;
  std_original_map.insert({1, 100});
  std_original_map.insert({2, 200});
  std_original_map.insert({3, 300});

  s21::map<int, int> map;
  map.insert({1, 100});
  map.insert({2, 200});
  map.insert({3, 300});

  std::map<int, int> std_copied_map(std_original_map);
  s21::map<int, int> copied_map(map);

  EXPECT_EQ(std_copied_map.size(), copied_map.size());
  auto std_iter = std_copied_map.begin();
  for (auto iter = copied_map.begin(); iter != copied_map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(MapTest9, MoveConstructor) {
  std::map<int, int> std_original_map;
  std_original_map.insert({1, 100});
  std_original_map.insert({2, 200});
  std_original_map.insert({3, 300});

  s21::map<int, int> map;
  map.insert({1, 100});
  map.insert({2, 200});
  map.insert({3, 300});

  std::map<int, int> std_moved_map(std::move(std_original_map));
  s21::map<int, int> moved_map(std::move(map));

  EXPECT_EQ(std_moved_map.size(), moved_map.size());
  auto std_iter = std_moved_map.begin();
  for (auto iter = moved_map.begin(); iter != moved_map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(MapTest10, MoveAssignmentOperator) {
  s21::map<int, int> map1;
  map1.insert({1, 100});
  map1.insert({2, 200});
  map1.insert({3, 300});
  std::map<int, int> std_map1;
  std_map1.insert({1, 100});
  std_map1.insert({2, 200});
  std_map1.insert({3, 300});

  s21::map<int, int> map2;
  map2 = std::move(map1);
  std::map<int, int> std_map2;
  std_map2 = std::move(std_map1);

  EXPECT_EQ(map2.size(), std_map2.size());
  EXPECT_EQ(map1.size(), std_map1.size());
  auto std_iter = std_map2.begin();
  for (auto iter = map2.begin(); iter != map2.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
  map1.insert(1, 1);
}

TEST(MapTest11, MapSwap) {
  s21::map<int, int> map1;
  map1.insert({1, 100});
  map1.insert({2, 200});
  map1.insert({3, 300});
  std::map<int, int> std_map1;
  std_map1.insert({1, 100});
  std_map1.insert({2, 200});
  std_map1.insert({3, 300});

  s21::map<int, int> map2;
  map2.insert({4, 400});
  map2.insert({5, 500});
  std::map<int, int> std_map2;
  std_map2.insert({4, 400});
  std_map2.insert({5, 500});

  map1.swap(map2);
  std_map1.swap(std_map2);

  EXPECT_EQ(map1.size(), std_map1.size());
  EXPECT_EQ(map2.size(), std_map2.size());
  auto std_iter = std_map2.begin();
  for (auto iter = map2.begin(); iter != map2.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(MapTest12, InsertOrAssign) {
  s21::map<int, int> map;
  auto result1 = map.insert_or_assign(1, 100);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(result1.first->first, 1);
  EXPECT_EQ(result1.first->second, 100);
  auto result2 = map.insert_or_assign(1, 200);
  EXPECT_FALSE(result2.second);
  EXPECT_EQ(result2.first->first, 1);
  EXPECT_EQ(result2.first->second, 200);
  try {
    map.at(999999);
  } catch (const std::out_of_range& e) {
    std::string s = e.what();
    EXPECT_EQ(s, "Element not found");
  }
}

TEST(MapTest13, InsertOrAssign2) {
  s21::map<int, int> map;
  map.insert_or_assign(1, 100);
  map.insert_or_assign(1, 200);
  s21::map<int, int> std_map;
  std_map.insert_or_assign(1, 100);
  std_map.insert_or_assign(1, 200);
  auto std_iter = std_map.begin();
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
}

TEST(MapTest14, insert_many) {
  s21::map<int, int> map;
  auto v = map.insert_many(std::make_pair(1, 2), std::make_pair(2, 3),
                           std::make_pair(3, 3), std::make_pair(4, 4));
  std::map<int, int> std_map;
  std_map.insert({1, 2});
  std_map.insert({2, 3});
  std_map.insert({3, 3});
  std_map.insert({4, 4});
  EXPECT_EQ(v.size(), 4);
  auto std_iter = std_map.begin();
  for (auto iter = map.begin(); iter != map.end(); ++iter) {
    EXPECT_EQ(iter->first, std_iter->first);
    EXPECT_EQ(iter->second, std_iter->second);
    ++std_iter;
  }
  map.clear();
  v = map.insert_many(std::make_pair(1, 2));
  EXPECT_EQ(v.size(), 1);
  map.clear();
  v = map.insert_many();
  EXPECT_EQ(v.size(), 0);
  v = map.insert_many({{1, 1}, {2, 2}});
  EXPECT_EQ(v.size(), 2);
}
