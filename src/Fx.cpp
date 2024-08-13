#include <cmath>
#include <iostream>
#include <stdexcept>

#include <cpr/cpr.h>

#include "fx/Currency.hpp"
#include "fx/Formatter.hpp"
#include "fx/Fx.hpp"

Fx::Fx(std::string const &num_str) : m_original_num_str(num_str)
{
  int dot_pos = num_str.find('.');
  std::string integer_part, decimal_part;
  if (dot_pos != std::string::npos)
  {
    integer_part = num_str.substr(0, dot_pos);
    decimal_part = num_str.substr(dot_pos + 1);
  }
  else
  {
    integer_part = num_str;
    decimal_part = "0";
  }

  m_integer_part = Formatter::safeStrToUll(integer_part);
  m_decimal_part = std::stold("0." + decimal_part);
}

std::string Fx::getOriginalNumString()
{
  return m_original_num_str;
}

std::string Fx::exchangeCurrency(std::string input_currency, std::string output_currency)
{
  std::string result;

  try
  {
    std::string pair_str;
    bool is_reversed = false;
    bool is_crypto = false;
    if (Currency::isForwardCurrencyPair(input_currency, output_currency))
    {
      pair_str = Currency::toPairString(input_currency, output_currency);
    }

    if (Currency::isReverseCurrencyPair(input_currency, output_currency))
    {
      is_reversed = true;
      pair_str = Currency::toPairString(output_currency, input_currency);
    }

    if (Currency::isForwardCryptoPair(input_currency, output_currency))
    {
      is_crypto = true;
      pair_str = Currency::toPairString(input_currency, output_currency);
    }

    if (Currency::isReverseCryptoPair(input_currency, output_currency))
    {
      is_reversed = true;
      is_crypto = true;
      pair_str = Currency::toPairString(output_currency, input_currency);
    }

    if (pair_str.empty())
    {
      throw std::runtime_error("Invalid currency pair");
    }

    auto rate = is_crypto ? fetchCryptoRate(pair_str) : fetchCurrencyRate(pair_str);
    auto converted = is_reversed ? (1 / rate * static_cast<long double>(m_integer_part) + 1 / rate * m_decimal_part)
                                 : rate * (static_cast<long double>(m_integer_part) + m_decimal_part);

    result = std::to_string(converted);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return result;
}

double Fx::fetchCurrencyRate(std::string pair_str)
{
  std::string url = "https://api.excelapi.org/currency/rate?pair=" + pair_str;
  return fetchRate(url);
}

double Fx::fetchCryptoRate(std::string pair_str)
{
  std::string url = "https://api.excelapi.org/crypto/rate?pair=" + pair_str;
  return fetchRate(url);
}

double Fx::fetchRate(std::string url)
{
  cpr::Response r = cpr::Get(cpr::Url{url});

  if (r.status_code != 200)
  {
    std::cerr << "Error: " << r.status_code << std::endl;
    std::cerr << r.error.message << std::endl;
    throw std::runtime_error("Failed to fetch currency rate");
  }

  return std::stod(r.text);
}
