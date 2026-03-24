#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"
#include "graph/articulation.hpp"
#include "graph/graph.hpp"
#include "misc/template.hpp"

int main() {
    int V, E;
    cin >> V >> E;
    Graph<ll> g(V);
    for (int i = 0; i < E; ++i) {
        int s, t;
        cin >> s >> t;
        addUndirectedEdge(g, s, t, 0);
    }
    vector<int> art;
    vector<vector<int>> comp;
    getArticulation(g, art, comp);
    sort(ALL(art));
    for (auto a : art)
        cout << a << endl;
    return 0;
}
