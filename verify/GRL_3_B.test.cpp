#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"
#include "misc/template.hpp"
#include "graph/graph.hpp"
#include "graph/bridge.hpp"

bool func(const Edge<ll> &a, const Edge<ll> &b){
	if(a.from != b.from) return a.from < b.from;
	return a.to < b.to;
}

int main(){
	int V,E;
	cin >> V >> E;
	Graph<ll> g(V);
	for(int i = 0; i < E; ++i){
		int s,t;
		cin >> s >> t;
		addUndirectedEdge(g, s, t, 0);
	}
	Edges<ll> brg;
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
