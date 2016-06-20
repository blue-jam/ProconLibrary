#include "misc/template.cpp"
#include "datastructure/segmenttree.cpp"

int main(){
	int n, q;
	cin >> n >> q;
	SegmentTree<int> st(n, INT_MAX);

	for(int i = 0; i < q; ++i){
		int c, x, y;
		cin >> c >> x >> y;
		if(c == 0)
			st.update(x, y);
		else
			cout << st.query(x,y+1) << endl;
	}
	return 0;
}
