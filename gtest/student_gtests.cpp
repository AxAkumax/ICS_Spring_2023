#include <gtest/gtest.h>

#include "Timer.h"
#include "holder.cpp"
#include "is_balanced.cpp"

TEST(ArrayStackSizeTest, ArrayStack) {
  ArrayStack as(3);
  as.insert("1");
  as.insert("2");
  as.insert("3");
  EXPECT_TRUE(as.is_full());
}
