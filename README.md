# fx-cli

CLI tool to convert input number to various styles, such as

- English, German, French, Spanish, and Japanese style
- Currency (JPY/USD, JPY/EUR, AUD/JPY, BTC/JPY, etc)

```bash
$ ./fx -f ENG 123456789
YOUR INPUT: 123,456,789
----------> 123 million 456 thousand and 789
```

## Environment

Please use compiler of the same or upper version than followings.

```bash
cmake --version
cmake version 3.16.3

g++ --version
g++ (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
```

## How to build

Release build will be done like below.

```bash
# build
mkdir build && cd build/
cmake -DCMAKE_BUILD_TYPE=Release ..
make
# install
sudo make install
```

## How to use

```bash
# format by language
## English
$ fx -f ENG 123456789
----------> 123 million 456 thousand and 789

## Germany
$ fx -f DEU 123456789
----------> 123 Millionen 456tausend und 789

## Japanese
$ fx -f JPN 123456789
----------> 1億2345万6789

# exchange by currency rate
## JPY/USD
$ fx -i JPY -o USD 123456789
YOUR INPUT: 123,456,789 JPY
----------> 836,484.812 USD

## USD/EUR
$ fx -i USD -o EUR 123456789
YOUR INPUT: 123,456,789 USD
----------> 113,045,320 EUR

## NZD/USD with English format
$ fx -i -i NZD -o USD -f ENG 123456789
YOUR INPUT: 123,456,789 NZD
----------> 74 million 333 thousand and 336 USD
```

## How to run tests

Unless specify Relase as CMAKE_BUILD_TYPE, unit tests will be enabled.

```bash
# build
mkdir build && cd build/
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
# run tests
ctest --verbose
```
