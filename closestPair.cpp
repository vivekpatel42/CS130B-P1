using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <limits>
#include <algorithm>
#include <float.h>

bool pairCompareX(const pair<double, double>& firstElem, const pair<double, double>& secondElem);
bool pairCompareY(const pair<double, double>& firstElem, const pair<double, double>& secondElem);
double distance(pair<double, double> firstPair, pair<double, double> secondPair);
pair<double, double>* brute(vector<pair<double, double>> points, int n);
pair<double, double>* basic(vector<pair<double, double>> points, int n);
pair<double, double>* basicHelper(vector<pair<double, double>> points, int n);
pair<double, double>* minimumStripBasic(pair<double, double>* strip, int size, double delta);
pair<double, double>* optimal(vector<pair<double, double>> points, int n);
pair<double, double>* optimalHelper(vector<pair<double, double>> pointsX, vector<pair<double, double>> pointsY, int n);
pair<double, double>* minimumStripOptimal(pair<double, double>* strip, int size, double delta);

// main: reads user input and determines which of the 3 algorithm implementations to run
// (brute, basic, or optimal)
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
			pair<double, double>* targetPoints = new pair<double, double>[2];
			if (strcmp(arg, "brute") == 0) {
				printf("Running brute force algorithm...\n");
				targetPoints = brute(points, points.size());
				printf("Distance: %lf\n", distance(targetPoints[0], targetPoints[1]));
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			} else if (strcmp(arg, "basic") == 0) {
				printf("Running basic algorithm...\n");
				targetPoints = basic(points, points.size());
				printf("Distance: %lf\n", distance(targetPoints[0], targetPoints[1]));
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			} else if (strcmp(arg, "optimal") == 0) {
				printf("Running optimal algorithm...\n");
				targetPoints = optimal(points, points.size());
				printf("Distance: %lf\n", distance(targetPoints[0], targetPoints[1]));
				for (int i = 0; i < 2; i++) {
					printf("(%.7lf, %.7lf)\n", targetPoints[i].first, targetPoints[i].second);
				}
			}
		}
	}
}

// Custom comparison function for sorting a vector of pairs by x-coordinate
bool pairCompareX(const pair<double, double>& point1, const pair<double, double>& point2) {
	return point1.first < point2.first;
}

// Custom comparison function for sorting a vector of pairs by y-coordinate
bool pairCompareY(const pair<double, double>& point1, const pair<double, double>& point2) {
	return point1.second < point2.second;
}

// Finds distance between a pair of points in two dimensions
double distance(pair<double, double> firstPair, pair<double, double> secondPair)
{
	return sqrt(pow((firstPair.first - secondPair.first), 2) + pow((firstPair.second - secondPair.second), 2));
}

pair<double, double>* brute(vector<pair<double, double>> points, int n)
{
	double minDist = DBL_MAX;
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
	return targetPoints;
}

// basic and basicHelper are the implementation for the basic divide-and-conquer algorithm
pair<double, double>* basic(vector<pair<double, double>> points, int n) {
	sort(points.begin(), points.end(), pairCompareX);
	return basicHelper(points, points.size());
}

pair<double, double>* basicHelper(vector<pair<double, double>> points, int n) {

	if (n <= 3) {
        return brute(points, n);
	} 

    int mid = n/2;
    pair<double, double> median = points[mid];

	pair<double, double>* resultRight = new pair<double, double>[2]; 
	pair<double, double>* resultLeft = new pair<double, double>[2];
	pair<double, double>* result = new pair<double, double>[2];

	vector<pair<double, double>> leftSubVector(points.begin(), points.begin() + mid);
	vector<pair<double, double>> rightSubVector(points.begin() + mid, points.end()); 

    resultRight = basicHelper(rightSubVector, mid);
    resultLeft = basicHelper(leftSubVector, n - mid);

	double deltaRight = distance(resultRight[0], resultRight[1]);
	double deltaLeft = distance(resultLeft[0], resultLeft[1]);
	double delta;
 
    if (deltaRight <= deltaLeft) {
    	result = resultRight;
    	delta = deltaRight;
    }
    else {
    	result = resultLeft;
    	delta = deltaLeft;
    }
 
    pair<double, double> strip[n];
    pair<double, double>* stripResult = new pair<double, double>[2];

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (abs(points[i].first - median.first) < delta) {
            strip[index] = points[i]; 
			index++;
		}
	} 

	stripResult = minimumStripBasic(strip, index, delta);
	double stripDist = distance(stripResult[0], stripResult[1]);

	if (delta <= stripDist) {
		return result;
	}
	else {
		return stripResult;
	}
}

pair<double, double>* minimumStripBasic(pair<double, double>* strip, int size, double delta) {
    double minimum = delta;
 	pair<double, double>* result = new pair<double, double>[2];
 	result[0] = make_pair(-DBL_MAX, -DBL_MAX);
 	result[1] = make_pair(DBL_MAX, DBL_MAX);
    sort(strip, strip + size, pairCompareY); 
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (distance(strip[i],strip[j]) < minimum) {
                minimum = distance(strip[i], strip[j]);
                result[0] = strip[i];
                result[1] = strip[j];
            }
        }
    }
 
    return result;
}

pair<double, double>* optimal(vector<pair<double, double>> points, int n) {
	vector<pair<double, double>> pointsX = points;
	vector<pair<double, double>> pointsY = points;
	sort(pointsX.begin(), pointsX.end(), pairCompareX);
	sort(pointsY.begin(), pointsY.end(), pairCompareY);
	return optimalHelper(pointsX, pointsY, pointsX.size());
}

pair<double, double>* optimalHelper(vector<pair<double, double>> pointsX, vector<pair<double, double>> pointsY, int n) {
	if (n <= 3) {
        return brute(pointsX, n);
	}
    int mid = n/2;
    pair<double, double> median = pointsX[mid];
    vector<pair<double, double>> leftY;   
    vector<pair<double, double>> rightY;  
    for (int i = 0; i < n; i++)
    {
      if (pointsY[i].first <= median.first) {
         leftY.push_back(pointsY[i]);
      }
      else {
         rightY.push_back(pointsY[i]);
      }
    }

   	pair<double, double>* resultRight = new pair<double, double>[2]; 
	pair<double, double>* resultLeft = new pair<double, double>[2];
	pair<double, double>* result = new pair<double, double>[2];

	vector<pair<double, double>> leftSubVector(pointsX.begin(), pointsX.begin() + mid);
	vector<pair<double, double>> rightSubVector(pointsX.begin() + mid, pointsX.end()); 

    resultRight = optimalHelper(rightSubVector, rightY, n - mid);
    resultLeft = optimalHelper(leftSubVector, leftY, mid);

	double deltaRight = distance(resultRight[0], resultRight[1]);
	double deltaLeft = distance(resultLeft[0], resultLeft[1]);
	double delta;

	if (deltaRight <= deltaLeft) {
		delta = deltaRight;
		result = resultRight;
	}
	else {
		delta = deltaLeft;
		result = resultLeft;
	}

    pair<double, double> strip[n];
    pair<double, double>* stripResult = new pair<double, double>[2];

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (abs(pointsY[i].first - median.first) < delta) {
            strip[index] = pointsY[i]; 
			index++;	
		}
	} 

	stripResult = minimumStripOptimal(strip, index, delta);
	double stripDist = distance(stripResult[0], stripResult[1]);

	if (delta <= stripDist) {
		return result;
	}
	else {
		return stripResult;
	}
}

pair<double, double>* minimumStripOptimal(pair<double, double>* strip, int size, double delta) {
	double minimum = delta;
	pair<double, double>* result = new pair<double, double>[2];
	result[0] = make_pair(-DBL_MAX, -DBL_MAX);
	result[1] = make_pair(DBL_MAX, DBL_MAX);
	for (int i = 0; i < size; i++) {
	    for (int j = i+1; j < size; j++) {
	        if (distance(strip[i],strip[j]) < minimum) {
	            minimum = distance(strip[i], strip[j]);
	            result[0] = strip[i];
	            result[1] = strip[j];
	    	}
		}	
	}
	return result;
}