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

enum class CryptoCurrencyPair
{
  BTCJPY,
  BTCUSD,
  ETHJPY,
  ETHUSD,
  LTCJPY,
  LTCUSD,
  XRPJPY,
  XRPUSD,
  XEMJPY,
  XEMUSD,
  MONAJPY,
  ADAUSD,
  BNBBTC,
  BNBUSDT
};

class Currency
{
public:
  static std::string toPairString(std::string prev, std::string next);

  static bool isForwardCurrencyPair(std::string prev, std::string next);

  static bool isReverseCurrencyPair(std::string prev, std::string next);

  static bool isForwardCryptoPair(std::string prev, std::string next);

  static bool isReverseCryptoPair(std::string prev, std::string next);
};
