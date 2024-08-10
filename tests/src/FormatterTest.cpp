#include "fx/Formatter.hpp"
#include <gtest/gtest.h>

TEST(FormatterTest, given_number_then_convert_to_expression_with_thousands_separator)
{
  EXPECT_EQ(Formatter::to1000sSep("12345678901234567890"), "12,345,678,901,234,567,890");
}

TEST(FormatterTest, given_number_then_convert_to_english_expression)
{
  EXPECT_EQ(Formatter::toEnglish("12345678901234567890"), "12 quintillion 345 quadrillion 678 trillion 901 billion 234 million 567 thousand and 890");
}

// TEST(FxTest, fetch_currency_rate)
// {
//   auto fx = Fx(12345678901234567890ULL);
//   auto rate = fx.fetchCurrencyRate("usd-jpy");
//   testing::internal::GetCapturedStdout();
//   std::cout << rate << std::endl;
//   EXPECT_EQ(rate, "hoge");
// }
