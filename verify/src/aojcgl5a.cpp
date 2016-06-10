#include "../../geometry/geometry.cpp"
#include "../../geometry/closestpair.cpp"

int main(){
    int n; cin >> n;
    vector<P> v(n);
    for(int i = 0; i < n;++i){
        double x, y;
        cin >> x >> y;
        v[i] = P(x,y);
    }
    cout << fixed << setprecision(10) << closestPair(v) << endl;
	return 0;
}
