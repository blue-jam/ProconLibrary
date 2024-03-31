#include "misc/template.cpp"
#include "graph/graph.hpp"
#include "graph/topologicalsort.cpp"

int main(){
	int V, E;
	cin >> V >> E;
	Graph g(V);
	for(int i = 0; i < E; ++i){
		int s,t;
		cin >> s >> t;
		g[s].push_back(Edge(s,t,0));
	}
	vector<int> v;
	topologicalSort(g, v);
	for(auto a: v){
		cout << a << endl;
	}
	return 0;
}
