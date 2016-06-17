// DISCO プレゼンツディスカバリーチャンネル プログラミングコンテスト予選 C問題
// http://discovery2016-qual.contest.atcoder.jp/tasks/discovery_2016_qual_c
#include "../../string/suffixarray.cpp"

int main(){
	string S;
	int K;
	cin >> S >> K;
	int acnt = 0;
	for(int i = 0; i < S.size(); ++i) if(S[i] == 'a') ++acnt;
	if(S.size() - acnt <= K){
		cout << string(acnt - (K - (S.size() - acnt)), 'a') << endl;
		return 0;
	}
 
	int cnt = 0, life = K;
	for(int i = 0; life >= 0 ; ++i){
		if(S[i] != 'a'){
			if(life == 0)
				break;
			else
				--life;
		}
		++cnt;
	}
 
	SuffixArray sa;
	sa.init(S);
	int idx = cnt;
	// string res = string(cnt, 'a') + S.substr(cnt);
	for(int i = cnt; i >= 0; --i){
		if(S[i] == 'a') break;
		if(sa.rank[idx] > sa.rank[i]){
			idx = i;
		}
	}
	cout << string(cnt, 'a') + S.substr(idx) << endl;
	return 0;
}
