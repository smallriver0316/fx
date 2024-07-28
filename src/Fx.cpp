#include <cmath>

#include "fx/Fx.hpp"

Fx::Fx(ULLONG num) : m_number(num) {}

std::string Fx::to1000sSep()
{
  std::string result = std::to_string(m_number);
  int size = result.size();
  for (int i = 3; i < size; i += 3)
  {
    result.insert(size - i, ",");
  }
  return result;
}

std::string Fx::toEnglish()
{
  ULLONG q = m_number, r;
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
