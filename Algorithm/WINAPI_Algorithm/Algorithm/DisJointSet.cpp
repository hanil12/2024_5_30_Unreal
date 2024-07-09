#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

struct User
{
	int guildId;
};

void GuildSystem()
{
	vector<User> users;

	for (int i = 0; i < 1000; i++)
	{
		User user;
		user.guildId = i;

		users.push_back(user);
	}

	// 0 ... 0
	// 1 ... 1
	// 555...555

	users[5].guildId = users[1].guildId;

	// guild Id가 2인 user 길드 Id 1으로 병합
	for (auto& user : users)
	{
		if (user.guildId == 2)
		{
			user.guildId = 1;
		}
	}
}

class Naive_DisJointSet
{
public:
	Naive_DisJointSet(int n)
	{
		_parent = vector<int>(n,0);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	// [0] [2] [4] [5]
	// [1]
	// [3]
	//  parent[3] == 1, parent[1] == 0
	int FindLeader(int u)
	{
		if(u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}


	 
	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if(uLeader == vLeader)
			return;

		_parent[vLeader] = uLeader;
	}

private:
	vector<int> _parent;
};

class DisJointSet
{
public:
	DisJointSet(int n)
	{
		_parent = vector<int>(n,0);
		_rank = vector<int>(n,1);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}

	//  u
	// [0]    [4] [5]
	// [1][2]
	// [3][6]
	//    [7]
	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if(uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
		{
			std::swap(uLeader, vLeader);
		}

		_parent[uLeader] = vLeader;

		if(_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

int main()
{
	DisJointSet set(10);

	set.Merge(5,6);
	set.Merge(0,1);
	set.Merge(3,5);
	set.Merge(1,3);

	cout << set.FindLeader(1) << endl;

	return 0;
}