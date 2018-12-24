/**
 * @file
 *
 * ## 凸多角形の切断
 *
 * 与えられた多角形の直線に対して左側を切除し，右側部分を残す．
 *
 * 多角形は反時計回りに点が格納されているものとする．
 *
 * ### 計算量
 *
 * N角形に対してO(N)
 *
 * ### ソースコード
 *
 * @include convexcut.cpp
 *
 * ### 確認済み問題
 *
 *   * AOJ 1283
 *
 * ### 使用方法
 *
 * 右側を切除したい場合は，if(ccwl[0], l[1], curr) != 1))の1を-1に置き換える．
 *
 * ### 参考
 *
 *   * [Spaghetti Source](http://www.prefield.com/)
 */
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
