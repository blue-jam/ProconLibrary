#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B"
#include "graph/topologicalsort.hpp"
#include "graph/graph.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int V, E;
    cin >> V >> E;
    Graph<ll> g(V);
    for (int i = 0; i < E; ++i) {
        int s, t;
        cin >> s >> t;
        g[s].push_back(Edge<ll>(s, t, 0));
    }
    vector<int> v;
    topologicalSort(g, v);
    for (auto a : v) {
        cout << a << "\n";
    }
    return 0;
}
