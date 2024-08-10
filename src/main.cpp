#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "CLI/CLI.hpp"

#include "fx/Formatter.hpp"
#include "fx/FxInterface.hpp"

int main(int argc, char **argv)
{
  CLI::App app{"Exchange given number with specified format"};
  argv = app.ensure_utf8(argv);

  // add version output
  app.set_version_flag("-v,--version", "0.1.0");

  // add format option
  std::string format;
  app.add_option<std::string>("-f, --format", format, "Format to use for output");

  // add input-currency option
  std::string input_currency;
  app.add_option<std::string>("-i, --input-currency", input_currency, "Input currency");

  // add output-currency option
  std::string output_currency;
  app.add_option<std::string>("-o, --output-currency", output_currency, "Output currency");

  std::string input_value;
  app.add_option<std::string>("input_value", input_value, "Input value")->required();

  CLI11_PARSE(app, argc, argv);

  try
  {
    // read value
    ULLONG value = Formatter::safeStrToUll(input_value);
    if (value == 0)
    {
      std::cerr << "Invalid number: " << argv[1] << std::endl;
      return 1;
    }

    std::cout << "Input value: " << value << std::endl;
    std::cout << "Input currency: " << input_currency << std::endl;
    std::cout << "Output currency: " << output_currency << std::endl;
    std::cout << "Format: " << format << std::endl;

    // create Fx instance
    auto fx = std::make_shared<Fx>(value);
    auto fx_interface = FxInterface(fx, input_currency, output_currency);

    // input value
    std::cout << "YOUR INPUT: " << Formatter::to1000sSep(fx->getOriginalNumString());
    if (!fx_interface.getInputCurrency().empty())
    {
      std::cout << " " << fx_interface.getInputCurrency();
    }
    std::cout << std::endl;

    std::string (*format_func)(std::string) = nullptr;
    if (format == "ENG")
    {
      format_func = &Formatter::toEnglish;
    }
    else
    {
      format_func = &Formatter::to1000sSep;
    }

    // output result
    std::cout << "----------> " << fx_interface.exchange(format_func);

    if (!fx_interface.getOutputCurrency().empty())
    {
      std::cout << " " << fx_interface.getOutputCurrency();
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
