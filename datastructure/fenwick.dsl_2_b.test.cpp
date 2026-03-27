#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include "datastructure/fenwick.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    Fenwick<int> bit(n + 1);
    for (int i = 0; i < q; ++i) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0) {
            bit.add(x, y);
        } else {
            cout << bit.get(y) - bit.get(x - 1) << "\n";
        }
    }
    return 0;
}
