// 依存：geometry
bool intersectSS(const Segment &s, const Segment &t){
    return  ccw(s[0],s[1],t[0]) * ccw(s[0],s[1],t[1]) <= 0 &&
            ccw(t[0],t[1],s[0]) * ccw(t[0],t[1],s[1]) <= 0;
}
// TODO:端点の扱いが雑なのを何とかする
P crosspointSS(const Segment &s, const Segment &t){
    double a = cross(s[1] - s[0], t[1] - t[0]);
    double b = cross(s[1] - s[0], s[1] - t[0]);
    if(!sgn(abs(a)) && !sgn(abs(b))) return s[0];   // same line
    // if(abs(a) < eps) assert(false);
    return t[0] + b/a * (t[1] - t[0]);
}
P crosspointLL(const Line &s, const Line &t){
    double a = cross(s[1] - s[0], t[1] - t[0]);
    double b = cross(s[1] - s[0], s[1] - t[0]);
    if(!sgn(abs(a)) && !sgn(abs(b))) return s[0];   // same line
    // if(abs(a) < eps) assert(false);
    return t[0] + b/a * (t[1] - t[0]);
}
// 直線と点の距離
double distanceLP(const Line &s, const P &p){
    return abs(cross(p-s[0],s[1]-s[0])) / abs(s[1]-s[0]);
}
// 線分と点の距離
double distanceSP(const Segment &s, const P &p){
    if(min(dot(s[1]-s[0], p-s[0]), dot(s[0]-s[1], p-s[1])) < 0)
        return min(abs(p-s[0]), abs(p-s[1]));
    else
        return distanceLP(s, p);
 
}
// 線分と線分の距離
double distanceSS(const Segment &s, const Segment &t){
    if(intersectSS(s, t)) return 0;
    return min( min(distanceSP(s, t[0]), distanceSP(s, t[1])),
                min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
// 円と円の交点（aからbへ向かう左側がfirst）
pair<P,P> crosspointCC(const Circle &a, const Circle &b){
    double d = abs(b.o - a.o);
    double x = (a.r * a.r - b.r * b.r + d * d) / (d * 2);
    P v = (b.o - a.o) * (1.0 / d);
    P n = P(0,1) * v;
    double h = sqrt(a.r * a.r - x * x);
    return make_pair(a.o + v * x + n * h,
                     a.o + v * x - n * h);
}
// 直線と円の交点の個数
// 交点の個数を返す
int intersectLC(const Line &l, const Circle &c){
    double d = distanceLP(l, c.o);
    return sgn(d, c.r) + 1;
}
// 直線と円の交点
// 直線が中心を通らない場合は，中心から直線へ向かう左側から．
// 通る場合は，中心から(l[1]-l[0])に向かう向きが先．
vector<P> crosspointLC(const Line &l, const Circle &c){
    int n = intersectLC(l, c);
    vector<P> res;
    if(!n) return res;
    P p = projection(l, c.o), e = 1.0/abs(l[1]-l[0])*(l[1]-l[0]);
    if(n == 1){
        res.push_back(p); return res;
    }
	if(sgn(abs(p - c.o)))
		e = (p - c.o) * P(0, 1/abs(p - c.o));
    double d = sqrt(c.r*c.r-norm(p-c.o));
    res.push_back(p + e * d);
    res.push_back(p - e * d);
    return res;
}
