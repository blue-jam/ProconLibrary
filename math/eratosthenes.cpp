/**
 * @file
 *
 * ### ソースコード
 *
 * @include eratosthenes.cpp
 */
/**
 * [0, n)の範囲の素数をエラトステネスの篩で列挙する．
 * 計算量は \f$O(n log log n)\f$.
 *
 * @param n 区間を表す正整数．半開区間であることに注意
 * @param prime 素数を格納するvector．空であることが望ましい．
 * @return 篩で使用したベクタ @a isPrime. isPrime[i] != 0であればiは素数
 *
 *
 * ### 確認済み問題
 *
 * - AOJ 1232
 *
 * ### 参考
 *
 * - プログラミングコンテストチャレンジブック(p122,123)
 */
vector<int> sieve_of_eratosthenes(ll n, vector<ll> &prime){
	vector<int> isPrime(n);
	for(ll i = 2; i < n; ++i)
		isPrime[i] = i;
	for(ll i = 2; i < n; ++i)
		if(isPrime[i]){
			prime.push_back(i);
			for(ll j = i * i; j < n; j += i)
				isPrime[j] = 0; 
		}
	return isPrime;
}
