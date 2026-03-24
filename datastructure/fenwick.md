---
title: Binary Indexed Tree (Fenwick Tree)
documentation_of: //datastructure/fenwick.hpp
---

Binary Indexed Tree(Fenwick Tree).
Segment Treeが任意の範囲に対する操作ができるのに対して，BITは始点からある点までの範囲に対する操作しか行えない．
反面，Segment Treeよりはるかに実装コストが低い．

0-indexedで管理されている．
modを0より大きくすると，modをとるようになる．

単純に実装した場合は始点が1になるが，工夫をして始点を0にずらしている．始点を1にしたい場合はupdate，getにある先頭の++iを消す．

### 確認済み問題
- AOJ 2326(Number Sorting)

### 参考
- プログラミングコンテストチャレンジブック
