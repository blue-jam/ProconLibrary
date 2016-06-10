// 依存：geometry
bool intersectSS(const Segment &s, const Segment &t){
    return  ccw(s[0],s[1],t[0]) * ccw(s[0],s[1],t[1]) <= 0 &&
            ccw(t[0],t[1],s[0]) * ccw(t[0],t[1],s[1]) <= 0;
}
// TODO:ここにあったTODOが文字化けで読めない
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
double distanceLP(const Line &s, const P &p){
    return abs(cross(p-s[0],s[1]-s[0])) / abs(s[1]-s[0]);
}
double distanceSP(const Segment &s, const P &p){
    if(min(dot(s[1]-s[0], p-s[0]), dot(s[0]-s[1], p-s[1])) < 0)
        return min(abs(p-s[0]), abs(p-s[1]));
    else
        return distanceLP(s, p);
 
}
double distanceSS(const Segment &s, const Segment &t){
    if(intersectSS(s, t)) return 0;
    return min( min(distanceSP(s, t[0]), distanceSP(s, t[1])),
                min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}

pair<P,P> crosspointCC(const Circle &a, const Circle &b){
    double d = abs(b.o - a.o);
    double x = (a.r * a.r - b.r * b.r + d * d) / (d * 2);
    P v = (b.o - a.o) * (1.0 / d);
    P n = P(0,1) * v;
    double h = sqrt(a.r * a.r - x * x);
    return make_pair(a.o + v * x + n * h,
                     a.o + v * x - n * h);
}
// TODO:ここにあったコメントが文字化けで読めない
int intersectLC(const Line &l, const Circle &c){
    double d = distanceLP(l, c.o);
    return sgn(d, c.r) + 1;
}
vector<P> crosspointLC(const Line &l, const Circle &c){
    int n = intersectLC(l, c);
    vector<P> res;
    if(!n) return res;
    P p = projection(l, c.o), e = 1.0/abs(l[1]-l[0])*(l[1]-l[0]);
    if(n == 1){
        res.push_back(p); return res;
    }
    double d = sqrt(c.r*c.r-norm(p-c.o));
    res.push_back(p + e * d);
    res.push_back(p - e * d);
    return res;
}
