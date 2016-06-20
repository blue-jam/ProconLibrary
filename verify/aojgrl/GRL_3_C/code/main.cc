#include "misc/template.cpp"
#include "graph/graph.cpp"
#include "graph/scc.cpp"

int main(){
	int V,E;
	cin >> V >> E;
	Graph g(V);
	for(int i = 0; i < E; ++i){
		int s,t;
		cin >> s >> t;
		g[s].push_back(Edge(s,t,0));
	}
	vector<vector<int>> comp;
	getSCC(g, comp);
	vector<int> dict(V);
	for(int i = 0; i < comp.size(); ++i)
		for(auto j: comp[i]) dict[j] = i;
	int Q;
	cin >> Q;
	for(int i = 0; i < Q; ++i){
		int u, v;
		cin >> u >> v;
		cout << (dict[u] == dict[v] ? 1: 0) << endl;
	}
	return 0;
}
