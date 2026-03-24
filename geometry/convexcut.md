---
title: 凸多角形の切断
documentation_of: //geometry/convexcut.hpp
---

与えられた多角形の直線に対して左側を切除し，右側部分を残す．

多角形は反時計回りに点が格納されているものとする．

### 計算量

- N角形に対して $O(N)$

### 確認済み問題

- AOJ 1283

### 使用方法

右側を切除したい場合は，`if(ccw(l[0], l[1], curr) != 1)` の1を-1に置き換える．

### 参考

- [Spaghetti Source](http://www.prefield.com/)
