#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

double distance(pair<double, double> firstPair, pair<double, double> secondPair);
pair<double, double>* brute(vector<pair<double, double>> &points);
pair<double, double>* basic(vector<pair<double, double>> &points);
pair<double, double>* optimal(vector<pair<double, double>> &points);

int main(int argc, char** argv)
{
	vector<pair<double, double>> points;
	if (argc == 2) {
		char* arg = argv[1];
		if (strcmp(arg, "brute") == 0 || strcmp(arg, "basic") == 0 || strcmp(arg, "optimal") == 0) {
			double xCoor, yCoor;
			printf("Please enter all points you would like to compute closest pair for: \n");
			while (scanf("%lf %lf", &xCoor, &yCoor) != EOF) {
				pair<double, double> tempPair = make_pair(xCoor, yCoor);
				points.push_back(tempPair);
			}
			printf("%d\n", points.size());
			pair<double, double>* targetPoints;
			if (strcmp(arg, "brute") == 0) {
				printf("Running brute force algorithm...\n");
				targetPoints = brute(points);
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			} else if (strcmp(arg, "basic") == 0) {
				printf("Running basic algorithm...\n");
				targetPoints = basic(points);
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			} else if (strcmp(arg, "optimal") == 0) {
				printf("Running optimal algorithm...\n");
				targetPoints = optimal(points);
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			}
		}
	}
}

double distance(pair<double, double> firstPair, pair<double, double> secondPair)
{
	return sqrt(pow((firstPair.first - secondPair.first), 2) + pow((firstPair.second - secondPair.second), 2));
}

pair<double, double>* brute(vector<pair<double, double>> &points)
{
	double minDist = INT_MAX;
	pair<double, double>* targetPoints = new pair<double, double>[2];
	for (int i = 0; i < points.size(); i++) {
	   for (int j = 0; j < points.size(); j++) {
			if (i != j && minDist > distance(points[i], points[j])) {
				minDist = distance(points[i], points[j]);
				targetPoints[0] = points[i];
				targetPoints[1] = points[j];
			}
		}
	}
	printf("Distance: %lf\n", minDist);
	return targetPoints;
}

pair<double, double>* basic(vector<pair<double, double>> &points) {
	pair<double, double>* targetPoints = new pair<double, double>[2];
	double minDist = INT_MAX;
  for (int i = 0; i < points.size(); i++) {
  	for (int j = i+1; j < points.size(); j++) {
    	if (i != j && minDist > distance(points[i], points[j])) {
      	minDist = distance(points[i], points[j]);
				targetPoints[0] = points[i];
				targetPoints[1] = points[j];
			}
		}	
	}
	printf("Distance: %.7lf\n", minDist);
	return targetPoints;
}

pair<double, double>* optimal(vector<pair<double, double>> &points) {
	pair<double, double>* targetPoints = new pair<double, double>[2];	
	return targetPoints;
}