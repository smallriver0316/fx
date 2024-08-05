#include <string>

using ULLONG = unsigned long long;

class Fx
{
public:
  explicit Fx(ULLONG num);

  std::string to1000sSep();

  std::string to1000sSep(std::string num_str);

  std::string toEnglish();

  std::string toEnglish(ULLONG num);

  std::string exchangeCurrency(std::string prev, std::string next);

private:
  float fetchCurrencyRate(std::string pair_str);

  ULLONG m_number;
};
