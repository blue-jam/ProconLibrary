#include "../../geometry/geometry.cpp"
#include "../../geometry/convexhull.cpp"

int main(){
	int n;
	cin >> n;
	vector<P> v(n);
	for(int i = 0; i < n; ++i){
		int x,y;
		cin >> x >> y;
		v[i] = P(x,y);
	}
	Polygon p = convex_hull(v,0);
	int m = p.size();
	int idx = 0;
	for(int i = 0; i < m; ++i){
		if(lessY(p[i], p[idx]))
			idx = i;
	}
	cout << m << endl;
	for(int i = 0; i < m; ++i){
		cout << (int)p[(idx+i)%m].real() << " " << (int)p[(idx+i)%m].imag() << endl;
	}
	return 0;
}
