/**
 * Union-Find木の実装.
 *
 * 集合の併合，任意の2つの要素が同じ集合に含まれているか調べる機能を持つ．
 * 詳しくは蟻本などを参照のこと．
 *
 * ### 計算量
 * <dl>
 *   <dt>併合，検索</dt><dd>@f$O(\alpha(n))@f$</dd>
 * </dl>
 *
 * ### ソースコード
 *
 * @include unionfind.cpp
 *
 * ### 確認済み問題
 * - POJ 1182
 *
 * ### 参考
 * - プログラミングコンテストチャレンジブック(p81-p86)
 */
struct UnionFind{
    /**
     * 要素の親のindex．親がない場合は-1．
     */
    vector<int> parent;
    /**
     * 要素の木における高さ．葉だと1．
     */
    vector<int> rank;

    /**
     * 要素数nのUnion-Find木の初期化．
     * @param n Union-Find木の要素数．
     */
    UnionFind(int n){ parent = vector<int>(n, -1); rank = vector<int>(n, 0); }

    /**
     * 要素xが含まれている集合の代表元を返す．
     * @param x 集合の代表元を探したい要素．
     * @return 要素xの代表元
     */
    int find(int x){
        if(parent[x] == -1) return x;
        else return (parent[x] = find(parent[x]));
    }

    /**
     * xとyの所属する集合を併合．trueなら併合成功．falseなら，すでに同じ集合．
     * @param x 一つ目の要素（0-indexed）
     * @param y 二つ目の要素（0-indexed）
     * @return 併合に成功したらtrue，xとyが既に同じ集合に属しているならfalse．
     */
    bool unite(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(rank[x] < rank[y])
            parent[x] = y;
        else
            parent[y] = x;
        if(rank[x] == rank[y])
            ++rank[x];
        return true;
    }

    /**
     * xとyの所属する集合が同じかどうか調べる．
     * @param x 一つ目の要素（0-indexed）
     * @param y 二つ目の要素（0-indexed）
     * @return xとyで表される要素が同じ集合に属していればtrue．
     */
    bool same(int x, int y){
        return find(x) == find(y);
    }
};
