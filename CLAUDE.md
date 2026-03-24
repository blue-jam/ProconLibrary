# 指示書

## 概要

C++23で書かれた競技プログラミング(プロコン)ライブラリ。アルゴリズムのカテゴリごとにヘッダ/ソースファイルが整理されており、AOJ (Aizu Online Judge) の問題を使って [Rime](https://github.com/icpc-jag/rime) テストフレームワークで検証を行っている。

## ビルドとテスト

**全検証テストの実行:**
```bash
./verify.sh
```
`online-judge-tools` (`oj`) 経由でAOJからテストデータをダウンロードし、`verify/` 以下の各問題ディレクトリで `rime test` を実行する。

**前提条件:** Python 3, `rime`, `online-judge-tools`
```bash
pip3 install setuptools online-judge-tools rime
```

**CI:** GitHub Actionsがpushごとに `./verify.sh` を実行する (`.github/workflows/ci.yml` 参照)。

**CMake (IDE/コンパイルチェック用):**
```bash
cmake -B build && cmake --build build
```
C++標準はC++23。

## アーキテクチャ

- **ライブラリモジュール** — 各トップレベルディレクトリにアルゴリズムの実装が `.cpp` または `.hpp` ファイルとして格納されており、コンテストの解法に `#include` して使う:
  - `datastructure/` — Fenwick木、セグメント木、遅延評価セグメント木、Union-Find、Link-Cut木、Static Top Tree
  - `geometry/` — 2D幾何プリミティブ (`geometry.cpp`)、凸包、アレンジメント、最近点対、接線
  - `graph/` — Dijkstra、Bellman-Ford、最大流 (Dinic, Edmonds-Karp, Ford-Fulkerson)、SCC、LCA、橋、関節点、トポロジカルソート、Auxiliary Tree; 共通の `graph.hpp` が `Edge`/`Graph` 型を定義
  - `math/` — エラトステネスの篩、FFT、剰余演算
  - `string/` — Aho-Corasick、Suffix Array
  - `misc/template.cpp` — コンテスト用テンプレート (`bits/stdc++.h`、ACL、`ll`・`eps` などの共通マクロ/型定義を含む)

- **検証 (`verify/`)** — Rimeベースのテストプロジェクトで、AOJの問題に対してライブラリの正当性を検証する:
  - ジャッジのカテゴリ別 (`aojcgl/`, `aojdsl/`, `aojgrl/`) およびトピック別 (`geometry/`, `datastructure/`) のサブディレクトリ
  - 各問題は `code/main.cc` (ライブラリを使った解法) と、任意で `test/judge.cc`/`validator.cc` を持つ
  - `verify/download.py` が `oj download` を使ってAOJからテストデータを取得する
  - `verify/common/testlib.h` はテストプロジェクト間で共有される

## コード規約

- ライブラリファイルはテンプレートの `typedef ll Weight` および `using ll = long long` を使用する
- `graph.hpp` の `Edge` の比較演算子は意図的に逆順 (大きい方がtrueを返す) にしており、`priority_queue` の最小ヒープとして使うため
- グラフ表現は2種類が共存: レガシーの `Edge`/`Graph` (typedef ベース) と新しいテンプレート版の `edge<T>`/`graph<T>`
- ドキュメントは日本語、Doxygen形式
