// 内接線．aからbへ向かうとき，aの左からbの右に抜けるのが先．
// aとbが接するときは，2点目に適当な点を取る
vector<Line> innertangent(const Circle &a, const Circle &b){
	double d = abs(b.o - a.o), t = a.r * d / (a.r + b.r);
	P p = a.o + t / d * (b.o - a.o);
	int n = sgn(a.r + b.r, d) + 1;
	if(!n) return vector<Line>();
	if(n == 1) return vector<Line>{Line(p, p - (b.o - a.o) * P(0,1))};
	else{
		auto l1 = a.tangent(p), l2 = b.tangent(p);
		return vector<Line>{Line(l1.second[1], l2.first[1]),
							Line(l1.first[1], l2.second[1])};
	}
}
// 内接線．aからbへ向かうとき，aの左からでるのが先
// aとbが接するときは，2点目に適当な点を取る
vector<Line> outertangent(const Circle &a, const Circle &b){
	if(sgn(a.r, b.r) > 0){
		auto l = outertangent(b, a);
		reverse(ALL(l));
		if(l.size() != 1) EACH(i, l) reverse(ALL(*i));
		return l;
	}
	double d = abs(b.o - a.o), t = -b.r * d / (b.r - a.r);
	P p = b.o + t / d * (b.o - a.o);
	int n = sgn(a.r, d + b.r) + 1;
	if(!n) return vector<Line>();
	if(n == 1)
		return vector<Line>{Line(p, p - (p - a.o) * P(0, 1))};
	else if(!sgn(a.r, b.r)){
		P v = (b.o - a.o) * P(0, 1/abs(b.o-a.o));
		return vector<Line>{Line(a.o + a.r * v, b.o + b.r * v),
							Line(a.o - a.r * v, b.o - b.r * v)};
	}
	else{
		auto l1 = a.tangent(p), l2 = b.tangent(p);
		return vector<Line>{Line(l1.second[1], l2.second[1]),
							Line(l1.first[1], l2.first[1])};
	}
}
