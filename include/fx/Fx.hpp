#pragma once

#include <string>

using ULLONG = unsigned long long;

class Fx
{
public:
  explicit Fx(ULLONG num);

  std::string getOriginalNumString();

  std::string exchangeCurrency(std::string input_currency, std::string output_currency);

protected:
  // for unit test
  virtual float fetchCurrencyRate(std::string pair_str);

private:
  ULLONG m_number;
};
