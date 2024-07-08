#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

template<typename T, typename Container = vector<T>, typename Pred = less<T>>
class Priority_queue
{
public:
	void push(const T& value)
	{
		_container.push_back(value);

		int now = _container.size() - 1;

		while (true)
		{
			if(now <= 0)
				break;

			int parent = (now - 1) / 2;
			if(Pred()(_container[now], _container[parent]))
				break;

			std::swap(_container[now], _container[parent]);
			now = parent;
		}
	}

	void pop()
	{
		_container[0] = _container.back();
		_container.pop_back();

		int now = 0;

		while (true)
		{
			int leftChild = now * 2 + 1;
			int rightChild = now * 2 + 2;

			if (leftChild >= (int)_container.size())
			{
				break;
			}

			int next = now;
			if (Pred()(_container[next], _container[leftChild]))
			{
				next = leftChild;
			}

			if (rightChild < (int)_container.size() && Pred()(_container[next] , _container[rightChild]))
			{
				next = rightChild;
			}

			if(next == now)
				break;

			std::swap(_container[now], _container[next]);
			now = next;
		}
	}

	const T& top()
	{
		return _container.front();
	}

	bool empty()
	{
		return _container.size() == 0;
	}

private:
	Container _container;
};

int main()
{
	Priority_queue<int,vector<int>,less<int>> pq;

	pq.push(5);
	pq.push(10);
	pq.push(50);
	pq.push(100);
	pq.push(1);
	pq.push(4);

	// N개에서 M만큼만 정렬하고 싶다.
	// => partial_sort => M * logN
	while (true)
	{
		if(pq.empty()) break;

		int top = pq.top();
		cout << top << endl;

		pq.pop();
	}

	return 0;
}