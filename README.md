# プロコンのライブラリ

[![verify](https://github.com/blue-jam/ProconLibrary/actions/workflows/verify.yml/badge.svg)](https://github.com/blue-jam/ProconLibrary/actions/workflows/verify.yml)

動作は保証しない．
いろいろな人のライブラリを参考にしてできています．

## 目標

- 作り始める→放置 を繰り返してできたライブラリもどきやソースコードの整理
- C++の新しい機能を活用する
- 使いやすいように書く
- ドキュメントを作る
- 自動整合性チェック＆自動ローカルverify
- テスト用データは自動ダウンロードができるようにする
  (オンラインジャッジに迷惑をかけない範囲で)

## フォーマット・静的解析

[clang-format](https://clang.llvm.org/docs/ClangFormat.html) と [cppcheck](https://cppcheck.sourceforge.io/) を使用。

```bash
cmake -S . -B build
# CMake ターゲットとして実行
cmake --build build --target format        # フォーマット適用
cmake --build build --target format-check  # フォーマットチェック
cmake --build build --target cppcheck      # 静的解析
cmake --build build --target lint          # format-check + cppcheck
```

CIでも push ごとに自動実行される。

## 参考にした参考書・ライブラリ・Webページ

- [Spaghetti Source](http://www.prefield.com/)
- プログラミングコンテストチャレンジブック
- logicmachineさんのライブラリ
- lyozさんのライブラリ
- deq notes
