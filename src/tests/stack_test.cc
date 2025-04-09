#include "tests.h"

TEST(Stack, access) {
  std::stack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::stack<int> s21;
  s21.push(1);
  s21.push(2);
  s21.push(3);

  EXPECT_EQ(s21.top(), original.top());
}

TEST(Stack, size) {
  s21::stack<int> stack1;
  EXPECT_EQ(stack1.size(), 0);
  stack1.push(10);
  stack1.push(20);
  stack1.push(30);
  EXPECT_EQ(stack1.size(), 3);

  s21::stack<int> stack2;
  EXPECT_EQ(stack2.size(), 0);
}

TEST(Stack, push) {
  std::stack<int> original;
  s21::stack<int> s21;

  for (int i = 1; i <= 5; ++i) {
    original.push(i);
    s21.push(i);
  }

  EXPECT_EQ(s21.size(), original.size());

  while (!original.empty()) {
    EXPECT_EQ(s21.top(), original.top());
    s21.pop();
    original.pop();
  }
}

TEST(Stack, constructor) {
  std::stack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  s21::stack<int> s21;
  s21.push(1);
  s21.push(2);
  s21.push(3);

  EXPECT_EQ(s21.size(), original.size());

  while (!original.empty()) {
    EXPECT_EQ(s21.top(), original.top());
    s21.pop();
    original.pop();
  }
}

TEST(Stack, Constructor_List) {
  s21::stack<int> our_stack = {1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(our_stack.top(), std_stack.top());
}

TEST(Stack, Constructor_Copy) {
  s21::stack<int> our_stack = {1, 2, 3};
  s21::stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.top(), std_copy.top());
}

TEST(Stack, Operator_Copy) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = our_stack_int;
  std_stack_empty = std_stack_int;
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Constructor_Move) {
  s21::stack<int> our_stack = {1, 2, 3};
  s21::stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.top(), std_move.top());
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Operator_Move) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, swap) {
  std::stack<int> original1, original2;
  s21::stack<int> s21_1, s21_2;
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
    EXPECT_EQ(s21_1.top(), original2.top());
    EXPECT_EQ(s21_2.top(), original1.top());
    s21_1.pop();
    s21_2.pop();
    original1.pop();
    original2.pop();
  }
}

#include "tests.h"

TEST(Stack, insert_many_front) {
  s21::stack<int> s21 = {1, 2, 5, 6};
  std::stack<int> original;
  original.push(1);
  original.push(2);
  original.push(5);
  original.push(6);

  s21.insert_many_front(3, 4);

  original.push(3);
  original.push(4);

  while (!s21.empty() && !original.empty()) {
    EXPECT_EQ(s21.top(), original.top());
    s21.pop();
    original.pop();
  }

  EXPECT_TRUE(s21.empty());
  EXPECT_TRUE(original.empty());
}
