#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fx/Fx.hpp"
#include "mock/MockFx.hpp"

using ::testing::Return;

TEST(FxTest, fx_instance_can_return_original_number_string)
{
  auto fx = MockFx(123456LL);
  EXPECT_EQ(fx.getOriginalNumString(), "123456");
}

TEST(FxTest, given_currency_pair_then_exchange_value)
{
  auto fx = MockFx(100LL);
  EXPECT_CALL(fx, fetchCurrencyRate("usd-jpy"))
      .Times(1)
      .WillOnce(Return(150.0f));

  EXPECT_EQ(fx.exchangeCurrency("USD", "JPY"), "15000.000000");
}

TEST(FxTest, given_currency_pair_but_only_reversed_pair_exists_then_exchange_value)
{
  auto fx = MockFx(15000LL);
  EXPECT_CALL(fx, fetchCurrencyRate("usd-jpy"))
      .Times(1)
      .WillOnce(Return(150.0f));

  EXPECT_EQ(fx.exchangeCurrency("JPY", "USD"), "100.000000");
}

TEST(FxTest, given_invalid_currency_pair_then_return_empty_string)
{
  auto fx = MockFx(15000LL);
  EXPECT_CALL(fx, fetchCurrencyRate("usd-cny"))
      .Times(0);

  EXPECT_EQ(fx.exchangeCurrency("USD", "CNY"), "");
}
