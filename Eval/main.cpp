#include <iostream>
#include "Eval.h"

using namespace std;

int main() {
	if (eval::compare("5 = 5")) {
		cout << "True" << endl;
	} else {
		cout << "False" << endl;
	}

	return 0;
}
