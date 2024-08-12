#include "fx/Fx.hpp"
#include <gmock/gmock.h>

class MockFx : public Fx
{
public:
  MockFx(std::string num_str) : Fx(num_str) {}

  MOCK_METHOD(double, fetchCurrencyRate, (std::string), (override));

  MOCK_METHOD(double, fetchCryptoRate, (std::string), (override));
};
