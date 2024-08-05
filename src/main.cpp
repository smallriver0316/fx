#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "CLI/CLI.hpp"

#include "fx/Fx.hpp"

class ConversionException : public std::runtime_error
{
public:
  ConversionException(const std::string &msg) : std::runtime_error(msg) {}
};

ULLONG safeStrtoull(std::string str)
{
  errno = 0;
  char *end;
  ULLONG value = std::strtoull(str.c_str(), &end, 10);

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

int main(int argc, char **argv)
{
  CLI::App app{"Exchange given number with specified format"};
  argv = app.ensure_utf8(argv);

  // add version output
  app.set_version_flag("-v,--version", "0.1.0");

  // add format option
  std::string format;
  CLI::Option *format_opt = app.add_option<std::string>("-f, --format", format, "Format to use for output");

  // add input-currency option
  std::string input_currency;
  CLI::Option *input_currency_opt = app.add_option<std::string>("-i, --input-currency", input_currency, "Input currency");

  // add output-currency option
  std::string output_currency;
  CLI::Option *output_currency_opt = app.add_option<std::string>("-o, --output-currency", output_currency, "Output currency");

  std::string input_value;
  app.add_option<std::string>("input_value", input_value, "Input value")->required();

  CLI11_PARSE(app, argc, argv);

  try
  {
    ULLONG value = safeStrtoull(input_value);
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
