#pragma once
#include "misc/template.hpp"

template<typename T>
struct Fenwick {
    vector<T> bit;
    T mod;
    /**
     * 要素数 @a n で初期化する．
     */
    Fenwick(int n) {
        bit = vector<T>(n + 1);
        mod = 0;
    }

    /**
     * @a i 番目の要素に @a v 加える
     * 計算量は \f$O(\log n)\f$ .
     */
    void add(int i, T v) {
        int n = bit.size();
        ++i;
        while (i < n) {
            bit[i] += v;
            if (mod > eps) bit[i] %= mod;
            i += i & -i;
        }
    }

    /**
     * 区間 \f$[0,i)\f$ の総和を返す．
     * 計算量は \f$O(\log n)\f$ .
     */
    T get(int i) {
        T res = 0;
        ++i;
        while (i > 0) {
            res += bit[i];
            if (mod > eps) bit[i] %= mod;
            i -= i & -i;
        }
        return res;
    }
};
