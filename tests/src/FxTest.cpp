#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fx/Fx.hpp"
#include "mock/MockFx.hpp"

using ::testing::_;
using ::testing::Return;

TEST(FxTest, fx_instance_can_return_original_number_string)
{
  auto fx = MockFx(123456LL);
  EXPECT_EQ(fx.getOriginalNumString(), "123456");
}

TEST(FxTest, given_currency_pair_then_exchange_value)
{
  auto fx = MockFx(100LL);
  EXPECT_CALL(fx, fetchCurrencyRate(_))
      .Times(1)
      .WillOnce(Return(150.0f));

  EXPECT_EQ(fx.exchangeCurrency("USD", "JPY"), "15000.000000");
}

TEST(FxTest, given_currency_pair_but_only_reversed_pair_exists_then_exchange_value)
{
  auto fx = MockFx(15000LL);
  EXPECT_CALL(fx, fetchCurrencyRate(_))
      .Times(1)
      .WillOnce(Return(150.0f));

  EXPECT_EQ(fx.exchangeCurrency("JPY", "USD"), "100.000000");
}

TEST(FxTest, given_invalid_currency_pair_then_return_empty_string)
{
  auto fx = MockFx(15000LL);
  EXPECT_CALL(fx, fetchCurrencyRate(_))
      .Times(0);

  EXPECT_EQ(fx.exchangeCurrency("USD", "CNY"), "");
}

TEST(FxTest, given_crypto_pair_then_exchange_value)
{
  auto fx = MockFx(100LL);
  EXPECT_CALL(fx, fetchCryptoRate(_))
      .Times(1)
      .WillOnce(Return(150.0f));

  EXPECT_EQ(fx.exchangeCurrency("BTC", "USD"), "15000.000000");
}

TEST(FxTest, given_crypto_pair_but_only_reversed_pair_exists_then_exchange_value)
{
  auto fx = MockFx(15000LL);
  EXPECT_CALL(fx, fetchCryptoRate(_))
      .Times(1)
      .WillOnce(Return(150.0f));

  EXPECT_EQ(fx.exchangeCurrency("USD", "BTC"), "100.000000");
}
