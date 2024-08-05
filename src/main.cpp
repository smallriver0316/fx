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
    std::cout << "Input:  " << fx.to1000sSep();
    if (input_currency_opt->count())
    {
      std::transform(input_currency.begin(), input_currency.end(), input_currency.begin(), ::toupper);
      std::cout << " " << input_currency;
    }
    std::cout << std::endl;

    // exchange currency
    std::string result_num;

    if (input_currency_opt->count() && output_currency_opt->count())
    {
      if (input_currency.length() != 3)
      {
        std::cerr << "Invalid input currency: " << input_currency << std::endl;
        return 1;
      }
      if (output_currency.length() != 3)
      {
        std::cerr << "Invalid output currency: " << output_currency << std::endl;
        return 1;
      }
      std::transform(output_currency.begin(), output_currency.end(), output_currency.begin(), ::toupper);
      result_num = fx.exchangeCurrency(input_currency, output_currency);
    }

    if (format_opt->count())
    {
      if (format == "ENG")
      {
        ULLONG result_ull = std::stoull(result_num);
        std::cout << "Output: " << fx.toEnglish(result_ull);
      }
      else
      {
        std::cerr << "Invalid format: " << format << std::endl;
        return 1;
      }
    }
    else
    {
      std::cout << "Output: " << fx.to1000sSep(result_num);
    }
    if (output_currency_opt->count())
    {
      std::cout << " " << output_currency;
    }
    std::cout << std::endl;
  }
  catch (const ConversionException &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
