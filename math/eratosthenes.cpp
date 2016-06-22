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
