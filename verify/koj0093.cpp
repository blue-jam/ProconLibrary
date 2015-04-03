#include <bits/stdc++.h>
using namespace std; 

#define ALL(x) (x).begin(),(x).end() 

typedef long long ll;
const double eps = 1e-10;
	vector<int> v;

// RMQを解くSegmentTree
// SegmentTree(n_, z)	: zは無視するデータ
// init(v)				: vで初期化
// update(k,d)			: k番目をdに更新
// query(a,b)			: [a,b)内での最小値
template<typename T> 
struct LasySegmentTree{
	struct node_t{
		T min, sum, add;
		int pos;
	};
	int n;
	vector<node_t> dat;
	inline void eval(int k, int l, int r){
		if(dat[k].add == 0) return;
		if(r - l > 1){
			dat[k*2+1].add += dat[k].add;
			dat[k*2+2].add += dat[k].add;
		}
		dat[k].min += dat[k].add;
		dat[k].sum += dat[k].add * (r - l);
		dat[k].add = 0;
	}
	inline void merge(int k){
		int lch = k*2+1, rch = k*2+2;
		T lm = dat[lch].min, rm = dat[rch].min;
		dat[k].min = min(lm, rm);
		dat[k].pos = lm <= rm ? dat[lch].pos: dat[rch].pos;
		dat[k].sum = dat[lch].sum + dat[rch].sum;
	}
	void init(vector<T> &v){
		for(int i = 0; i < v.size(); ++i){
			dat[i+n-1].min = dat[i+n-1].sum = v[i];
			dat[i+n-1].pos = i;
		}
		for(int k = n - 2; k >= 0; --k)
			merge(k);
	}
	LasySegmentTree(int n_){
		for(n = 1; n < n_; n *= 2);
		dat = vector<node_t>(n * 2 - 1);
	}
	T get(int a, int b, int &pos, int k, int l, int r){
		eval(k, l, r);
		if(b <= l || r <= a)
			return numeric_limits<T>::max();
		else if(a <= l && r <= b){
			pos = dat[k].pos;
			return dat[k].min;
		} else{
			int m = (l+r)/2, lp = -1, rp = -1;
			T lm = get(a, b, lp, k*2+1, l, m);
			T rm = get(a, b, rp, k*2+2, m, r);
			merge(k);
			pos = lm <= rm ? lp: rp;
			return min(lm, rm);
		}
	}
	T get(int a, int b, int &p){
		p = -1;
		return get(a, b, p, 0, 0, n);
	}
	T get(int a, int b){ int p; return get(a, b, p); }
	T sum(int a, int b, int k, int l, int r){
		eval(k, l, r);
		if(b <= l || r <= a)
			return 0;
		else if(a <= l && r <= b)
			return dat[k].sum;
		else{
			T lv = sum(a, b, k * 2 + 1, l, (l + r) / 2);
			T rv = sum(a, b, k * 2 + 2, (l + r) / 2, r);
			merge(k);
			return lv + rv;
		}
	}
	T sum(int a, int b){ return sum(a, b, 0, 0, n); }
	void add(int a, int b, T d, int k, int l, int r){
		eval(k, l, r);
		if(b <= l || r <= a)
			return;
		if(a <= l && r <= b){
			dat[k].add += d;
			eval(k, l, r);
			return;
		}
		int m = (l + r) / 2;
		add(a, b, d, k*2+1, l, m);
		add(a, b, d, k*2+2, m, r);
		merge(k);
	}
	T add(int a, int b, T d){ add(a, b, d, 0, 0, n); }
};

int N, Q;
int main(){
	ios::sync_with_stdio(false);
	cin >> N >> Q;
	v.resize(N);
	for(int i = 0; i < N; ++i){
		cin >> v[i];
	}
	LasySegmentTree<int> st(N);
	st.init(v);
	for(int i = 0; i < Q; ++i){
		int q, l, r, x;
		cin >> q >> l >> r;
		--l;
		if(q == 1){
			cout << st.get(l, r) << endl;
		}
		else{
			cin >> x;
			st.add(l, r, x);
		}
	}
	return 0;
}
