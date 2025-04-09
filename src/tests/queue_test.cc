#include "tests.h"

TEST(Queue, access) {
  std::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::queue<int> s21;
  s21.push(1);
  s21.push(2);
  s21.push(3);

  EXPECT_EQ(s21.front(), original.front());
  EXPECT_EQ(s21.back(), original.back());
}

TEST(Queue, size) {
  s21::queue<int> queue1;
  EXPECT_EQ(queue1.size(), 0);
  queue1.push(10);
  queue1.push(20);
  queue1.push(30);
  EXPECT_EQ(queue1.size(), 3);

  s21::queue<int> queue2;
  EXPECT_EQ(queue2.size(), 0);
}

TEST(Queue, push) {
  std::queue<int> original;
  s21::queue<int> s21;

  for (int i = 1; i <= 5; ++i) {
    original.push(i);
    s21.push(i);
  }

  EXPECT_EQ(s21.size(), original.size());

  while (!original.empty()) {
    EXPECT_EQ(s21.front(), original.front());
    s21.pop();
    original.pop();
  }
}

TEST(Queue, constructor) {
  std::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::queue<int> s21;
  s21.push(1);
  s21.push(2);
  s21.push(3);

  EXPECT_EQ(s21.size(), original.size());

  while (!original.empty()) {
    EXPECT_EQ(s21.front(), original.front());
    s21.pop();
    original.pop();
  }
}

TEST(Queue, Constructor_List) {
  s21::queue<int> our_queue = {1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(our_queue.front(), std_queue.front());
  EXPECT_EQ(our_queue.back(), std_queue.back());
}

TEST(Queue, Constructor_Copy) {
  s21::queue<int> our_queue = {1, 2, 3};
  s21::queue<int> our_copy(our_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_copy(std_queue);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(Queue, Operator_Copy) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = our_queue_int;
  std_queue_empty = std_queue_int;
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Constructor_Move) {
  s21::queue<int> our_queue = {1, 2, 3};
  s21::queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());
  EXPECT_EQ(our_move.back(), std_move.back());
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(Queue, Operator_Move) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = std::move(our_queue_int);
  std_queue_empty = std::move(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, swap) {
  std::queue<int> original1, original2;
  s21::queue<int> s21_1, s21_2;
  for (int i = 1; i <= 5; ++i) {
    original1.push(i);
    original2.push(i * 10);
    s21_1.push(i);
    s21_2.push(i * 10);
  }

  s21_1.swap(s21_2);

  EXPECT_EQ(s21_1.size(), 5);
  EXPECT_EQ(s21_2.size(), 5);

  while (!original1.empty() && !original2.empty()) {
    EXPECT_EQ(s21_1.front(), original2.front());
    EXPECT_EQ(s21_2.front(), original1.front());
    s21_1.pop();
    s21_2.pop();
    original1.pop();
    original2.pop();
  }
}

TEST(Queue, insert_many_front) {
  s21::queue<int> s21 = {1, 2, 5, 6};
  std::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(5);
  original.push(6);

  s21.insert_many_back(3, 4);

  original.push(3);
  original.push(4);

  while (!s21.empty() && !original.empty()) {
    EXPECT_EQ(s21.front(), original.front());
    s21.pop();
    original.pop();
  }

  EXPECT_TRUE(s21.empty());
  EXPECT_TRUE(original.empty());
}