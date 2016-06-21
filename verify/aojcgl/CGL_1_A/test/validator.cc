#include "testlib.h"

const int INF = 10000;

int main(){
	registerValidation();

	int xp1, yp1, xp2, yp2;
	xp1 = inf.readInt(-INF,+INF, "xp1");
	inf.readSpace();
	yp1 = inf.readInt(-INF,+INF, "yp1");
	inf.readSpace();
	xp2 = inf.readInt(-INF,+INF, "xp2");
	inf.readSpace();
	yp2 = inf.readInt(-INF,+INF, "yp2");
	inf.readEoln();
	ensuref(xp1 != xp2 || yp1 != yp2, "P1 != P2");
	int q = inf.readInt(1, 1000, "q");
	inf.readEoln();
	for(int i = 0; i < q; ++i){
		int x = inf.readInt(-INF,+INF,format("xp%d", i));
		inf.readSpace();
		int y = inf.readInt(-INF,+INF,format("yp%d", i));
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
