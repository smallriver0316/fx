#include <string>

enum class CurrencyPair
{
  USDJPY,
  EURJPY,
  EURUSD,
  AUDCHF,
  AUDJPY,
  AUDNZD,
  AUDUSD,
  CADJPY,
  CHFJPY,
  EURAUD,
  EURCAD,
  EURCHF,
  EURGBP,
  EURNZD,
  GBPAUD,
  GBPCHF,
  GBPJPY,
  GBPNZD,
  GBPUSD,
  NZDJPY,
  NZDUSD,
  USDCAD,
  USDCHF,
  ZARJPY
};

class Currency
{
public:
  static std::string toPairString(std::string prev, std::string next);
  static bool isForwardPair(std::string prev, std::string next);
  static bool isReversePair(std::string prev, std::string next);
};
