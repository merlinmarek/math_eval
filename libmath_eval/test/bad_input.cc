#include <gtest/gtest.h>

#include <math_eval.h>

TEST(bad_input, double_operator)
{
    try
    {
        math_eval(infix_to_postfix("++"));
        FAIL() << "expected std::invalid_argument";
    }
    catch(const std::invalid_argument& e)
    {
        ASSERT_STREQ("found operator + with less than 2 operands on the stack", e.what());
    }
}

TEST(bad_input, unmatching_parantheses)
{
    try
    {
        math_eval(infix_to_postfix("(4+3))"));
        FAIL() << "expected std::invalid_argument";
    }
    catch(const std::invalid_argument& e)
    {
        ASSERT_STREQ("missing parantheses in expression", e.what());
    }
}

TEST(bad_input, unkown_function)
{
    try
    {
        math_eval(infix_to_postfix("foo(5)"));
        FAIL() << "expected std::invalid_argument";
    }
    catch(const std::invalid_argument& e)
    {
        ASSERT_STREQ("unkown function foo", e.what());
    }
}
