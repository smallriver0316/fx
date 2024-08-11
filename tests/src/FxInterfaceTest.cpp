#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fx/Formatter.hpp"
#include "fx/FxInterface.hpp"

#include "mock/MockFx.hpp"

TEST(FxInterfaceTest, FxInterface_instance_can_provide_input_currency)
{
  auto fx = std::make_shared<Fx>(123456LL);
  auto fx_interface = FxInterface(fx, "usd", "eur");
  EXPECT_EQ(fx_interface.getInputCurrency(), "USD");
}

TEST(FxInterfaceTest, given_insufficient_input_currency_then_return_empty_string)
{
  auto fx = std::make_shared<Fx>(123456LL);
  auto fx_interface = FxInterface(fx, "us", "eur");
  EXPECT_EQ(fx_interface.getInputCurrency(), "");
}

TEST(FxInterfaceTest, FxInterface_instance_can_provide_output_currency)
{
  auto fx = std::make_shared<Fx>(123456LL);
  auto fx_interface = FxInterface(fx, "usd", "eur");
  EXPECT_EQ(fx_interface.getOutputCurrency(), "EUR");
}

TEST(FxInterfaceTest, given_insufficient_output_currency_then_return_empty_string)
{
  auto fx = std::make_shared<Fx>(123456LL);
  auto fx_interface = FxInterface(fx, "usd", "eu");
  EXPECT_EQ(fx_interface.getOutputCurrency(), "");
}

TEST(FxInterfaceTest, given_currency_pair_then_return_exchanged_value)
{
  auto fx = std::make_shared<MockFx>(123456LL);
  EXPECT_CALL(*fx, fetchCurrencyRate("usd-jpy"))
      .Times(1)
      .WillOnce(::testing::Return(1));

  auto fx_interface = FxInterface(fx, "usd", "jpy");
  EXPECT_EQ(fx_interface.exchange(&Formatter::to1000sSep), "123,456");
}
