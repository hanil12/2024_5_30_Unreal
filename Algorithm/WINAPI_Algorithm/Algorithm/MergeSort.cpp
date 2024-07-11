#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// 처음들어왔을 때는 제일 작게 쪼개져있는 상태
	int leftIndex = left;
	int rightIndex = mid + 1;
	// [55] / [30]
	// left = 0
	// right = 1
	// 
	// leftIndex = 0
	// rightIndex = 1
	// mid = 0

	vector<int> temp;

	while (true)
	{
		
		if(leftIndex > mid || rightIndex > right)
			break;

		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
			// temp : 
		}
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
			// temp : 30
			// leftIndex : 0
			// rightIndex : 2
		}
	}

	// 왼쪽에 있던 원소들이 temp에 다 복사가 되었다.
	// right 배열이 남아있었다.
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}
	// 오른쪽에 있던 원소들이 temp에 다 복사가 되었다.
	// left 배열이 남아있다.
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if(left >= right)
		return;

	int mid = (left + right) / 2;

	// Divide
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	// Conquer
	MergeResult(v, left, mid, right);
}

int main()
{
	vector<int> v = { 55,30,15,100,1,5,70 };

	//MergeSort(v, 0, v.size()-1);
	// n x logn 만큼의 시간복잡도를 가지는 정렬 3인방
	//std::sort(v.begin(), v.end());
	//std::partial_sort(v.begin(),v.begin() + 3, v.end());
	std::stable_sort(v.begin(), v.end());

	return 0;
}