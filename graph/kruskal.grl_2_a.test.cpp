#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"
#include "graph/kruskal.hpp"
#include "datastructure/unionfind.hpp"
#include "graph/graph.hpp"
#include "misc/template.hpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int V, E;
    cin >> V >> E;
    Edges<ll> es;
    for (int i = 0; i < E; ++i) {
        int s, t, w;
        cin >> s >> t >> w;
        es.push_back(Edge<ll>(s, t, w));
    }
    cout << kruskal_e(es, V).first << "\n";
    return 0;
}
