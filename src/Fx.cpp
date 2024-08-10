#include <cmath>
#include <iostream>
#include <stdexcept>

#include <cpr/cpr.h>

#include "fx/Currency.hpp"
#include "fx/Fx.hpp"

Fx::Fx(ULLONG num) : m_number(num) {}

std::string Fx::getOriginalNumString()
{
  return std::to_string(m_number);
}

std::string Fx::exchangeCurrency(std::string input_currency, std::string output_currency)
{
  std::string result;

  try
  {
    std::string pair_str;
    if (Currency::isForwardPair(input_currency, output_currency))
    {
      pair_str = Currency::toPairString(input_currency, output_currency);
    }

    bool is_reversed = false;
    if (Currency::isReversePair(input_currency, output_currency))
    {
      is_reversed = true;
      pair_str = Currency::toPairString(output_currency, input_currency);
    }

    if (pair_str.empty())
    {
      throw std::runtime_error("Invalid currency pair");
    }

    auto rate = fetchCurrencyRate(pair_str);
    auto converted = is_reversed ? 1 / rate * static_cast<float>(m_number)
                                 : rate * static_cast<float>(m_number);

    result = std::to_string(converted);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return result;
}

float Fx::fetchCurrencyRate(std::string pair_str)
{
  std::string url = "https://api.excelapi.org/currency/rate?pair=" + pair_str;
  cpr::Response r = cpr::Get(cpr::Url{url});

  if (r.status_code != 200)
  {
    std::cerr << "Error: " << r.status_code << std::endl;
    std::cerr << r.error.message << std::endl;
    throw std::runtime_error("Failed to fetch currency rate");
  }

  return std::stof(r.text);
}
