---
title: グラフの要素
documentation_of: //graph/graph.hpp
---

### グラフの要素
グラフは各頂点から出て行く辺をリストとして保持する隣接リスト表現と各頂点間に辺が存在する情報を記録する隣接行列表現がある．
それぞれ利点があるので状況に応じて使い分けること．

- **隣接リスト**: 頂点を基準に考えればいいときに有向．重複辺も扱える．
- **隣接行列**: $O(E)$ が $O(V^2)$ になる．密グラフや，頂点数が少ないグラフについて効率よく扱える．重複辺を扱いにくい．

Edgeのless演算子は，weightの小さい辺が小さいと判定される通常の順序で定義している．
priority_queueでweightの小さいほうを先に取り出す場合は，以下のようにgreaterを指定する．

```cpp
priority_queue<Edge<ll>, vector<Edge<ll>>, greater<Edge<ll>>> Q;
```

Graphは隣接リストを保持する軽量な構造体で，`g[v]` で頂点 `v` から出る辺の一覧を取得できる．

```cpp
Graph<ll> g(n);
g.add_directed(a, b, w);
g.add_undirected(a, b, w);
```

辺の端点を持つvectorからグラフを構築できる．デフォルトでは1-indexedの入力として扱う．

```cpp
vector<int> A, B;
vector<ll> W;

auto g1 = Graph<ll>::directed(n, A, B, W);              // 1-indexed, weighted, directed
auto g2 = Graph<ll>::undirected(n, A, B, W);            // 1-indexed, weighted, undirected
auto g3 = Graph<ll>::directed(n, A, B);                 // 1-indexed, unweighted, directed
auto g4 = Graph<ll>::undirected(n, A, B, IndexBase::Zero); // 0-indexed, unweighted, undirected
```
