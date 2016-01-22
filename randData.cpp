using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
	if (argc == 2) {
		int numPoints = atoi(argv[1]);
		int max = 10000, min = -10000;
		double point1, point2;
		for (int i = 0; i < numPoints; i++) {\
			point1 = min + (max - min)*(double)rand() / RAND_MAX;
			point2 = min + (max - min)*(double)rand() / RAND_MAX;
			cout << point1 << " " << point2 << endl;
		}
	}
	cout << flush;
	return 0;
}