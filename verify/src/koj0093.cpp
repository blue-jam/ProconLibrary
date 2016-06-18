#include "../../datastructure/lazysegtree.cpp"

int N, Q;
vector<int> v;
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
