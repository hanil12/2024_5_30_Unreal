#pragma once
class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();

private:
	void DFS(int32 here);

private:
	unordered_map<const char*, int32>	_nameToId;
	unordered_map<int32, const char*>	_idToName;
	map<int32, set<int32>>				_lockHistory; // adjacent 역할

	Mutex _lock;

	// -- DFS에 필요한 것들
	vector<int32>	_discoveredOrder; // 노드가 발견된 순서를 기입하는 배열
	int32			_discoveredCount = 0;
	vector<bool>	_finished; // 현재(here) DFS가 끝났는지 여부
	vector<int32>	_parent;
};

