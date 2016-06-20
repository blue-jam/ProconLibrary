#include "misc/template.cpp"
#include "geometry/geometry.cpp"

int main(){
    int q; cin >> q;
    for(int i = 0; i < q; ++i){
        vector<Line> L;
        for(int j = 0; j < 2; ++j){
            int a, b, c, d; cin >> a >> b >> c >> d;
            L.push_back(Line(P(a,b), P(c,d)));
        }
        int r = 0;
        if(parallel(L[0], L[1])) r = 2;
        else if(orthogonal(L[0], L[1])) r = 1;
        cout << r << endl;
    }
	return 0;
}
