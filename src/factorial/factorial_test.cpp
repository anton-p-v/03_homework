#include <gtest/gtest.h>

#include "factorial.h"


namespace {

TEST(Factorial, Test1) {
  EXPECT_EQ(factorial(9), 362880);
}

}
