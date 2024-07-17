#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// Enchant
// N만큼 강화
// 강화는 100프로 성공하며 강화할 때 올라가는 수치는 +1, +2, +3이 랜덤으로 나오게된다.
// 이 때 N만큼 강화할 때 나오는 경우의 수를 구하라.
// 이 때 (1 <= N <= 100000)

int N = 7;
// +1 +1 +1
// +1 +2
// +2 +1
// +3

// 4

// N = 1
// 1

// N = 2
// 2

// N = 3
// 4

// N = 4
// 7

vector<int> cache = vector<int>(100001, -1);

int Enchant(int num)
{
	// 기저사향
	if(num == 0)
		return 1;

	if(num < 0)
		return 0;

	int& ref = cache[num];
	if(ref != -1)
		return ref;

	return ref = Enchant(num - 1) + Enchant(num - 2) + Enchant(num - 3);
}

int main()
{
	N = 7;
	int result = Enchant(4);
	cout << result << endl;

	return 0;
}