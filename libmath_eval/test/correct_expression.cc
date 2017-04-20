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

TEST(evaluation_test, leading_minus)
{
    EXPECT_EQ(math_eval(infix_to_postfix("-3*7")), -21);
}

TEST(evaluation_test, complex_expression_1)
{
    // sqrt and exp are tested
    EXPECT_NEAR(math_eval(infix_to_postfix("4 * (9 + sqrt(exp(5) + 4))")), 85.3823, 0.0001);
}

TEST(evaluation_test, complex_expression_2)
{
    // sqrt, sin and log are tested
    EXPECT_NEAR(math_eval(infix_to_postfix("sqrt(sin(log(14)))")), 0.694009, 0.0001);
}

TEST(evaluation_test, complex_expression_3)
{
    // cos, tan and asin are tested 
    EXPECT_NEAR(math_eval(infix_to_postfix("asin(tan(cos(1.4)))")), 0.172477, 0.0001);
}
