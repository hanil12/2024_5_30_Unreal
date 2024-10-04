#pragma once

template <typename T>
class LockBasedStack
{
public:
	void Push(const T& value)
	{
		UniqueLock lg(_m);
		_s.push(value);

		_cv.notify_one();
	}

	bool TryPop(OUT T& output)
	{
		UniqueLock lg(_m);

		if(_s.empty())
			return false;

		output = _s.top();
		_s.pop();

		return true;
	}

	void WaitPop(OUT T& output)
	{
		UniqueLock lg(_m);
		_cv.wait(lg, [this]()->bool { return _s.empty() == false; });

		output = _s.top();
		_s.pop();
	}

private:
	stack<T> _s;
	Mutex _m;
	ConditionV _cv;
};

