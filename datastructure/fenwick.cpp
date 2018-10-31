// Fenwick(n)	: 要素数nで初期化
// update(i,v)	: i番目の要素にvだけ加える
// get(i)		: 区間[0,i)の総和
// modを0より大きくすると，modをとるようになる

template<typename T> 
struct Fenwick{
	vector<T> bit;
	T mod;
	Fenwick(int n){
		bit = vector<T>(n + 1);
		mod = 0;
	}
	void add(int i, T v){
		int n = bit.size();
		++i;
		while(i < n){
			bit[i] += v;
			if(mod > eps) bit[i] %= mod;
			i += i & -i;
		}
	}
	T get(int i){
		T res = 0;
		++i;
		while(i > 0){
			res += bit[i];
			if(mod > eps) bit[i] %= mod;
			i -= i & -i;
		}
		return res;
	}
};
