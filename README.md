# NSFPlay for Linux (CLI)

## About

[NSFPlay](https://github.com/bbbradsmith/nsfplay) のコア部分のソースコードを用いて CLI (コマンドライン) で .NSF ファイルを再生できるようにしてみたものです。

音声の再生には SDL2 のサウンド機能を使っています。

## Restrictions

本リポジトリでは、オリジナルの NSFPlay から VRC7 の機能を削除する修正をしています。

> 以下のコマンドを実行すれば VRC7 対応状態にすることができます。
>
> ```
> git checkout 750f51f8e1457c51b60b051c44edc6e9da7b6d93
> ```

本リポジトリは、[VGS-Zero](https://github.com/suzukiplan/vgszero) で NSF を再生する機能を実装するためのコードベースの開発を目的としていて、VRC7 (OPLL) は音色の著作権の関係で VGS-Zero への組み込みが（リーガル的な判断で）できないと判断されたため、VRC7 の実装を削除する対応を行っています。

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

```
./nsfplay [-t track_number]
          /path/to/file.nsf
```

## License

- [./src/cli.cpp](./src/cli.cpp): [LICENSE-cli.txt](./LICENSE-cli.txt) (GPLv3)
  - Copyright (c) 2024, Yoji Suzuki
- Part of NEZplug: [LICENSE-NEZplug.txt](./LICENSE-NEZplug.txt) (Free Software)
  - Copyright (c) Mamiya (mamiya@proc.org.tohoku.ac.jp)
- KM6502: [LICENSE-km6502.txt](./LICENSE-km6502.txt) (PDS)
  - Copyright (c) Mamiya (mamiya@proc.org.tohoku.ac.jp)
- emu2149: [LICENSE-emu2149](./LICENSE-emu2149.txt) (MIT)
  - Copyright (c) 2014 Mitsutaka Okazaki
  - https://github.com/digital-sound-antiques/emu2149
- emu2212: [LICENSE-emu2212](./LICENSE-emu2212.txt) (MIT)
  - Copyright (c) 2014 Mitsutaka Okazaki
  - https://github.com/digital-sound-antiques/emu2212
