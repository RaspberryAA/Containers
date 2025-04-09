#include "tests.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
#pragma GCC diagnostic ignored "-Wunused-result"
  RUN_ALL_TESTS();
#pragma GCC diagnostic pop
  return 0;
}
