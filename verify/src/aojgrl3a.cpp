#include "../../graph/graph.cpp"
#include "../../graph/articulation.cpp"

int main(){
	int V,E;
	cin >> V >> E;
	Graph g(V);
	for(int i = 0; i < E; ++i){
		int s,t;
		cin >> s >> t;
		addUndirectedEdge(g, s, t, 0);
	}
	vector<int> art;
	vector<vector<int>> comp;
	getArticulation(g, art, comp);
	sort(ALL(art));
	for(auto a: art)
		cout << a << endl;
	return 0;
}
