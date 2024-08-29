#include <memory>

#include "fx/Fx.hpp"

class FxInterface
{
public:
  explicit FxInterface(std::shared_ptr<Fx> p_fx, std::string const &input_currency, std::string const &output_currency);

  std::string exchange(std::string (*formatter)(std::string) = [](std::string s)
                       { return s; });

  std::string getOriginalNumString();

  std::string getInputCurrency();

  std::string getOutputCurrency();

private:
  std::shared_ptr<Fx> m_fx;
  std::string m_input_currency;
  std::string m_output_currency;
};
