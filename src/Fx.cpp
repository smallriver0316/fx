#include <cmath>
#include <iostream>
#include <stdexcept>

#include <cpr/cpr.h>

#include "fx/Currency.hpp"
#include "fx/Fx.hpp"

Fx::Fx(ULLONG num) : m_number(num) {}

std::string Fx::to1000sSep()
{
  return to1000sSep(std::to_string(m_number));
}

std::string Fx::to1000sSep(std::string num_str)
{
  int dot_pos = num_str.find(".");
  int size = dot_pos == std::string::npos ? num_str.size() : dot_pos;

  for (int i = 3; i < size; i += 3)
  {
    num_str.insert(size - i, ",");
  }
  return num_str;
}

std::string Fx::toEnglish()
{
  return toEnglish(m_number);
}

std::string Fx::toEnglish(ULLONG num)
{
  ULLONG q = num, r;
  std::string result;

  for (int i = 3; q > 0; i += 3)
  {
    r = q % 1000LL;
    q /= 1000LL;

    if (r > 0)
    {
      switch (i)
      {
      case 3:
        if (q > 0)
        {
          result = "and " + std::to_string(r);
        }
        else
        {
          result = std::to_string(r);
        }
        break;
      case 6:
        result = std::to_string(r) + " thousand " + result;
        break;
      case 9:
        result = std::to_string(r) + " million " + result;
        break;
      case 12:
        result = std::to_string(r) + " billion " + result;
        break;
      case 15:
        result = std::to_string(r) + " trillion " + result;
        break;
      case 18:
        result = std::to_string(r) + " quadrillion " + result;
        break;
      case 21:
        result = std::to_string(r) + " quintillion " + result;
        break;
      }
    }
  }
  return result;
}

std::string Fx::exchangeCurrency(std::string prev, std::string next)
{
  std::string result;

  try
  {
    std::string pair_str;
    if (Currency::isForwardPair(prev, next))
    {
      pair_str = Currency::toPairString(prev, next);
    }

    bool is_reversed = false;
    if (Currency::isReversePair(prev, next))
    {
      is_reversed = true;
      pair_str = Currency::toPairString(next, prev);
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
