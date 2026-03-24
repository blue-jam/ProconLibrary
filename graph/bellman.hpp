#pragma once
#include "graph/graph.hpp"
#include "misc/template.hpp"

template<typename W>
bool bellmanFord(const Graph<W>& g, int s, vector<W>& dist, vector<int>& prev) {
    int n = g.size();
    bool negativeLoop = false;
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    for (int k = 0; k < 2 * n; ++k) {
        for (int v = 0; v < n; ++v) {
            for (const auto& edge : g[v]) {
                if (dist[edge.from] != INF && dist[edge.to] > dist[edge.from] + edge.weight) {
                    if (dist[edge.from] == -INF) {
                        dist[edge.to] = -INF;
                    } else {
                        dist[edge.to] = dist[edge.from] + edge.weight;
                    }
                    prev[edge.to] = edge.from;
                    if (k == n - 1) {
                        dist[edge.to] = -INF;
                        negativeLoop = true;
                    }
                }
            }
        }
    }
    return negativeLoop;
}
template<typename W>
bool findNegativeLoop(const Graph<W>& g) {
    int n = g.size();
    vector<W> dist(n, 0);
    for (int k = 0; k < n; ++k) {
        for (int v = 0; v < n; ++v) {
            for (const auto& edge : g[v]) {
                if (dist[edge.to] > dist[edge.from] + edge.weight) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                    if (k == n - 1) return true;
                }
            }
        }
    }
    return false;
}
vector<int> buildPath(const vector<int>& prev, int t) {
    vector<int> path;
    for (int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

template<typename T, T (*add)(T, T), bool (*lt)(T, T), T (*zero)(), T (*inf)()>
struct bellman_ford {
    graph<T> g;
    vector<T> dist;
    vector<ll> prev;
    bool has_negative_loop;

    explicit bellman_ford(graph<T> g) : g(g), dist(g.n, inf()), prev(g.n, -1), has_negative_loop(false) {}

    bool run(int s) {
        const T INF = inf();
        const auto eq = [](T a, T b) { return !lt(a, b) && !lt(b, a); };

        int n = g.n;
        dist[s] = zero();

        for (int k = 0; k < 2 * n; ++k) {
            for (int v = 0; v < n; ++v) {
                for (auto& e : g.edges[v]) {
                    auto new_distance = add(dist[e.from], e.weight);
                    if (!eq(dist[e.from], INF) && lt(new_distance, dist[e.to])) {
                        dist[e.to] = new_distance;
                        prev[e.to] = e.from;
                        if (k >= n - 1) {
                            dist[e.to] = -INF;
                            has_negative_loop = true;
                        }
                    }
                }
            }
        }
        return has_negative_loop;
    }
};
