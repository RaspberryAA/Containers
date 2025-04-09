#include "tests.h"

TEST(List, access) {
  std::list<int> original = {1, 2, 3, 4, 5};
  s21::list<int> s21 = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21.front(), original.front());
  EXPECT_EQ(s21.back(), original.back());
}

TEST(List, size) {
  s21::list<int> list1;
  EXPECT_EQ(list1.size(), 0);
  list1.push_back(10);
  list1.push_back(20);
  list1.push_back(30);
  EXPECT_EQ(list1.size(), 3);
  s21::list<int> list2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(list2.size(), 5);
}

TEST(List, push_back) {
  std::list<int> original;

  s21::list<int> s21;

  for (int i = 1; i <= 5; ++i) {
    original.push_back(i);
    s21.push_back(i);
  }

  EXPECT_EQ(s21.size(), original.size());

  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, push_front) {
  std::list<int> original;
  s21::list<int> s21;

  for (int i = 1; i <= 5; ++i) {
    original.push_front(i);
    s21.push_front(i);
  }

  EXPECT_EQ(s21.size(), original.size());

  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, constructor) {
  std::list<int> original = {1, 2, 3, 4, 5};
  s21::list<int> s21 = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21.size(), original.size());

  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, constructor_with_size) {
  std::list<int> original = {1, 2, 3, 4, 5};

  s21::list<int> s21(5);

  EXPECT_EQ(s21.size(), original.size());
}

TEST(List, constructor_copy) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> original_list = {1, 2, 3};
  s21::list<int> s21_copy(s21_list);
  std::list<int> original_copy(original_list);
  EXPECT_EQ(s21_copy.front(), original_copy.front());
  EXPECT_EQ(s21_copy.back(), original_copy.back());
}

TEST(List, constructor_move) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> original_list = {1, 2, 3};
  s21::list<int> s21_copy(std::move(s21_list));
  std::list<int> original_copy(std::move(original_list));
  EXPECT_EQ(s21_copy.front(), original_copy.front());
  EXPECT_EQ(s21_copy.back(), original_copy.back());
}

TEST(List, insert) {
  std::list<int> original = {1, 2, 3, 4, 5};
  s21::list<int> s21 = {1, 2, 3, 4, 5};

  auto it1 = s21.end();
  auto it2 = original.end();

  s21.insert(it1, 8);
  original.insert(it2, 8);

  it1 = s21.begin();
  it2 = original.begin();

  s21.insert(it1, 9);
  original.insert(it2, 9);

  ++it1;
  ++it2;

  s21.insert(it1, 5);
  original.insert(it2, 5);

  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, erase) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, sort) {
  s21::list<int> list = {5, 3, 8, 1, 7};
  s21::list<int> expected = {1, 3, 5, 7, 8};

  list.sort();

  auto it1 = list.begin();
  auto it2 = expected.begin();
  for (; it1 != list.end() && it2 != expected.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, unique) {
  std::list<int> original = {1, 2, 3, 3, 5};
  s21::list<int> s21 = {1, 2, 3, 3, 5};
  original.unique();
  s21.unique();
  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, pop_back) {
  std::list<int> original = {1, 2, 3, 3, 5};
  s21::list<int> s21 = {1, 2, 3, 3, 5};
  original.pop_back();
  s21.pop_back();
  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, pop_front) {
  std::list<int> original = {1, 2, 3, 3, 5};
  s21::list<int> s21 = {1, 2, 3, 3, 5};
  original.pop_front();
  s21.pop_front();
  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, swap) {
  s21::list<int> list1, list2;

  for (int i = 1; i <= 5; ++i) {
    list1.push_back(i);
    list2.push_back(i * 10);
  }

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 5);
  EXPECT_EQ(list2.size(), 5);

  auto it1 = list1.begin();
  auto it2 = list2.begin();
  for (int i = 1; i <= 5; ++i, ++it1, ++it2) {
    EXPECT_EQ(*it1, i * 10);
    EXPECT_EQ(*it2, i);
  }
}

TEST(List, merge) {
  s21::list<int> list1, list2, list3;

  for (int i = 1; i <= 3; ++i) {
    list1.push_back(i);
    list2.push_back(i + 3);
  }

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);

  int expected_value = 1;
  for (int num : list1) {
    EXPECT_EQ(num, expected_value++);
  }

  s21::list<int> list4(list1);
  list3.merge(list1);

  auto it1 = list4.begin();
  auto it2 = list3.begin();
  for (; it1 != list4.end() && it2 != list3.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, splice) {
  s21::list<int> s21_1 = {1};
  s21::list<int> s21_2 = {2, 3, 4, 5};
  std::list<int> original_1 = {1};
  std::list<int> original_2 = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = s21_1.begin();
  std::list<int>::iterator std_it = original_1.begin();
  s21_1.splice(our_it, s21_2);
  original_1.splice(std_it, original_2);
  auto it1 = s21_1.begin();
  auto it2 = original_1.begin();
  for (; it1 != s21_1.end() && it2 != original_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, splice2) {
  s21::list<int> s21_1 = {1};
  s21::list<int> s21_2 = {2, 3, 4, 5};
  s21::list<int> original_1 = {1};
  s21::list<int> original_2 = {2, 3, 4, 5};
  s21::list<int>::iterator our_it = nullptr;
  s21::list<int>::iterator std_it = nullptr;
  s21_1.splice(our_it, s21_2);
  original_1.splice(std_it, original_2);
  auto it1 = s21_1.begin();
  auto it2 = original_1.begin();
  for (; it1 != s21_1.end() && it2 != original_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}
TEST(List, splice3) {
  s21::list<int> s21_1 = {1};
  s21::list<int> s21_2;
  s21::list<int> original_1 = {1};
  s21::list<int> original_2;
  s21::list<int>::iterator our_it = s21_1.begin();
  s21::list<int>::iterator std_it = original_1.begin();
  our_it++;
  std_it++;

  s21_1.splice(our_it, s21_2);
  original_1.splice(std_it, original_2);
  auto it1 = s21_1.begin();
  auto it2 = original_1.begin();
  for (; it1 != s21_1.end() && it2 != original_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, reverse) {
  s21::list<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.push_back(i);
  }

  list.reverse();

  int expected_value = 5;
  for (int num : list) {
    EXPECT_EQ(num, expected_value--);
  }
}

TEST(List, operator_decrement) {
  std::list<int> original = {1, 2, 3, 3, 5};
  s21::list<int> s21 = {1, 2, 3, 3, 5};
  auto it1 = s21.begin();
  auto it2 = original.begin();
  it1++;
  it2++;
  it1--;
  it2--;
  it1++;
  it2++;
  --it1;
  --it2;
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, insert_many) {
  s21::list<int> s21 = {1, 2, 5, 6};
  std::list<int> original = {1, 2, 5, 6};

  s21.insert_many(s21.begin(), 3, 4);
  auto it_o = original.begin();
  original.insert(it_o, 3);
  it_o++;
  original.insert(it_o, 4);

  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, insert_many_back) {
  s21::list<int> s21 = {1, 2, 5, 6};
  std::list<int> original = {1, 2, 5, 6};

  s21.insert_many_back(3, 4);

  original.push_back(3);
  original.push_back(4);

  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, insert_many_front) {
  s21::list<int> s21 = {1, 2, 5, 6};
  std::list<int> original = {1, 2, 5, 6};

  s21.insert_many_front(3, 4);

  original.push_front(3);
  original.push_front(4);

  auto it1 = s21.begin();
  auto it2 = original.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, operatoreq1) {
  s21::list<int> s21 = {1, 2, 5, 6};
  std::list<int> original = {1, 2, 5, 6};
  s21::list<int> s21e = {1, 2};
  std::list<int> originale = {1, 2};
  originale = original;
  s21e = s21;
  auto it1 = s21.begin();
  auto it2 = originale.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(List, operatoreq2) {
  s21::list<int> s21 = {1, 2, 5, 6};
  std::list<int> original = {1, 2, 5, 6};
  s21::list<int> s21e = {1, 2};
  std::list<int> originale = {1, 2};
  s21e = std::move(s21);
  originale = std::move(original);
  auto it1 = s21e.begin();
  auto it2 = originale.begin();
  for (; it1 != s21.end() && it2 != original.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}