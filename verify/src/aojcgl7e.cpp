#include "../../geometry/geometry.cpp"
#include "../../geometry/crosspoint.cpp"

int main(){
    vector<Circle> v;
    for(int i = 0; i < 2; ++i){
        int x, y, r; cin >> x >> y >> r;
        v.push_back(Circle(x,y,r));
    }
    pair<P, P> ps = crosspointCC(v[0], v[1]);
    if(!lessX(ps.first, ps.second)) swap(ps.first, ps.second);
    cout << fixed << setprecision(10);
    cout << real(ps.first) << " " << imag(ps.first) << " ";
    cout << real(ps.second) << " " << imag(ps.second) << endl;
	return 0;
}
