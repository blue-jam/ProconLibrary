#include <io.h>
#include "testlib.h"

const double EPS = 1e-8;

int main(int argc, char *argv[]){
	setName("compair list of doubles");
	registerTestlibCmd(argc, argv);

	int n = 0;
	while(!ans.seekEof()){
		double jx = ans.readDouble();
		double px = ouf.readDouble();
		if (!doubleCompare(jx, px, EPS)){
			quitf(_wa, "%d%s line differ", n, englishEnding(n).c_str());
		}
	}
	quitf(_ok, "passed");
}
