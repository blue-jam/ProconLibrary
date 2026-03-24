#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"
#include "misc/template.hpp"
#include "graph/lca.hpp"

int main() {
    int n;
    cin >> n;
    vector<int> parent(n, -1);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int c;
            cin >> c;
            parent[c] = i;
        }
    }
    int r = -1;
    for (int i = 0; i < n; ++i)
        if (parent[i] < 0) r = i;
    vector<vector<int>> ancestor;
    vector<int> depth(n);
    initLCA(parent, ancestor);
    calcDepth(parent, r, depth);

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        int w = lca(u, v, depth, ancestor);
        cout << w << endl;
    }
    return 0;
}
