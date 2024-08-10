#include <cerrno>
#include <stdexcept>
#include <string>

using ULLONG = unsigned long long;

class ConversionException : public std::runtime_error
{
public:
  ConversionException(const std::string &msg) : std::runtime_error(msg) {}
};

class Formatter
{
public:
  static ULLONG safeStrToUll(std::string num_str);

  static std::string toEnglish(std::string num_str);

  static std::string to1000sSep(std::string num_str);
};
