#include "misc/template.cpp"
#include "geometry/geometry.cpp"

int main(){
    int x1, x2, y1, y2, q;
    cin >> x1 >> y1 >> x2 >> y2 >> q;
    Line L(P(x1, y1), P(x2, y2));
    for(int i = 0; i < q; ++ i){
        int x, y;
        cin >> x >> y;
        int c = ccw(L[0], L[1], P(x,y));
        if(c == 0) cout << "ON_SEGMENT" << endl;
        else if(c == 2) cout << "ONLINE_BACK" << endl;
        else if(c == -2) cout << "ONLINE_FRONT" << endl;
        else if(c == 1) cout << "COUNTER_CLOCKWISE" << endl;
        else cout << "CLOCKWISE" << endl;
    }
	return 0;
}
