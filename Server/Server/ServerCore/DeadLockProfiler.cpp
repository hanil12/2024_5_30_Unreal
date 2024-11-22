#include "pch.h"
#include "DeadLockProfiler.h"

// 
void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard guard(_lock);

	int32 lockId = 0;

	auto findIt = _nameToId.find(name);
	if (findIt == _nameToId.end())
	{
		lockId = static_cast<int32>(_nameToId.size());
		_nameToId[name] = lockId;
		_idToName[lockId] = name;
	}
	else
	{
		lockId = findIt->second;
	}

	// Push 후 두번 째 부터
	// ... 잡고 있는 락이 있었다면
	if (LLockStack.empty() == false)
	{
		const int32 prevId = LLockStack.top();
		if (lockId != prevId) // lock 스택에서 내 전꺼와 다르다면 사이클 판별을 해야한다.
		{
			set<int32>& history = _lockHistory[prevId]; 
			if (history.find(lockId) == history.end())
			{
				history.insert(lockId);
				CheckCycle();
			}
		}
	}

	LLockStack.push(lockId);
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard guard(_lock);

	if(LLockStack.empty())
		CRASH("MULTIPLE POP");

	int32 lockId = _nameToId[name];
	if(LLockStack.top() != lockId)
		CRASH("UNVAILD POP");

	LLockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	// DFS 전 초기화
	const int32 lockCount = static_cast<int32>(_nameToId.size());
	_discoveredOrder = vector<int32>(lockCount, -1);
	_discoveredCount = 0;
	_finished = vector<bool>(lockCount, false);
	_parent = vector<int32>(lockCount, -1);

	for (int32 lockId = 0; lockId < lockCount; lockId++)
	{
		DFS(lockId);
	}

	_discoveredOrder.clear();
	_finished.clear();
	_parent.clear();
}

void DeadLockProfiler::DFS(int32 here)
{
	if(_discoveredOrder[here] != -1)
		return;

	_discoveredOrder[here] = _discoveredCount++;

	auto findIt = _lockHistory.find(here);
	// here에서 인접한 정점이 없다. 
	// 1. 첫번째 락
	// 2. 마지막 Lock
	if (findIt == _lockHistory.end())
	{
		_finished[here] = true;
		return;
	}

	set<int32>& nextSet = findIt->second;
	for (int32 there : nextSet)
	{
		//  아직 방문하지 않았으면 방문
		if (_discoveredOrder[there] == -1)
		{
			_parent[there] = here;
			DFS(there);
			continue;
		}
		
		// 순방향 간선
		// here가 there보다 먼저 발견되었다면, there는 here의 후손이다.
		if(_discoveredOrder[here] < _discoveredOrder[there])
			continue;

		// 순방향이 아니고, DFS(there)가 아직 종료하지 않았다면, there는 here의 선조이다. => (역방향 간선)
		// - there는 here의 후손이였으며, 선조이다.
		if (_finished[there] == false)
		{
			cout << _idToName[here] << " -> " << _idToName[there] << endl;

			int32 now = here;
			while (true)
			{
				cout << _idToName[_parent[now]] << " -> " << _idToName[now] << endl;
				now = _parent[now];
				if(now == there)
					break;
			}

			CRASH("DEADLOCK_DETECTED");
		}
	}

	_finished[here] = true;
}
