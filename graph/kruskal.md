---
title: 最小全域森 (Kruskal)
documentation_of: //graph/kruskal.hpp
---

辺のコストを小さいほうから見ていき，2つの頂点がまだ連結していないときはその辺を加え，すでに連結なときは辺を加えない．同じ集合に属しているか否かの判定を
Union-Find木を使用して調べている．

グラフが連結な場合は最小全域木と一致する．また，N個の木からなる最小全域森を計算したい場合は，辺を1つ追加するごとに木の数が1つ減っていくことを利用して求めればよい．

### 計算量

- $O(E \log V)$ (= $O(E \log E)$)

### 確認済み問題

- POJ 3723

### 参考

- [Spaghetti Source](http://www.prefield.com/algorithm/graph/kruskal.html)
- プログラミングコンテストチャレンジブック(p101)
