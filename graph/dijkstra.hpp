#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
void dijkstra(const Graph<W>& g, int s, vector<W>& dist, vector<int>& prev) {
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge<W>> Q; // a < b <-> a.weight > b.weight
    Q.push(Edge<W>(-2, s, 0));
    while (!Q.empty()) {
        Edge<W> e = Q.top();
        Q.pop();
        if (prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        for (const auto& edge : g[e.to]) {
            if (dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                Q.push(Edge<W>(edge.from, edge.to, dist[edge.to]));
            }
        }
    }
}

vector<int> buildPath(const vector<int>& prev, int t) {
    vector<int> path;
    for (int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
