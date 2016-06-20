#include <io.h>
#include "testlib.h"

const double EPS = 1e-8;

int main(int argc, char *argv[]){
	setName("compares two signed integers");
	registerTestlibCmd(argc, argv);

	int n = 0;
	while(!ans.seekEof()){
		double jx = ans.readDouble();
		double jy = ans.readDouble();
		double px = ouf.readDouble();
		double py = ouf.readDouble();
		if (!doubleCompare(jx, px, EPS) || !doubleCompare(jy, py, EPS)){
			quitf(_wa, "%d%s line differ", n, englishEnding(n).c_str());
		}
	}
	quitf(_ok, "passed");
}
