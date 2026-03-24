---
title: 単一始点最短路 (Dijkstra)
documentation_of: //graph/dijkstra.hpp
---

始点の距離を0とし，近いところから順番に距離を確定していく．負の辺が存在しないグラフのある頂点からすべての頂点に対しての最短距離を求めることができる．

経路復元では，目的地から直前の頂点をたどることで，経路の逆順を復元している．

### 確認済み問題

- POJ 3268
- 経路復元は行っていない

### 参考

- [Spaghetti Source](http://www.prefield.com/algorithm/graph/dijkstra.html) 変数名以外はそのまま
