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
// 凸多角形の共通部分．O(nm)．
// TODO:O(n+m)にする
Polygon convex_intersect(const Polygon &a, const Polygon &b){
	Polygon res = a;
	for(int i = 0; i < b.size(); ++i){
		res = convex_cut(res, Line(curr(b,i), next(b,i)));
	}
	return res;
}
