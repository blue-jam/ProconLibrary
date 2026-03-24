---
title: 複数パターンの検索 (Aho-Corasick法)
documentation_of: //string/aho.hpp
---

複数の文字列パターンについていったんTrie木を構築した後，KMP法を実行しながら失敗したときのリンクを作成する．これにより，複数の文字列についてのマッチングが同時に行えるパターンマッチングオートマトンが作成できる．

### 計算量

- PMAの構築: $O(m)$
- パターンの検索: $O(n+m)$

$m$ はパターンの文字列の長さの総和．$n$ は検索する文字列の長さ．

### 確認済み問題

- SRM519 Div1 Medium (RequiredSubstrings)

### 参考

- [Spaghetti Source](http://www.prefield.com/algorithm/string/aho_corasick.html)

ソースコードの参考．状態遷移の際に何回もリンク先へ飛ぶ必要がある，ほかの文字列を部分列として含んでいるときの対策がないといった点を改善した．また，DPを行いやすいように状態に一意のインデックスを割り振るようにした．
