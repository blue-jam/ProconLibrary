/**
 * Binary Indexed Tree(Fenwick Tree).
 * Segment Treeが任意の範囲に対する操作ができるのに対して，BITは始点からある点までの範囲に対する操作しか行えない．
 * 反面，Segment Treeよりはるかに実装コストが低い．
 *
 * 0-indexedで管理されている．
 * modを0より大きくすると，modをとるようになる
 *
 * @tparam T 管理するデータ型
 *
 * 単純に実装した場合は始点が1になるが，工夫をして始点を0にずらしている．始点を1にしたい場合はupdate，getにある先頭の++iを消す．
 *
 * ### ソースコード
 *
 * @include fenwick.cpp
 *
 * ### 確認済み問題
 * - AOJ 2326(Number Sorting)
 *
 * ### 参考
 * - プログラミングコンテストチャレンジブック
 */
template<typename T>
struct Fenwick{
    vector<T> bit;
    T mod;
    /**
     * 要素数 @a n で初期化する．
     */
    Fenwick(int n){
        bit = vector<T>(n + 1);
        mod = 0;
    }

    /**
     * @a i 番目の要素に @a v 加える
     * 計算量は \f$O(\log n)\f$ .
     */
    void add(int i, T v){
        int n = bit.size();
        ++i;
        while(i < n){
            bit[i] += v;
            if(mod > eps) bit[i] %= mod;
            i += i & -i;
        }
    }

    /**
     * 区間 \f$[0,i)\f$ の総和を返す．
     * 計算量は \f$O(\log n)\f$ .
     */
    T get(int i){
        T res = 0;
        ++i;
        while(i > 0){
            res += bit[i];
            if(mod > eps) bit[i] %= mod;
            i -= i & -i;
        }
        return res;
    }
};
