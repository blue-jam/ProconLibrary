---
title: Static Top Tree
documentation_of: //datastructure/statictoptree.hpp
---

Static Top Tree.

木をHL分解した上で，Compress, Rake, Add Edge, Add Vertex, Vertexの5つの操作により木の構造を表現する．
頂点の値を更新した際に，根までのパス上のノードの値を更新することで，木全体の集約値を効率的に管理できる．
