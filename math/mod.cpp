// O(n)での逆元配列計算
vector<ll> calcinvs(ll n, ll mod){
	vector<ll> inv(n);
	inv[1] = 1;
	for(ll i=2;i<n;++i)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	return inv;
}
