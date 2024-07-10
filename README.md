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

## How to setup

Installing spdlog is required.

```bash
git clone https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && make -j
sudo make install
```

## How to build

```bash
mkdir build && cd build/
cmake ..
make
```
