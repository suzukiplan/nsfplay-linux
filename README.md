# NSFPlay for Linux (CLI)

## About

[NSFPlay](https://github.com/bbbradsmith/nsfplay) のコア部分のソースコードを用いて CLI (コマンドライン) で .NSF ファイルを再生できるようにしてみたものです。

音声の再生には SDL2 のサウンド機能を使っています。

## Restrictions

本リポジトリでは、オリジナルの NSFPlay から VRC7 (OPLL) と FME7 (AY-3-8910) の機能を削除する修正をしています。

> 以下のコマンドを実行すれば VRC7 と FME7 に対応した状態にすることができます。
>
> ```
> git checkout 750f51f8e1457c51b60b051c44edc6e9da7b6d93
> ```

本リポジトリは、[VGS-Zero](https://github.com/suzukiplan/vgszero) で NSF を再生する機能を実装するためのコードベースの開発を目的としていて、VRC7 (OPLL) は音色の著作権の関係で VGS-Zero への組み込みができないと判断（リーガル的な判断）がされたため、VRC7 の実装を削除する対応を行っています。

VRC7 以外の機能についてはメンテナンスの簡略化を目的として削除しています。

また、RaspberryPi Zero 2W のベアメタル環境で動作させることを目的として STL を使わない形に修正している影響で nsfconfig による設定の可変化を削除して、固定値の設定による nsfplay の改変モジュール ([src/nsfplay.hpp](src/nsfplay.hpp)）を用いて NSF の再生を行っています。（動作上の違いは無い...はず）

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

- [./src/nsfplay.hpp](./src/nsfplay.hpp): [LICENSE-NSFPlay-alter.txt](./LICENSE-NSFPlay-alter.txt) (GPLv3)
  - Copyright (c) Mamiya (mamiya@proc.org.tohoku.ac.jp)
  - Copyright (c) 2024, Yoji Suzuki
- [./src/cli.cpp](./src/cli.cpp): [LICENSE-cli.txt](./LICENSE-cli.txt) (GPLv3)
  - Copyright (c) 2024, Yoji Suzuki
- Part of NEZplug: [LICENSE-NEZplug.txt](./LICENSE-NEZplug.txt) (Free Software)
  - Copyright (c) Mamiya (mamiya@proc.org.tohoku.ac.jp)
- KM6502: [LICENSE-km6502.txt](./LICENSE-km6502.txt) (PDS)
  - Copyright (c) Mamiya (mamiya@proc.org.tohoku.ac.jp)
