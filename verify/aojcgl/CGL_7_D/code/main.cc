#include "misc/template.cpp"
#include "geometry/geometry.cpp"
#include "geometry/crosspoint.cpp"

int main(){
    int x, y, r, q; cin >> x >> y >> r >> q;
    Circle C(x, y, r);
    for(int i = 0; i < q; ++i){
        int x1, x2, y1, y2, q;
        cin >> x1 >> y1 >> x2 >> y2;
        Line L(P(x1, y1), P(x2, y2));
        vector<P> vp = crosspointLC(L, C);
        if(vp.size() == 1) vp.push_back(vp[0]);
        sort(ALL(vp), lessX);
        for(int j = 0; j < 2; ++j){
            cout << fixed << setprecision(10) << real(vp[j]) << " " << imag(vp[j]);
            if(j == 0) cout << " ";
        }
        cout << endl;
    }
	return 0;
}
