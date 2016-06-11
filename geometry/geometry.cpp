const double PI = atan(1) * 4;
// 大小比較用
int sgn(double a){
    return a < -eps ? -1: a > eps ? 1: 0;
}
int sgn(double a, double b){
    return sgn(b - a);
}
typedef complex<double> P;
typedef vector<P> Polygon;
struct Line : public vector<P> {
    Line(P a, P b) {
        push_back(a); push_back(b);
    }
};
struct Segment : public Line {
    Segment(const P &a, const P &b) : Line(a,b) { }
};
struct Circle{
    P o;
    double r;
    Circle() { }
    Circle(const P &o, double r) : o(o), r(r) { }
    Circle(double x, double y, double r) : o(x,y), r(r) { }
	// 点の包含（境界を含む）
    bool contains(const P &p) const{
        return sgn(abs(p-o), r) <= 0;
    }
	// 内部（境界を含まず）
    bool inside(const P &p) const{
        return sgn(abs(p-o), r) < 0;
    }
	// 点pを通る接線．pからoへ向かうベクトルの左側がfirstに入る
    pair<Line,Line> tangent(const P &p) const{
        vector<Line> res;
        double d = abs(p - o), s = r*r / d, t = sqrt(r*r-s*s);
        P q = o + s/d * (p - o), e = (p - o) * P(0, 1/d); 
        return make_pair(Line(p,q+e*t), Line(p,q-e*t));
    }
};
 
bool near(const P &a, const P &b){
    return !sgn(abs(a-b));
}
// sort用．ClosestPair用にX,Yに分けている
bool lessX(const P &a, const P &b){
    if(sgn(real(a), real(b))) return real(a) < real(b);
    if(sgn(imag(a), imag(b))) return imag(a) < imag(b);
    return false;
}
bool lessY(const P &a, const P &b){
    if(sgn(imag(a), imag(b))) return imag(a) < imag(b);
    if(sgn(real(a), real(b))) return real(a) < real(b);
    return false;
}
double dot(const P &a, const P &b){
    return real(conj(a) * b);
}
double cross(const P &a, const P &b){
    return imag(conj(a) * b);
}
int ccw(const P &a, P b, P c){
    assert(!near(a, b));
    b -= a; c -= a;
    if (sgn(cross(b, c)) > 0)        return +1;  // ccw
    if (sgn(cross(b, c)) < 0)        return -1;  // cw
    if (sgn(dot(b, c)) < 0)          return +2;  // c-a-b
    if (sgn(norm(b), norm(c)) > 0)   return -2;  // a-b-c
    return 0;                                   // a-c-b
}
bool parallel(const Line &s, const Line &t){
    return !sgn(abs(cross(s[1]-s[0], t[1]-t[0])));
}
bool orthogonal(const Line &s, const Line &t){
    return !sgn(abs(dot(s[1]-s[0], t[1]-t[0])));
}
// 点aの直線s上への射影
P projection(const Line &s, const P &a){
    P v = s[1] - s[0];
    return s[0] + dot(v, a - s[0]) / abs(v) / abs(v) * v;
}
// 直線sに対する点aの鏡映
P reflection(const Line &s, const P &a){
    P p = projection(s, a);
    return 2.0 * p - a;
}

