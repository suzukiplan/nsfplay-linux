# NSFPlay for Linux (CLI)

## About

[NSFPlay](https://github.com/bbbradsmith/nsfplay) のコア部分のソースコードを用いて CLI (コマンドライン) で .NSF ファイルを再生できるようにしてみたものです。

音声の再生には SDL2 のサウンド機能を使っています。

## How to Execute

実行モジュールは配布していないのでビルドが必要です。

ビルド & 動作確認は Linux でのみしています。（若干手直しすれば macOS でも動かせるかもしれません）

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

ビルドが成功すると本リポジトリの [test.nsf](./test.nsf) が再生されます。

## Usage

```bash
./nsfplay /path/to/file.nsf
```

## License

complex licenses（確認中）
