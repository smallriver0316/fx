#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "spdlog/spdlog.h"

#include "fx/Fx.hpp"

class ConversionException : public std::runtime_error
{
public:
  ConversionException(const std::string &msg) : std::runtime_error(msg) {}
};

ULLONG safeStrtoull(const char *str)
{
  errno = 0;
  char *end;
  ULLONG value = std::strtoull(str, &end, 10);

  if (errno == ERANGE)
  {
    std::ostringstream msg;
    msg << "Out of range value: " << str;
    throw ConversionException(msg.str());
  }
  else if (*end != '\0')
  {
    std::ostringstream msg;
    msg << "Invalid number: " << str;
    throw ConversionException(msg.str());
  }

  return value;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    spdlog::error("Usage: {} <integer>", argv[0]);
    return 1;
  }

  try
  {
    ULLONG value = safeStrtoull(argv[1]);
    if (value == 0 && argv[1][0] != '0')
    {
      spdlog::error("Invalid number: {}", argv[1]);
      return 1;
    }

    auto fx = Fx(value);
    std::cout << fx.expressEng() << std::endl;
  }
  catch (const ConversionException &e)
  {
    spdlog::error(e.what());
    return 1;
  }

  return 0;
}
