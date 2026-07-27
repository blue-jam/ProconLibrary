#pragma once

#include <atcoder/all>
#include <bits/stdc++.h>

using namespace std;
using namespace atcoder;

#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define RREP(i, n) for (int i = (int)(n)-1; i >= 0; --i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define RFOR(i, a, b) for (int i = (int)(b)-1; i >= (int)(a); --i)

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T, class U>
bool chmin(T& a, U&& b) {
    if (a > b) {
        a = std::forward<U>(b);
        return true;
    }
    return false;
}

template<class T, class U>
bool chmax(T& a, U&& b) {
    if (a < b) {
        a = std::forward<U>(b);
        return true;
    }
    return false;
}

template<class T>
constexpr T floor_div(T a, T b) {
    assert(b != 0);
    T q = a / b;
    T r = a % b;
    if (r != 0 && ((r > 0) != (b > 0))) --q;
    return q;
}

template<class T>
constexpr T ceil_div(T a, T b) {
    assert(b != 0);
    T q = a / b;
    T r = a % b;
    if (r != 0 && ((r > 0) == (b > 0))) ++q;
    return q;
}

template<class T>
void sort_unique(vector<T>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

#ifndef EPS
const double eps = 1e-10;
#else
const double eps = EPS;
#endif
