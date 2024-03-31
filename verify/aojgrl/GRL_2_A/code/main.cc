#include "misc/template.cpp"
#include "datastructure/unionfind.cpp"
#include "graph/graph.hpp"
#include "graph/kruskal.cpp"

int main(){
	int V,E;
	cin >> V >> E;
	Edges es;
	for(int i = 0; i < E; ++i){
		int s, t, w;
		cin >> s >> t >> w;
		es.push_back(Edge(s,t,w));
	}
	cout << kruskal_e(es, V).first << endl;
	return 0;
}
