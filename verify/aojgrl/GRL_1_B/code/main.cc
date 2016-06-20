#include "misc/template.cpp"
#include "graph/graph.cpp"
const int INF = 1000000010;
#include "graph/bellman.cpp"

int main(){
	int V, E, r;
	cin >> V >> E >> r;
	Graph g(V);
	for(int i = 0; i < E; ++i){
		int s,t,d;
		cin >> s >> t >> d;
		g[s].push_back(Edge(s,t,d));
	}
	vector<int> dist(V);
	vector<int> prev(V);

	bool res = bellmanFord(g, r, dist, prev);
	if(res){
		cout << "NEGATIVE CYCLE" << endl;
		return 0;
	}
	for(int a : dist){
		if(a == INF)
			cout << "INF" << endl;
		else
			cout << a << endl;
	}
	return 0;
}
