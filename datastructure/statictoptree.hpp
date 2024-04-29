template <
        typename Path,
        typename Point,
        Path (*vertex)(int i),
        Path (*compress)(Path&, Path&),
        Point (*rake)(Point&, Point&),
        Point (*add_edge)(Path&),
        Path (*add_vertex)(Point&, int)
>
struct static_top_tree {
    enum Type { NONE, VERTEX, COMPRESS, RAKE, ADD_EDGE, ADD_VERTEX };

    struct node {
        Type type;
        // ノードの番号、左の子、右の子、親のノード、木における頂点の番号
        int id, left, right, parent, v_index;
        explicit node(Type type=NONE, int id=-1, int left=-1, int right=-1, int parent=-1, int v_index=-1) :
                type(type), id(id), left(left), right(right), parent(parent), v_index(v_index) {}
    };

    // 木のグラフ表現（連結リスト）。
    // init()で初期化すると、有向になる。また、各頂点について、g[v][0]がheavy-edgeになる
    vector<vector<int>> g;
    vector<node> nodes;
    vector<Point> points;
    vector<Path> paths;
    vector<int> v_to_node;  // 頂点番号からノード番号への変換表

    int root_g = 0, root_nodes = 0; // 木の根の頂点番号、ノードの根の番号

    explicit static_top_tree(int n): g(n), v_to_node(n, -1) {
    }

    /**
     * u-v間に辺を追加する
     */
    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    /**
     * 木の頂点rootを根として初期化する
     * @param root
     */
    void init(int root) {
        root_g = root;

        // HL分解を行う。また、子から親への枝を削除する
        hl_dfs(root_g, -1);

        // 木の生成過程を作る
        Result r = comp(0);
        root_nodes = r.node_index;
        paths.resize(nodes.size());
        points.resize(nodes.size());

        // Path/Pointの初期化
        init_dfs(root_nodes);
    }

    /**
     * 木の頂点vの値が更新された時の更新作業
     * @param v
     */
    void update(int v) {
        int ni = v_to_node[v];
        while (ni != -1) {
            do_update(ni);
            ni = nodes[ni].parent;
        }
    }

private:
    /**
     * vを根とする部分木にHL分解を行う
     * @param v 今いる頂点の番号
     * @param previous 親の頂点の番号
     * @return 部分木のサイズ
     */
    int hl_dfs(int v, int previous) {
        int size = 1, max_c_size = 0;   // 部分木のサイズ、最大の部分木のサイズ
        for (size_t i = 0; i < g[v].size(); i++) {
            int u = g[v][i];
            if (g[v][i] == previous) {
                // 親の頂点への枝を削除
                swap(g[v][i], g[v].back());
                g[v].pop_back();
                i--;
                continue;
            }
            int c_size = hl_dfs(u, v);
            size += c_size;
            if (c_size > max_c_size) {
                // 最大の部分木を最初に持ってくる
                swap(g[v][i], g[v][0]);
                max_c_size = c_size;
            }
        }
        return size;
    }

    /**
     * ノードを追加する便利関数
     * @return 追加されたノードの番号
     */
    int add_node(Type type, int left, int right) {
        int id = nodes.size();
        nodes.emplace_back(type, id, left, right);
        if (left != -1) nodes[left].parent = id;
        if (right != -1) nodes[right].parent = id;
        return id;
    }

    struct Result {
        int node_index, size;
    };

    /**
     * aをtypeの操作で平衡二分木になるように分割する
     */
    Result merge(vector<Result> &a, Type type) {
        if (a.size() == 1) {
            return a[0];
        }
        int size = 0;
        for (const auto &r : a) {
            size += r.size;
        }
        vector<Result> b, c;
        for (size_t i = 0; i < a.size(); i++) {
            if (size > a[i].size) {
                b.push_back(a[i]);
            } else {
                c.push_back(a[i]);
            }
            size -= a[i].size * 2;
        }
        Result r1 = merge(b, type);
        Result r2 = merge(c, type);
        return Result{add_node(type, r1.node_index, r2.node_index), r1.size + r2.size};
    }

    /**
     * Compress操作を行う
     */
    Result comp(int v) {
        vector<Result> children{ do_add_v(v) };
        while (!g[v].empty()) {
            v = g[v][0];
            children.push_back(do_add_v(v));
        }
        return merge(children, COMPRESS);
    }

    /**
     * Rake操作を行う
     */
    Result do_rake(int v) {
        vector<Result> children;
        for (size_t i = 1; i < g[v].size(); i++) {  // compressで処理するため、heavy-edge(indexが0)は除外
            children.push_back(do_add_e(g[v][i]));
        }
        return merge(children, RAKE);
    }

    /**
     * Add Edge操作を行う
     */
    Result do_add_e(int v) {
        Result r = comp(v);
        return {add_node(ADD_EDGE, r.node_index, -1), r.size};
    }

    /**
     * Add Vertex操作を行う
     */
    Result do_add_v(int v) {
        if (g[v].size() <= 1) {
            // 葉またはheavy-edgeしかない場合は、Vertex操作を行う
            return do_vertex(v);
        }
        Result r = do_rake(v);
        int ni = add_node(ADD_VERTEX, r.node_index, -1);
        nodes[ni].v_index = v;  // 木の頂点番号を設定
        v_to_node[v] = ni;
        return {ni, r.size + 1};// 頂点数が増える
    }

    /**
     * Vertex操作を行う
     */
    Result do_vertex(int v) {
        int ni = add_node(VERTEX, -1, -1);
        nodes[ni].v_index = v;  // 木の頂点番号を設定
        v_to_node[v] = ni;
        return {ni, 1};         // 頂点数は1
    }

    /**
     * ノードnvのPath/Pointを更新する便利関数
     */
    void do_update(int nv) {
        if (nodes[nv].type == COMPRESS) {
            paths[nv] = compress(paths[nodes[nv].left], paths[nodes[nv].right]);
        } else if (nodes[nv].type == RAKE) {
            points[nv] = rake(points[nodes[nv].left], points[nodes[nv].right]);
        } else if (nodes[nv].type == ADD_EDGE) {
            points[nv] = add_edge(paths[nodes[nv].left]);
        } else if (nodes[nv].type == ADD_VERTEX) {
            paths[nv] = add_vertex(points[nodes[nv].left], nodes[nv].v_index);
        } else if (nodes[nv].type == VERTEX) {
            paths[nv] = vertex(nodes[nv].v_index);
        }
    }

    /**
     * 再帰的にPath/Pointを初期化する
     */
    void init_dfs(int ni) {
        if (nodes[ni].left != -1)
            init_dfs(nodes[ni].left);
        if (nodes[ni].right != -1)
            init_dfs(nodes[ni].right);
        do_update(ni);
    }
};
