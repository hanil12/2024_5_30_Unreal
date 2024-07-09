#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

// MST : (Minimum Spanning Tree)
// DisJoint Set

vector<vector<int>> adjacent;

void CreateGraph_AdjacentMatrix()
{
	//    0  1  2  3  4  5  6
	// 0  T  T  T  F  T  F  F
	// 1  T  T  F  F  F  F  F
	// 2  T  F  T  T  T  T  F
	// 3  F  F  T  T  F  F  F
	// 4  T  F  T  F  T  F  T
	// 5  F  F  T  F  F  T  F
	// 6  F  F  F  F  T  F  T

	adjacent = vector<vector<int>>(7, vector<int>(7, -1));

	adjacent[0][0] = 0;
	adjacent[0][1] = 3;
	adjacent[0][2] = 2;
	adjacent[0][4] = 10;

	adjacent[1][0] = 3;
	adjacent[1][1] = 0;

	adjacent[2][0] = 2;
	adjacent[2][2] = 0;
	adjacent[2][3] = 7;
	adjacent[2][4] = 3;
	adjacent[2][5] = 5;

	adjacent[3][2] = 7;
	adjacent[3][3] = 0;

	adjacent[4][0] = 10;
	adjacent[4][2] = 3;
	adjacent[4][4] = 0;
	adjacent[4][6] = 4;

	adjacent[5][2] = 5;
	adjacent[5][5] = 0;

	adjacent[6][4] = 4;
	adjacent[6][6] = 0;
}

int main()
{
	CreateGraph_AdjacentMatrix();

	return 0;
}