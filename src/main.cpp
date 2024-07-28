#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
    std::cerr << "Usage: " << argv[0] << " <integer>" << std::endl;
    return 1;
  }

  try
  {
    ULLONG value = safeStrtoull(argv[1]);
    if (value == 0 && argv[1][0] != '0')
    {
      std::cerr << "Invalid number: " << argv[1] << std::endl;
      return 1;
    }

    auto fx = Fx(value);
    std::cout << fx.to1000sSep() << std::endl;
    std::cout << "English expression: " << fx.toEnglish() << std::endl;
  }
  catch (const ConversionException &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
