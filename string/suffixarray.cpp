struct SuffixArray{
	int n;
	string S;
	vector<int> sa,rank,lcp;

	void init(const string &s){
		S = s;
		n = S.size();

		sa.resize(n+1);
		rank.resize(n+1);
		lcp.resize(n+1);

		vector<tuple<int,int,int>> tmp(n+1);
		vector<int> trank(n+1);

		// SuffixArrayとrank配列の構築
		for(int i = 0; i <= n; ++i)
			rank[i] = i < n ? S[i]: -1;
		for(int k = 1; k <= n; k *= 2){
			for(int i = 0; i <= n; ++i)
				tmp[i] = make_tuple(rank[i], i+k<n ? rank[i+k]: -1, i);
			sort(ALL(tmp));

			trank[get<2>(tmp[0])] = 0;
			for(int i = 1; i <= n; ++i){
				trank[get<2>(tmp[i])] = trank[get<2>(tmp[i-1])];
				if(get<0>(tmp[i]) != get<0>(tmp[i-1]) || get<1>(tmp[i]) != get<1>(tmp[i-1]))
						trank[get<2>(tmp[i])]++;
			}
			copy(ALL(trank), rank.begin());
		}
		for(int i = 0; i <= n; ++i)
			sa[rank[i]] = i;

		// lcp配列の計算(未検査)
		int h = 0;
		lcp[0] = 0;
		for (int i = 0; i < n; ++i){
			int j = sa[rank[i] - 1];

			if (h > 0) h--;
			for(; j+h<n && i+h < n && S[j+h]==S[i+h]; ++h) ;
			lcp[rank[i]-1] = h;
		}
	}
};
