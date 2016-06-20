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
    int q; cin >> q;
    for(int i = 0; i < q; ++i){
        int x, y; cin >> x >>y;
        int c =contains(p, P(x,y));
        if(c == OUT) cout << 0 << endl;
        else if(c == ON) cout << 1 << endl;
        else cout << 2 << endl;
    }
	return 0;
}
