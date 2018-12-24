/**
 * @file
 * ## 平面幾何の要素
 *
 * ### 浮動小数の誤差について
 *
 * 平面幾何の問題を計算するときは浮動小数の演算が必要となることが多く，答えの出力の際に誤差が許容されていたり，計算の際にどれぐらいの誤差を0とみてよいかなどが与えられることが多い．0の判定などにはepsを使用すること．
 *
 * #### 点の表現
 *
 * 数多くのC++の競技プログラミング用ライブラリでは，complex型を使用することが多い．
 *
 * その理由としては，
 *
 *   * 宣言が楽（typedef complex<double> P;で終わる）
 *   * 絶対値の定義や数値の掛け算などの定義がなされていること
 *
 * が主な理由として挙げられる．
 *
 * x座標は実数値，y座標は虚数値として扱うので，x座標を取得するときはp.real()，real(p)，y座標を取得するときはp.imag()，imag(p)とする．
 *
 * operator< では，x座標が小さい方を小さいものとして，x座標が等しいときはy座標が小さい方を小さいものとしている．
 *
 * #### 直線，線分
 *
 * 直線は通る2点，線分は2つの端点を用いて表現する．vector<P> を継承するので，以下の2点が利点として得られる．
 *
 *   * 辞書順の比較ができる
 *   * 点に添え字を用いてアクセスできる
 *
 * 半直線は出てくることが少ないので，詳細は説明しないが，ライブラリで行っていることを理解すれば，必要なときに実装できるはず．
 *
 * #### 辺の交差のない多角形
 *
 * vector<P>で表す．点を格納する向きは反時計回りとする．
 *
 * #### 円
 *
 * 円は中心と半径を用いて表す．
 *
 * ### 使用方法
 *
 * 特に記述しない．Lineのコンストラクタは一個減らしてもいい気がするが．
 *
 * conjはcomplexの共役なものを返す関数である．
 *
 * conj(a) * b = (real(a) - i imag(a)) * (real(b) - i imag(b)) = (real(a) *
 * real(b) + imag(a) * imag(b)) + i (real(a) * imag(b) - imag(a) * real(b)) となる．
 *
 * ### ソースコード
 *
 * @include geometry.cpp
 *
 * ### 参考
 *
 *   * [deq notes](http://www.deqnotes.net/)(平面幾何の解説が詳しい)
 *   * [Spaghetti Source](http://www.prefield.com/)
 */
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
#define curr(p,i) p[i]
#define next(p,i) p[(i+1)%p.size()]
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
