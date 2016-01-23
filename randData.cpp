using namespace std;

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
	srand(time(NULL));
	if (argc == 2) {
		int numPoints = atoi(argv[1]);
		int max = 10000, min = -10000;
		double point1, point2;
		for (int i = 0; i < numPoints; i++) {
			point1 = min + (max - min)*(double)rand() / RAND_MAX;
			point2 = min + (max - min)*(double)rand() / RAND_MAX;
			cout << point1 << " " << point2 << endl;
		}
	}
	return 0;
}