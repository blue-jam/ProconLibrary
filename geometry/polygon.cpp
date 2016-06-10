// 依存: geometry
#define curr(p,i) p[i]
#define next(p,i) p[(i+1)%p.size()]
double area(Polygon &p){
    double a = 0;
    for(int i = 0; i < p.size(); ++i)
        a += cross(curr(p,i), next(p,i));
    return a / 2.0;
}
bool convex(Polygon &p){
    for(int i = 0; i < p.size(); ++i){
        if(ccw(curr(p,i), next(p,i), next(p,i+1)) == -1)
            return false;
    }
    return true;
}
enum {OUT, ON, IN};
int contains(const Polygon &p, const P &q){
    bool in = false;
    for(int i = 0; i < p.size(); ++i){
        P a = curr(p, i) - q, b = next(p,i) - q;
        if(imag(a) > imag(b)) swap(a,b);
        if(sgn(imag(a)) <= 0 && sgn(imag(b)) > 0)
            if(sgn(cross(a,b)) < 0) in = !in;
        if(!sgn(abs(cross(a,b))) && sgn(dot(a,b)) <= 0) return ON;
    }
    return in ? IN: OUT;
}
