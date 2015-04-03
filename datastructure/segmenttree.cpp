// RMQを解くSegmentTree
// SegmentTree(n_, z)	: zは無視するデータ
// init(v)				: vで初期化
// update(k,d)			: k番目をdに更新
// query(a,b)			: [a,b)内での最小値
template<typename T> 
struct SegmentTree{
	int n;
	vector<T> dat;
	T ign;
	SegmentTree(int n_, T z){
		for(n = 1; n < n_; n *= 2);
		ign = z;
		dat = vector<T>(n * 2 - 1, z);
	}
	void init(vector<T> &v){
		for(int i = 0; i < v.size(); ++i){
			dat[i + n - 1] = v[i];
		}
		for(int k = n - 2; k >= 0; --k){
			dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}
	void update(int k, T d){
		k += n - 1;
		dat[k] = d;
		while(k > 0){
			k = (k - 1) / 2;
			dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}
	T get(int a, int b, int k, int l, int r){
		if(b <= l || r <= a)
			return ign;
		if(a <= l && r <= b){
			return dat[k];
		}
		else{
			T vl = get(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = get(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(vl, vr);
		}
	}
	T query(int a, int b){
		return get(a, b, 0, 0, n);
	}
};
