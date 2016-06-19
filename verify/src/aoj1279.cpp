const double INF = 1e+10;
typedef double Weight;
struct Edge{
    int from, to;
    Weight weight;
    int rev;     // 無向グラフの対の辺
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
vector<int> buildPath(const vector<int> &prev, int t){
    vector<int> path;
    for(int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
#include "../../geometry/geometry.cpp"
#include "../../geometry/crosspoint.cpp"
#include "../../geometry/polygon.cpp"
#include "../../geometry/arrangement.cpp"

int main(){
    for(;;){
        int n;
        cin >> n;
        if(n == 0) return 0;
        P s, g;
        vector<Segment> v;
        int x, y;
        cin >> x >> y; s=P(x,y);
        cin >> x >> y; g=P(x,y);
        for(int i = 0; i < n; ++i){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            v.push_back(Segment(P(x1,y1), P(x2,y2)));
        }
        vector<Segment> road, signs;
        for(int i = 0; i < n; ++i){
            int f = 0;
            for(int j=0;j<n;++j) if(i != j) for(int k=0;k<2;++k){
                if(ccw(v[j][0], v[j][1], v[i][k]) == 0)
                    f |= 1 << k;
            }
            if(f == 3) road.push_back(v[i]);
            else signs.push_back(v[i]);
        }
        vector<P> ps;
        Graph graph = segmentArrangement(road, ps);
        int si, gi;
        for(int i=0;i<ps.size();++i) if(abs(ps[i]-s) < eps) si = i;
        for(int i=0;i<ps.size();++i) if(abs(ps[i]-g) < eps) gi = i;
 
        EACH(i, signs){
            Segment ss = *i;
            EACH(j, graph) EACH(k, *j) {
                int a = k->from, b = k->to;
                bool f = true;
                double d = 1;
                if(ccw(ps[a], ps[b], ss[0]) == 0){
                    d = dot(ss[0]-ss[1], ps[b]-ps[a]);
                }
                else if(ccw(ps[a], ps[b], ss[1]) == 0){
                    d = dot(ss[1]-ss[0], ps[b]-ps[a]);
                }
                if(d < eps){
                    k->weight = INF;
                }
            }
        }
 
        vector<int> prev(ps.size(),-1);
        vector<Weight> dist(ps.size());
        dijkstra(graph, si, dist, prev);
        if(dist[gi] == INF){
            cout << -1 << endl;
        }
        else{
            vector<int> path = buildPath(prev, gi);
            EACH(i, path){
                cout << (int)ps[*i].real() << " " << (int)ps[*i].imag() << endl;
            }
            cout << 0 << endl;
        }
    }
}
