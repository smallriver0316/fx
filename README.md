# fx

CLI tool to convert input number to various styles, such as

- English expression
- currency (JPY/USD, JPY/EUR, JPY/BTC, etc)

Now this provides functionality to only convert input number to English expression.

```bash
$ ./fx 123456789
123 million 456 thousand and 789
```

## Environment

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

## How to run tests

Unless specify Relase as CMAKE_BUILD_TYPE, unit tests will be enabled.

```bash
# build
mkdir build && cd build/
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
# run tests
ctest
```
