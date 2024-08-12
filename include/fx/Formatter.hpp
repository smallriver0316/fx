#include <cerrno>
#include <stdexcept>
#include <string>
#include <utility>

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

  static std::pair<std::string, std::string> splitNumStr(std::string num_str);

  static std::string to1000sSep(std::string num_str);

  static std::string toEnglish(std::string num_str);

  static std::string toGerman(std::string num_str);

  static std::string toSpanish(std::string num_str);

  static std::string toJapanese(std::string num_str);

  static std::string toFrench(std::string num_str);
};
