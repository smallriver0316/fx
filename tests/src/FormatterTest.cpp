#include "fx/Formatter.hpp"
#include <gtest/gtest.h>

TEST(FormatterTest, given_number_then_convert_unsigned_long_long_value)
{
  unsigned long long expected = 1234567890LL;
  EXPECT_EQ(Formatter::safeStrToUll("1234567890"), expected);
}

TEST(FormatterTest, given_too_large_value_then_throw_exception)
{
  EXPECT_THROW(
      Formatter::safeStrToUll("123456789012345678901234567890"),
      ConversionException);
}

TEST(FormatterTest, given_number_then_convert_to_expression_with_thousands_separator)
{
  EXPECT_EQ(
      Formatter::to1000sSep("12345678901234567890"),
      "12,345,678,901,234,567,890");
}

TEST(FormatterTest, given_number_then_convert_to_english_expression)
{
  EXPECT_EQ(
      Formatter::toEnglish("12345678901234567890"),
      "12 quintillion 345 quadrillion 678 trillion 901 billion 234 million 567 thousand and 890");
}

TEST(FormatterTest, given_number_with_decimal_part_then_split_into_integer_and_decimal_parts)
{
  auto result = Formatter::splitNumStr("1234567890.1234567890");
  EXPECT_EQ(result.first, "1234567890");
  EXPECT_EQ(result.second, "123");
}

TEST(FormatterTest, given_number_with_decimal_part_and_trailing_zeros_then_cut_off_them_and_return)
{
  auto result = Formatter::splitNumStr("1234567890.10000000");
  EXPECT_EQ(result.second, "1");
}
