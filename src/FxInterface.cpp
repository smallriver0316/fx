#include <algorithm>

#include "fx/FxInterface.hpp"

FxInterface::FxInterface(std::shared_ptr<Fx> p_fx, std::string const &input_currency, std::string const &output_currency)
    : m_fx(std::move(p_fx)), m_input_currency(input_currency), m_output_currency(output_currency)
{
  std::transform(m_input_currency.begin(), m_input_currency.end(), m_input_currency.begin(), ::toupper);
  std::transform(m_output_currency.begin(), m_output_currency.end(), m_output_currency.begin(), ::toupper);
}

std::string FxInterface::exchange(std::string (*formatter)(std::string))
{
  std::string result;
  if (!m_input_currency.empty() && !m_output_currency.empty())
  {
    result = m_fx->exchangeCurrency(m_input_currency, m_output_currency);
  }
  else
  {
    result = m_fx->getOriginalNumString();
  }

  return formatter(result);
}

std::string FxInterface::getOriginalNumString()
{
  return m_fx->getOriginalNumString();
}

std::string FxInterface::getInputCurrency()
{
  if (m_input_currency.length() == 3)
  {
    return m_input_currency;
  }
  return "";
}

std::string FxInterface::getOutputCurrency()
{
  if (m_output_currency.length() == 3)
  {
    return m_output_currency;
  }
  return "";
}
