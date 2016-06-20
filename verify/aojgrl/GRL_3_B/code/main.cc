#include "misc/template.cpp"
#include "graph/graph.cpp"
#include "graph/bridge.cpp"

bool func(const Edge &a, const Edge &b){
	if(a.from != b.from) return a.from < b.from;
	return a.to < b.to;
}

int main(){
	int V,E;
	cin >> V >> E;
	Graph g(V);
	for(int i = 0; i < E; ++i){
		int s,t;
		cin >> s >> t;
		addUndirectedEdge(g, s, t, 0);
	}
	Edges brg;
	vector<vector<int>> comp;
	getBridge(g, brg, comp);
	EACH(i, brg)
		if(i->from > i->to)
			swap(i->from, i->to);
	sort(ALL(brg), func);
	for(auto b: brg)
		cout << b.from << " " << b.to << endl;
	return 0;
}
