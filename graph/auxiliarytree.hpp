/**
 * Auxiliary Tree
 *
 * 参考:
 * - https://smijake3.hatenablog.com/entry/2019/09/15/200200
 * - https://atcoder.jp/contests/abc340/editorial/9249
 */
struct auxiliary_tree {
    /**
     * Auxiliary Treeの構造体
     */
    struct AT {
        int n, n_, root;    // n: 頂点数, n_: 元の木の頂点数, root: 根
        vector<int> parent, vertices;   // parent: （現在のインデックスにおける）親, vertices: 頂点集合
        vector<vector<int>> children;   // children: （現在のインデックスにおける）子

        explicit AT(int n, int n_, int root): n(n), n_(n_), root(root) {
        }
    };

    int n, root, maxLog;    // n: 頂点数, root: 根, maxLog: ダブリングの最大の深さ
    vector<vector<int>> g, ancestor;    // g: 隣接リスト, ancestor: LCA用のダブリングした祖先
    vector<int> depth, ord; // depth: 頂点の深さ, ord: DFSでの訪問順

    explicit auxiliary_tree(int n): n(n), g(n) {
        assert(n >= 2);
        root = -1;
        maxLog = -1;
    }

    /**
     * u-v間に辺を追加する
     */
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    /**
     * 木の頂点rを根として初期化する
     */
    void init(int r) {
        root = r;

        for (maxLog = 0; (1 << maxLog) < n; maxLog++);
        ancestor.assign(maxLog, vector<int>(n, -1));
        depth.assign(n, -1);
        ord.assign(n, -1);

        depth[root] = 0;
        initDfs(root, -1, 0);

        for (int k = 0; k + 1 < maxLog; k++) {
            for (int v = 0; v < n; v++) {
                if (ancestor[k][v] < 0) {
                    ancestor[k + 1][v] = -1;
                } else {
                    ancestor[k + 1][v] = ancestor[k][ancestor[k][v]];
                }
            }
        }
    }

    /**
     * 頂点集合vに対するAuxiliary Treeを構築する
     */
    AT buildFor(vector<int> &v) {
        vector<int> u(v);
        sort(u.begin(), u.end(), [&](int a, int b) { return ord[a] < ord[b]; });

        stack<int> S;
        vector<int> at_vertices;
        vector<pair<int, int>> pairs;
        S.push(u[0]);
        at_vertices.push_back(u[0]);
        for (int i = 1; i < u.size(); i++) {
            int w = lca(S.top(), u[i]);
            while (S.size() > 1 && depth[w] <= depth[S.top()]) {
                int a = S.top(); S.pop();
                int p;
                if (depth[S.top()] < depth[w]) {
                    p = w;
                } else {
                    p = S.top();
                }
                pairs.emplace_back(p, a);
            }
            if (S.top() != w) {
                S.push(w);
                at_vertices.push_back(w);
            }
            if (S.top() != u[i]) {
                S.push(u[i]);
                at_vertices.push_back(u[i]);
            }
        }

        while (S.size() > 1) {
            int a = S.top(); S.pop();
            int p = S.top();
            pairs.emplace_back(p, a);
        }

        sort(at_vertices.begin(), at_vertices.end(), [&](int a, int b) { return ord[a] < ord[b]; });
        at_vertices.erase(unique(at_vertices.begin(), at_vertices.end()), at_vertices.end());

        AT at(at_vertices.size(), n, S.top());
        at.vertices = at_vertices;
        at.parent = vector<int>(at.n, -1);
        at.children = vector<vector<int>>(at.n);

        map<int, int> v_to_index;
        for (int i = 0; i < at.n; i++) {
            v_to_index[at.vertices[i]] = i;
        }
        for (auto [p, v] : pairs) {
            at.parent[v_to_index[v]] = v_to_index[p];
            at.children[v_to_index[p]].push_back(v_to_index[v]);
        }

        return at;
    }

    /**
     * u-v間のLCAを求める
     */
    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k < maxLog; k++) {
            if ((depth[v] - depth[u]) >> k & 1) {
                v = ancestor[k][v];
            }
        }
        if (u == v) return u;
        for (int k = maxLog - 1; k >= 0; k--) {
            if (ancestor[k][u] != ancestor[k][v]) {
                u = ancestor[k][u];
                v = ancestor[k][v];
            }
        }
        return ancestor[0][u];
    }

private:
    int initDfs(int v, int p, int num) {
        ord[v] = num++;     // 行きがけ順の番号をつける
        for (int i = 0; i < g[v].size(); i++) {
            int u = g[v][i];
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            ancestor[0][u] = v;
            num = initDfs(u, v, num);
        }
        return num;
    }
};
