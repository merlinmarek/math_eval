#include <gtest/gtest.h>

#include <math_eval.h>

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(math_eval(infix_to_postfix("3+4")), 7);
}
