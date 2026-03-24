# 指示書

## 概要

C++23で書かれた競技プログラミング(プロコン)ライブラリ。アルゴリズムのカテゴリごとにヘッダ/ソースファイルが整理されており、AOJ (Aizu Online Judge) の問題を使って [online-judge-tools/verification-helper](https://github.com/online-judge-tools/verification-helper) (`oj-verify`) で検証を行っている。

## ビルドとテスト

**全検証テストの実行:**
```bash
oj-verify run
```
`oj-verify` が `verify/*.test.cpp` 内の `#define PROBLEM "url"` を読み取り、テストデータのダウンロード・コンパイル・実行・結果比較を自動で行う。

**前提条件:** Python 3, `online-judge-tools`
```bash
pip3 install online-judge-tools online-judge-verify-helper
```

**CI:** GitHub Actionsがpushごとに `oj-verify run` を実行する (`.github/workflows/ci.yml` 参照)。

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

- **検証 (`verify/`)** — `oj-verify` ベースのテストで、AOJの問題に対してライブラリの正当性を検証する:
  - 各問題は `verify/{problem_id}.test.cpp` として配置
  - ファイル先頭の `#define PROBLEM "url"` でジャッジのURLを指定
  - 浮動小数点比較が必要な問題は `#define ERROR 1e-8` 等で許容誤差を指定
  - 設定は `.verify-helper/config.toml` に記載

## コード規約

- ライブラリファイルはテンプレートの `typedef ll Weight` および `using ll = long long` を使用する
- `graph.hpp` の `Edge` の比較演算子は意図的に逆順 (大きい方がtrueを返す) にしており、`priority_queue` の最小ヒープとして使うため
- グラフ表現は2種類が共存: レガシーの `Edge`/`Graph` (typedef ベース) と新しいテンプレート版の `edge<T>`/`graph<T>`
- ドキュメントは日本語、Doxygen形式
