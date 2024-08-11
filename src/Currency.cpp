#include <algorithm>
#include <unordered_map>

#include "fx/Currency.hpp"

const std::unordered_map<std::string, CurrencyPair> currency_pair_map = {
    {"USDJPY", CurrencyPair::USDJPY},
    {"EURJPY", CurrencyPair::EURJPY},
    {"EURUSD", CurrencyPair::EURUSD},
    {"AUDCHF", CurrencyPair::AUDCHF},
    {"AUDJPY", CurrencyPair::AUDJPY},
    {"AUDNZD", CurrencyPair::AUDNZD},
    {"AUDUSD", CurrencyPair::AUDUSD},
    {"CADJPY", CurrencyPair::CADJPY},
    {"CHFJPY", CurrencyPair::CHFJPY},
    {"EURAUD", CurrencyPair::EURAUD},
    {"EURCAD", CurrencyPair::EURCAD},
    {"EURCHF", CurrencyPair::EURCHF},
    {"EURGBP", CurrencyPair::EURGBP},
    {"EURNZD", CurrencyPair::EURNZD},
    {"GBPAUD", CurrencyPair::GBPAUD},
    {"GBPCHF", CurrencyPair::GBPCHF},
    {"GBPJPY", CurrencyPair::GBPJPY},
    {"GBPNZD", CurrencyPair::GBPNZD},
    {"GBPUSD", CurrencyPair::GBPUSD},
    {"NZDJPY", CurrencyPair::NZDJPY},
    {"NZDUSD", CurrencyPair::NZDUSD},
    {"USDCAD", CurrencyPair::USDCAD},
    {"USDCHF", CurrencyPair::USDCHF},
    {"ZARJPY", CurrencyPair::ZARJPY}};

bool Currency::isForwardPair(std::string prev, std::string next)
{
  auto pair = prev + next;
  return pair.length() == 6 && currency_pair_map.find(pair) != currency_pair_map.end();
}

bool Currency::isReversePair(std::string prev, std::string next)
{
  auto pair = next + prev;
  return pair.length() == 6 && currency_pair_map.find(pair) != currency_pair_map.end();
}

std::string Currency::toPairString(std::string prev, std::string next)
{
  std::transform(prev.begin(), prev.end(), prev.begin(), ::tolower);
  std::transform(next.begin(), next.end(), next.begin(), ::tolower);

  return prev + "-" + next;
}
