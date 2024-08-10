#include "fx/Currency.hpp"
#include <gtest/gtest.h>

TEST(CurrencyTest, given_pair_of_currencies_is_registered_pair)
{
  std::string currency1 = "USD";
  std::string currency2 = "JPY";
  EXPECT_TRUE(Currency::isForwardPair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_is_not_registered_pair)
{
  std::string currency1 = "CAD";
  std::string currency2 = "EUR";
  EXPECT_FALSE(Currency::isForwardPair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_is_reverse_pair)
{
  std::string currency1 = "JPY";
  std::string currency2 = "USD";
  EXPECT_TRUE(Currency::isReversePair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_is_not_reverse_pair)
{
  std::string currency1 = "CHF";
  std::string currency2 = "ZAR";
  EXPECT_FALSE(Currency::isReversePair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_then_output_pair_code_string)
{
  std::string currency1 = "USD";
  std::string currency2 = "JPY";
  EXPECT_EQ(Currency::toPairString(currency1, currency2), "usd-jpy");
}
