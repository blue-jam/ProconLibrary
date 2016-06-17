#include "../../math/fft.cpp"

int main(){
	int N;
	cin >> N;
	int n = 1;
	while(n < N + 1) n *= 2;
	vector<int> A(N), B(N);
	vector<P> a(n * 2), b(n * 2);
	for(int i = 0; i < N; ++i){
		cin >> A[i] >> B[i];
		a[i+1] = P(A[i], 0);
		b[i+1] = P(B[i], 0);
	}
	vector<P> aa = dft(a), bb = dft(b);
	vector<P> cc(n * 2);
	for(int i = 0; i < n * 2; ++i)
		cc[i] = aa[i] * bb[i];
	vector<P> c = idft(cc);
	for(int i = 1; i <= 2 * N; ++i){
		cout << (ll)(real(c[i]) + (1e-3)) << endl;
	}
	return 0;
}
