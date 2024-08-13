#pragma once

#include <string>

using ULLONG = unsigned long long;

class Fx
{
public:
  explicit Fx(std::string const &num_str);

  std::string getOriginalNumString();

  std::string exchangeCurrency(std::string input_currency, std::string output_currency);

protected:
  // set virtual for unit test
  virtual double fetchCurrencyRate(std::string pair_str);

  virtual double fetchCryptoRate(std::string pair_str);

  virtual double fetchRate(std::string url);

private:
  std::string m_original_num_str;
  ULLONG m_integer_part;
  long double m_decimal_part;
};
