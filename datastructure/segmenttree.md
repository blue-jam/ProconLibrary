---
title: Segment Tree
documentation_of: //datastructure/segmenttree.hpp
---

Range Minimum Queryを解くSegment Tree.

Segment Treeは区間を扱う問題に強い効果を発揮するデータ構造．
完全二分木であり，各接点は区間を管理する．根は区間全体，その子は半分ずつを管理，...葉は1つの要素を管理となる．
n個の要素があるとき，区間についての操作を $O(\log n)$ でできる．
Range Minimum Queryや，DPの高速化に利用される．

空間計算量は $O(n)$ になる．

### 確認済み問題
- POJ 3264

### 参考
- プログラミングコンテストチャレンジブック(p153-p158)
