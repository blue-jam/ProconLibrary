#include "../../geometry/geometry.cpp"
#include "../../geometry/crosspoint.cpp"

typedef double Weight;
const Weight INF = 1e+10;
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

void dijkstra(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge> Q;     // a < b <-> a.weight > b.weight
    Q.push(Edge(-2, s, 0));
    while(!Q.empty()){
        Edge e = Q.top(); Q.pop();
        if(prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        EACH(i, g[e.to]){
        //for(Edges::const_iterator i=g[e.to].begin(); i!=g[e.to].end(); ++i){    //マクロが使えないとき
            if(dist[i -> to] > dist[i -> from] + i -> weight){
                dist[i -> to] = dist[i -> from] + i -> weight;
                Q.push(Edge(i -> from, i -> to, dist[i -> to]));
            }
        }
    }
}

vector<Segment> star(int x, int y, int a, int r){
	P p(x,y);
	vector<P> vp;
	for(int i = 0; i < 5; ++i){
		vp.push_back(p + polar((double)r, (90.0 + a + 360 / 5 * i) * PI / 180.0));
	}
	return vector<Segment>{
			Segment(vp[0], vp[2]),
			Segment(vp[2], vp[4]),
			Segment(vp[4], vp[1]),
			Segment(vp[1], vp[3]),
			Segment(vp[3], vp[0])
		};
}

int main(){
	for(;;){
		int N, M, L;
		cin >> N >> M >> L;
		if(!N) return 0;
		vector<vector<Segment>> v;
		for(int i = 0; i < N; ++i){
			int x, y, a, r;
			cin >> x >> y >> a >> r;
			v.push_back(star(x, y, a, r));
		}
		Graph g(N);
		for(int i = 0; i < N; ++i) for(int j = i+1; j < N; ++j) {
			double d = 1e+10;
			for(int k=0;k<5;++k) for(int l=0;l<5;++l)
				d = min(d, distanceSS(v[i][k], v[j][l]));
			addUndirectedEdge(g, i, j, d);
		}
		vector<Weight> dist(N);
		vector<int> prev(N);
		dijkstra(g, M-1, dist, prev);
		cout << fixed << setprecision(10) << dist[L-1] << endl;
	}
}
