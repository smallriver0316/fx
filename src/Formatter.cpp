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
  auto split_nums = splitNumStr(num_str);
  auto integer_part = split_nums.first;
  int size = integer_part.size();

  for (int i = 3; i < size; i += 3)
  {
    integer_part.insert(size - i, ",");
  }

  return integer_part + (split_nums.second != "" ? "." + split_nums.second : "");
}

std::string Formatter::toEnglish(std::string num_str)
{
  auto split_nums = splitNumStr(num_str);

  ULLONG q = safeStrToUll(split_nums.first), r;
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

  return result + (split_nums.second != "" ? "." + split_nums.second : "");
}

std::pair<std::string, std::string> Formatter::splitNumStr(std::string num_str)
{
  int dot_pos = num_str.find(".");
  std::string integer_part, decimal_part = "";
  if (dot_pos != std::string::npos)
  {
    integer_part = num_str.substr(0, dot_pos);
    decimal_part = num_str.length() - dot_pos > 3
                       ? num_str.substr(dot_pos + 1, 3)
                       : num_str.substr(dot_pos + 1);
  }
  else
  {
    integer_part = num_str;
  }

  return std::make_pair(integer_part, decimal_part);
}
