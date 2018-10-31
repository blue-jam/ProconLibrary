#include "misc/template.cpp"
#include "datastructure/fenwick.cpp"

int main(){
	int n,q;
	cin >> n >> q;
	Fenwick<int> bit(n + 1);
	for(int i = 0; i < q; ++i){
		int c, x, y;
		cin >> c >> x >> y;
		if(c == 0){
			bit.add(x, y);
		}
		else{
			cout << bit.get(y) - bit.get(x - 1) << endl;
		}
	}
	return 0;
}
