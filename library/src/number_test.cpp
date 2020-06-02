#include <example/number.hpp>

#include <gtest/gtest.h>

namespace {

class NumberTestFixture : public ::testing::Test
{
protected:
    Example::Number n;
};

TEST_F(NumberTestFixture, Operators) {
    n = 42;
    EXPECT_EQ(42, (int)n);
}

TEST_F(NumberTestFixture, Factorial) {
    n = 6;
    EXPECT_EQ(720, n.Factorial());
}

TEST_F(NumberTestFixture, Fibonacci) {
    n = 0;
    EXPECT_EQ(0, n.Fibonacci());

    n = 6;
    EXPECT_EQ(8, n.Fibonacci());

    n = 41;
    EXPECT_EQ(165580141, n.Fibonacci());
}

}  // namespace