#include "fx/Currency.hpp"
#include <gtest/gtest.h>

TEST(CurrencyTest, given_pair_of_currencies_is_registered_pair)
{
  std::string currency1 = "usd";
  std::string currency2 = "jpy";
  EXPECT_TRUE(Currency::isForwardPair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_is_not_registered_pair)
{
  std::string currency1 = "cad";
  std::string currency2 = "eur";
  EXPECT_FALSE(Currency::isForwardPair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_is_reverse_pair)
{
  std::string currency1 = "jpy";
  std::string currency2 = "usd";
  EXPECT_TRUE(Currency::isReversePair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_is_not_reverse_pair)
{
  std::string currency1 = "chf";
  std::string currency2 = "zar";
  EXPECT_FALSE(Currency::isReversePair(currency1, currency2));
}

TEST(CurrencyTest, given_pair_of_currencies_then_output_pair_code_string)
{
  std::string currency1 = "usd";
  std::string currency2 = "jpy";
  EXPECT_EQ(Currency::toPairString(currency1, currency2), "usd-jpy");
}
