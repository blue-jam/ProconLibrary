#include "misc/template.cpp"
#include "datastructure/lazysegtree.cpp"

int N, Q;
string s;
int main(){
	cin >> N >> Q >> s;
	vector<int> v(N), q(Q);
	set<int> cl;
	for(int i = 0; i < Q; ++i){
		cin >> q[i];
	}
	for(int i = 0; i < N; ++i){
		v[i] = s[i] == '(' ? 1: -1;
		if(v[i] < 0) cl.insert(i);
		if(i > 0) v[i] += v[i-1];
	}
	LasySegmentTree<int> st(N);
	st.init(v);
	for(int I = 0; I < Q; ++I){
		int l = q[I]-1;
		if(s[l] == '('){
			s[l] = ')';
			cl.insert(l);
			st.add(l, N, -2);
			l = *(cl.begin());
			cl.erase(l);
			s[l] = '(';
			st.add(l, N, +2);
		}
		else{
			s[l] = '(';
			cl.erase(l);
			st.add(l, N, +2);
			l = -1;
			int r = N-1;
			while(r - l > 1){
				int c =  (l + r) / 2;
				if(st.get(c, r) >= 2)
					r = c;
				else
					l = c;
			}
			l = r;
			cl.insert(l);
			s[l] = ')';
			st.add(l, N, -2);
		}
		cout << l+1 << endl;
	}
	return 0;
}
