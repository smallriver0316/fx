#include <string>

using ULLONG = unsigned long long;

class Fx
{
public:
  explicit Fx(ULLONG num);

  std::string to1000sSep();

  std::string toEnglish();

private:
  ULLONG m_number;
};
