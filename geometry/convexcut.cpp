// 左側切除
Polygon convex_cut(const Polygon &p, const Line &l){
    Polygon res;
    for(int i = 0; i < p.size(); ++i){
		P a = curr(p,i), b = next(p,i);
        Line tl = Line(a, b);
        if(ccw(l[0], l[1], a) != -1) res.push_back(a);
        if(ccw(l[0], l[1], a) * ccw(l[0], l[1], b) < 0)
            res.push_back(crosspointLL(tl, l));
    }
    return res;
}
