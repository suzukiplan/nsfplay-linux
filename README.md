# NSFPlay for Linux (CLI)

## About

[NSFPlay](https://github.com/bbbradsmith/nsfplay) を SDL2 のサウンド機能を用いてコマンドラインで動作するようにしたものです。

## How to Build

```bash
# install GNU Make, GCC and other
sudo apt install build-essential

# install SDL2
sudo apt-get install libsdl2-dev

# install ALSA
sudo apt-get install libasound2
sudo apt-get install libasound2-dev

# download repository
git clone https://github.com/suzukiplan/nsfplay-linux

# move to this dir
cd nsfplay-linux

# build
make
```

## Usage

```bash
nsfplay /path/to/file.nsf
```

## License

complex licenses（確認中）
