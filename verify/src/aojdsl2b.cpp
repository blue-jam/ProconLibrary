#include "../../datastructure/fenwick.cpp"

int main(){
	int n,q;
	cin >> n >> q;
	Fenwick<int> bit(n);
	for(int i = 0; i < q; ++i){
		int c, x, y;
		cin >> c >> x >> y;
		if(c == 0){
			bit.add(x-1, y);
		}
		else{
			cout << bit.get((y-1)+1) - bit.get(x-1) << endl;
		}
	}
	return 0;
}
