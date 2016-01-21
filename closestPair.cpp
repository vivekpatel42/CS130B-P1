#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

bool pairCompareX(const pair<double, double>& firstElem, const pair<double, double>& secondElem);
bool pairCompareY(const pair<double, double>& firstElem, const pair<double, double>& secondElem);
double distance(pair<double, double> firstPair, pair<double, double> secondPair);
pair<double, double>* brute(vector<pair<double, double>> points, int n);
pair<double, double>* basic(vector<pair<double, double>> points, int n);
pair<double, double>* optimal(vector<pair<double, double>> points, int n);

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
				targetPoints = brute(points, points.size());
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			} else if (strcmp(arg, "basic") == 0) {
				printf("Running basic algorithm...\n");
				targetPoints = basic(points, points.size());
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			} else if (strcmp(arg, "optimal") == 0) {
				printf("Running optimal algorithm...\n");
				targetPoints = optimal(points, points.size());
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			}
		}
	}
}

// Custom comparison function for vector of pairs along the x axis
bool pairCompareX(const pair<double, double>& firstElem, const pair<double, double>& secondElem) {
	return firstElem.first < secondElem.first;
}

// Custom comparison function for vector of pairs along the y axis
bool pairCompareY(const pair<double, double>& firstElem, const pair<double, double>& secondElem) {
	return firstElem.second < secondElem.second;
}

double distance(pair<double, double> firstPair, pair<double, double> secondPair)
{
	return sqrt(pow((firstPair.first - secondPair.first), 2) + pow((firstPair.second - secondPair.second), 2));
}

pair<double, double>* brute(vector<pair<double, double>> points, int n)
{
	double minDist = INT_MAX;
	pair<double, double>* targetPoints = new pair<double, double>[2];
	for (int i = 0; i < n; i++) {
	   for (int j = i+1; j < n; j++) {
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

pair<double, double>* basic(vector<pair<double, double>> points, int n) {
	pair<double, double>* targetPoints = new pair<double, double>[2];
	
	return targetPoints;
}

pair<double, double>* basicHelper(vector<pair<double, double>> points, int n) {

	if (n <= 3) {
        return brute(points, n);
	} 

    int mid = n/2;
    pair<double, double> median = points[mid];

	pair<double, double>* resultRight = new pair<double, double>[2];
	pair<double, double>* resultLeft = new pair<double, double>[2];

    resultRight = basicHelper(points, mid);
    resultLeft = basicHelper(points + mid, n - mid);

	double deltaRight = distance(resultRight[0], resultRight[1]);
	double deltaLeft = distance(resultLeft[0], resultLeft[1]);
 
    double delta = min(deltaRight, deltaLeft);
 
    pair<double, double>* strip = new pair<double, double>[n];

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (abs(points[i].first - median.first) < delta) {
            strip[index] = points[i]; 
			index++;
		}
	} 

    return min(delta, stripClosest(strip, j, delta));
}

double stripClosest(pair<double, double>* strip, int size, float d)
{
    double min = delta;
 
    sort(strip, size, sizeof(Point), compareY); 
 
    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);
 
    return min;
}

pair<double, double>* optimal(vector<pair<double, double>> points, int n) {
	pair<double, double>* targetPoints = new pair<double, double>[2];	
	return targetPoints;
}
