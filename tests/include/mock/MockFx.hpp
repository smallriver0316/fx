#include "fx/Fx.hpp"
#include <gmock/gmock.h>

class MockFx : public Fx
{
public:
  MockFx(ULLONG num) : Fx(num) {}

  MOCK_METHOD(float, fetchCurrencyRate, (std::string), (override));
};
