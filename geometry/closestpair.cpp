// 依存: geometry
double closestPairRecur(vector<P> &v, int l, int r, P &a, P &b){
    if(r - l < 2) return numeric_limits<double>::max();
    int m = (l + r) / 2;
    P a2, b2;
    double x = real(v[m]);
    double d  = abs(v[l+1]-v[l]); a = v[l]; b = v[l+1];
    double d1 = closestPairRecur(v, l, m, a, b);        // 再帰実行
    double d2 = closestPairRecur(v, m, r, a2, b2);
    d = min(d, d1);
    if(sgn(d, d2) < 0){
        d = d2; a = a2; b = b2;
    }
    auto vb = v.begin();
    inplace_merge(vb+l, vb+m, vb+r, lessY);
	// [x-d,x+d]の範囲の点をwに保持
    vector<P> w;
    for(int i = l; i < r; ++i){
        if(sgn(x-d, real(v[i])) < 0 || sgn(real(v[i]), x+d) < 0)
            continue;
        for(int j = w.size()-1; j >= 0 && sgn(imag(w[j])+d, imag(v[i])) < 0; --j)
            if(sgn(abs(w[j] - v[i]), d) > 0){
                d = abs(w[j]-v[i]); a = v[i]; b = w[j];
            }
        w.push_back(v[i]);
    }
    assert(sgn(abs(b-a), d) == 0);
    return d;
}
double closestPair(vector<P> v, P &a, P &b){
    sort(ALL(v), lessX);
    return closestPairRecur(v, 0, v.size(), a, b);
}
double closestPair(vector<P> v){
    P a, b;
    return closestPair(v, a, b);
}
