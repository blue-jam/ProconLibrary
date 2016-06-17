typedef complex<double> P;
const double PI = atan(1) * 4;

vector<P> fft(const vector<P> &a, int r){
	int n = a.size();
	if(n == 1) return vector<P>(1, a[0]);
	P w = polar(1.0, r * 2.0 * PI / n);
	P z = P(1, 0);
	vector<P> a0(n/2), a1(n/2);
	for(int i = 0; i < n/2; ++i){
		a0[i] = a[i*2];
		a1[i] = a[i*2+1];
	}
	vector<P> y0 = fft(a0, r), y1 = fft(a1, r), y(n);
	for(int i=0; i < n/2; ++i){
		y[i] = y0[i] + z * y1[i];
		y[i+(n/2)] = y0[i] - z * y1[i];
		z *= w;
	}
	return y;
}
// 離散フーリエ変換
vector<P> dft(const vector<P> &a){
	return fft(a, 1);
}
// 離散フーリエ逆変換
vector<P> idft(const vector<P> &a){
	vector<P> y = fft(a, -1);
	int n = a.size();
	for(int i = 0; i < n; ++i) y[i] /= n;
	return y;
}
