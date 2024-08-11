#include "fx/Formatter.hpp"

ULLONG Formatter::safeStrToUll(std::string num_str)
{
  errno = 0;
  char *end;
  ULLONG value = std::strtoull(num_str.c_str(), &end, 10);

  if (errno == ERANGE)
  {
    throw ConversionException("Out of range value: " + num_str);
  }
  else if (*end != '\0')
  {
    throw ConversionException("Invalid number: " + num_str);
  }

  return value;
}

std::string Formatter::to1000sSep(std::string num_str)
{
  int dot_pos = num_str.find(".");
  int size = dot_pos == std::string::npos ? num_str.size() : dot_pos;

  for (int i = 3; i < size; i += 3)
  {
    num_str.insert(size - i, ",");
  }
  return num_str;
}

std::string Formatter::toEnglish(std::string num_str)
{
  ULLONG q = safeStrToUll(num_str), r;
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
