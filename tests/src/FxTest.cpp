#include "fx/Fx.hpp"
#include <gtest/gtest.h>

TEST(FxTest, given_number_then_convert_to_expression_with_thousands_separator)
{
  auto fx = Fx(12345678901234567890ULL);
  EXPECT_EQ(fx.to1000sSep(), "12,345,678,901,234,567,890");
}

TEST(FxTest, given_number_then_convert_to_english_expression)
{
  auto fx = Fx(12345678901234567890ULL);
  EXPECT_EQ(fx.toEnglish(), "12 quintillion 345 quadrillion 678 trillion 901 billion 234 million 567 thousand and 890");
}
