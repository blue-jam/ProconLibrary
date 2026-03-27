#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"
#include "datastructure/segmenttree.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    SegmentTree<int> st(n, INT_MAX);

    for (int i = 0; i < q; ++i) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0)
            st.update(x, y);
        else
            cout << st.query(x, y + 1) << "\n";
    }
    return 0;
}
