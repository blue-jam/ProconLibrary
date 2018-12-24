/**
 * @file
 * ### グラフの要素
 * グラフは各頂点から出て行く辺をリストとして保持する隣接リスト表現と各頂点間に辺が存在する情報を記録する隣接行列表現がある．
 * それぞれ利点があるので状況に応じて使い分けること．
 *
 * <dl>
 *   <dt>隣接リスト</dt><dd>頂点を基準に考えればいいときに有向．重複辺も扱える．</dd>
 *   <dt>隣接行列</dt><dd>@f$O(E)@f$ が @f$O(V^2)@f$ になる．密グラフや，頂点数が少ないグラフについて効率よく扱える．重複辺を扱いにくい．</dd>
 * </dl>
 *
 * ### ソースコード
 *
 * @include graph.cpp
 *
 * Edgeのless演算子のオーバーロードで，大きいほうが左辺のときにtrueを返すようにしている．
 * これはpriority_queueで，weightの小さいほうを先に取り出すときの工夫である．
 * 気に入らない場合は，greater演算子をオーバーロードし，priority_queueを以下のように宣言する．
 *
 * @code
 * priority_queue<Edge>, vector<Edge>, greater<Edge>> Q;
 * @endcode
 */
typedef int Weight;
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
