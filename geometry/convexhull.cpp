/*
	strict=1だと，辺上の点を出力しない
				strict	not strict
	111...110	T		F
	111...111	T		T
	000...000	T		F
	000...001	F		F
	000...010	F		F
*/
Polygon convex_hull(vector<P> &ps, int strict=1){
    int n = ps.size(), k = 0;
    sort(ALL(ps), lessX);
    Polygon qs(n*2);
    for(int i = 0; i < n; qs[k++] = ps[i++])
        while(k > 1 && (ccw(qs[k-2], qs[k-1], ps[i]) & 7) > 6-strict) --k;
    for(int i = n-2, t=k; i >= 0; qs[k++] = ps[i--])
        while(k>t && (ccw(qs[k-2],qs[k-1], ps[i]) & 7) > 6-strict) --k;
    qs.resize(k-1);
    return qs;
}
