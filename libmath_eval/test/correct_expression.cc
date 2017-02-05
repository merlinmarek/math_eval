#include <gtest/gtest.h>

#include <math_eval.h>

TEST(evaluation_test, simple_addition)
{
    EXPECT_EQ(math_eval(infix_to_postfix("3+4")), 7);
}

TEST(evaluation_test, simple_subtraction)
{
    EXPECT_EQ(math_eval(infix_to_postfix("10-4")), 6);
}

TEST(evaluation_test, complex_expression)
{
    EXPECT_NEAR(math_eval(infix_to_postfix("4 * (9 + sqrt(exp(5) + 4))")), 85.3823, 0.0001);
}
