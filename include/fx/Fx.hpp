#include <string>

using ULLONG = unsigned long long;

class Fx
{
public:
  Fx(ULLONG num);

  std::string express1000sSep();

  std::string expressEng();

private:
  ULLONG m_number;
};
