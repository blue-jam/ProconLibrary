/**
 * Range Minimum Queryを解くSegment Tree.
 *
 * @tparam T 管理するデータ構造の型
 *
 * Segment Treeは区間を扱う問題に強い効果を発揮するデータ構造．
 * 完全二分木であり，各接点は区間を管理する．根は区間全体，その子は半分ずつを管理，．．．葉は1つの要素を管理となる．
 * n個の要素があるとき，区間についての操作を@f$O(\log n)@f$でできる．
 * Range Minimum Queryや，DPの高速化に利用される．
 *
 * 空間計算量は @f$O(n)@f$ になる．
 *
 * ### ソースコード
 *
 * @include segmenttree.cpp
 *
 * ### 確認済み問題
 * - POJ 3264
 *
 * ### 参考
 * - プログラミングコンテストチャレンジブック(p153-p158)
 */
template<typename T>
struct SegmentTree{
    int n;
    vector<T> dat;
    T ign;

    /**
     * Segment Treeを全て@a ignore で初期化する．
     * 計算量は @f$O(n)@f$ .
     * @param n_ Segment Treeの要素数
     * @param ignore 無視されるデータ．例えば，Range Minimum Queryでは，正の無限大を用いる．
     */
    SegmentTree(int n_, T ignore){
        for(n = 1; n < n_; n *= 2);
        ign = ignore;
        dat = vector<T>(n * 2 - 1, ignore);
    }

    /**
     * Segment Treeを与えられたベクタを初期値として初期化する．
     * 計算量は @f$O(n)@f$ .
     * @param v 初期化するデータを与えるベクタ
     */
    void init(vector<T> &v){
        for(int i = 0; i < v.size(); ++i){
            dat[i + n - 1] = v[i];
        }
        for(int k = n - 2; k >= 0; --k){
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    /**
     * @a k 番目を値 @a d に更新する．
     * 計算量は @f$O(\log n)@f$ .
     * @param k 更新する要素を表すindex. (0-indexed)
     * @param d 新しい値
     */
    void update(int k, T d){
        k += n - 1;
        dat[k] = d;
        while(k > 0){
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    T get(int a, int b, int k, int l, int r){
        if(b <= l || r <= a)
            return ign;
        if(a <= l && r <= b){
            return dat[k];
        }
        else{
            T vl = get(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = get(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }

    /**
     * 区間 \f$[a, b)\f$ 内での最小値を返す．
     * @param a 区間の開始位置．(0-indexed)
     * @param b 区間の終了位置．(0-indexed)
     * @return クエリの結果
     */
    T query(int a, int b){
        return get(a, b, 0, 0, n);
    }
};
