#include "misc/template.cpp"
#include "geometry/geometry.cpp"
#include "geometry/polygon.cpp"

int main(){
    int n; cin >> n;
    Polygon p(n);
    for(int i = 0; i < n; ++i){
        int x, y; cin >> x >> y;
        p[i] = P(x,y);
    }
    cout << fixed << setprecision(1);
    cout << area(p) << endl;
	return 0;
}
