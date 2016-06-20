#include <bits/stdc++.h>
using namespace std; 

#define ALL(x) (x).begin(),(x).end() 
#define EACH(i,c) for(auto i=(c).begin();i!=(c).end();++i)

typedef long long ll;
const double eps = 1e-4;

typedef double Weight;
struct Edge{
    int from, to;
    Weight weight;
    int rev;     // ネットワークフロー時の逆辺
    Edge(int from, int to, Weight weight) :
        from(from), to(to), weight(weight) { }
    Edge(int from, int to, Weight weight, int rev) :
        from(from), to(to), weight(weight), rev(rev){ }
};
bool operator < (const Edge &a, const Edge &b){
    if(a.weight != b.weight) return a.weight > b.weight;
    if(a.from != b.from) return a.from > b.from;
    return  a.to > b.to;
}
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

typedef vector<Weight> Array;
typedef vector<Array> Matrix;

void addFlowEdge(Graph &g, int a, int b, Weight c){
    g[a].push_back(Edge(a, b, c, g[b].size()));
    g[b].push_back(Edge(b, a, 0, g[a].size() - 1));
}
void addUndirectedEdge(Graph &g, int a, int b, Weight c){
    g[a].push_back(Edge(a, b, c, g[b].size()));
    g[b].push_back(Edge(b, a, c, g[a].size() - 1));
}

#include "geometry/geometry.cpp"
#include "geometry/crosspoint.cpp"
#include "geometry/polygon.cpp"
#include "geometry/arrangement.cpp"

int main(){
    int N;
    cin >> N;
    vector<P> ps(N);
    for(int i=0;i<N;++i){
        int x, y;
        cin >> x >> y;
        ps[i] = P(x,y);
    }
    vector<Segment> vs;
    for(int i=0;i<N-1;++i) vs.push_back(Segment(ps[i], ps[i+1]));
    merge_segments(vs);
    Graph g = segmentArrangement(vs, ps);
	vector<vector<int>> pols;
	pols = getPolygon(g, ps);
	vector<double> res;
	EACH(i,pols) {
		Polygon p;
		EACH(j,*i) p.push_back(ps[*j]);
		res.push_back(area(p));
	}
    double sum = 0;
    sort(ALL(res));
    EACH(i, res) sum += *i;
    cout << fixed << setprecision(5) << sum << endl;
    return 0;
}
