/**
 * Link-Cut Tree.
 *
 * Link-Cut Treeは木を管理する木構造である．管理対象の木をパスに分解し，パスはSplay木で表す．
 * いろいろな操作が \f$O(\log N)\f$ で行える
 *
 * ### ソースコード
 *
 * @include linkcut.cpp
 *
 * ### 確認済み問題
 *
 * - JOI2013年春合宿4日目 SpaceShips(link,cut,findrootのみ)
 *
 * ### 参考
 *
 * - iwiwi先生のスライド
 * - Data Structures and Network Algorithms
 */
struct LinkCutTree{
    static const int L = 0, R = 1;
    struct node{
        node *pp, *cp[2];//*lp, *rp;
        bool rev;
        int dcost, dmin;
        int id;
        node(){
            id = -1;
            pp = cp[L] = cp[R] = NULL;
            rev = false;
            dcost = dmin = 0;
        }
        // Splay木の根であるか
        bool isRoot(){
            return !pp || pp->cp[L] != this && pp->cp[R] != this;
        }
        // ノードの状態（反転など）を子に伝搬させる
        void push(){
            if(rev){
                swap(cp[L], cp[R]);
                if(cp[L]) cp[L]->rev ^= true;
                if(cp[R]) cp[R]->rev ^= true;
                rev = false;
            }
        }
        // dがRなら右回転，dがLなら左回転を行う
        void rot(int d){
            node *q = pp, *r = q->pp;
            int e = 1 - d;
            if(q->cp[e] = cp[d]) cp[d]->pp = q;
            cp[d] = q; q->pp = this;

            int qd = q->dmin;
            q->dmin = q->dcost;
            if(q->cp[e]) q->dmin = min(q->dmin, dmin + q->cp[e]->dmin);
            if(q->cp[d]) q->dmin = min(q->dmin, q->cp[d]->dmin);
            q->dcost -= q->dmin;
            if(q->cp[e]) q->cp[e]->dmin += dmin - q->dmin;
            if(q->cp[d]) q->cp[d]->dmin -= q->dmin;
            if(cp[e]) cp[e]->dmin += dmin;
            dcost += dmin;
            dmin = qd;

            if(pp=r){
                if(r->cp[L] == q) r->cp[L] = this;
                if(r->cp[R] == q) r->cp[R] = this;
            }
        }
        // Splay操作
        void splay(){
            push();
            while(!isRoot()){
                node *q = pp;
                if(q->isRoot()){
                    q->push(); push();
                    if(q->cp[L] == this) rot(R);
                    else rot(L);
                }
                else{
                    node *r = q->pp;
                    r->push(); q->push(); push();
                    for(int i = 0; i < 2; ++i) if(r->cp[i] == q){
                        if(q->cp[i] == this){ q->rot(1-i); rot(1-i); }
                        else{ rot(i); rot(1-i); }
                        break;
                    }
                }
            }
        }
    };
    vector<node> nodes;
    LinkCutTree(int n) : nodes(n) {
        for(int i = 0; i < n; ++i) nodes[i].id = i;
    }
    node *expose(node *x){
        node *rp = NULL;
        for(node *p = x; p != NULL; p = p->pp){
            int ndmin;
            p->splay();

            if(p->cp[R]) p->cp[R]->dmin += p->dmin;
            ndmin = p->dmin + p->dcost;
            if(rp) ndmin = min(ndmin, rp->dmin);
            if(p->cp[L]) ndmin = min(ndmin, p->dmin + p->cp[L]->dmin);
            if(rp) rp->dmin = rp->dmin - ndmin;
            if(p->cp[L]) p->cp[L]->dmin += p->dmin - ndmin;
            p->dcost += p->dmin - ndmin;
            p->dmin = ndmin;

            p->cp[R] = rp;
            rp = p;
        }
        x->splay();
        return x;
    }

    /**
     * 頂点 @a v を根とする木を頂点 @a w に接続する
     */
    void link(int v, int w){
        node *c = &nodes[v], *p = &nodes[w];
        expose(c);
        expose(p);
        c->pp = p;
        p->cp[R] = c;

        p->dcost += p->dmin - min(p->dmin, c->dmin);
        if(p->cp[L]) p->cp[L]->dmin += p->dmin - min(p->dmin, c->dmin);
        p->dmin = min(p->dmin, c->dmin);
        c->dmin = c->dmin - p->dmin;
    }

    /**
     * 木を頂点 @a v から親に向かう辺を削除することで2つの木に分ける
     */
    void cut(int v){
        node *c = &nodes[v];
        expose(c);
        node *p = c -> cp[L];
        c->cp[L] = NULL;
        p->pp = NULL;

        p->dmin += c->dmin;
        c->dmin += c->dcost;
        c->dcost = 0;
    }

    /**
     * 頂点 @a n が属する木の根を見つける
     * @return 木の根の番号
     */
    int findroot(int n){
        node *v = expose(&nodes[n]);
        while(v->cp[L]) v->push(), v = v->cp[L];
        v->splay();
        return v->id;
    }

    /**
     * 頂点 @a n から根に向かうパスの中で最小の重みと，その重みをもつ頂点のうち最も根に近い頂点の組を返す
     * @return (重み最小の頂点，重み最大の頂点）
     */
    pair<int, int> findcost(int n){
        node *v = expose(&nodes[n]);
        for(;;){
            v->push();
            if(v->cp[L] && v->cp[L]->dmin == 0) v = v->cp[L];
            else if((!v->cp[L] || v->cp[L]->dmin > 0) && v->dcost > 0) v = v->cp[R];
            else break;
        }
        v->splay();
        return make_pair(v->dmin, v->id);
    }

    /**
     * 頂点 @a n から根に向かうパスの中にある頂点の重みに値 @a x を加える
     */
    void addcost(int n, int x){
        node *v = expose(&nodes[n]);
        v->dmin += x;
    }

    /**
     * 頂点 @a v を根にする
     */
    void evert(int v){
        node *r = expose(&nodes[v]);
        r->rev ^= true;
    }
};
