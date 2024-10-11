#pragma once
class RefCountable
{
public:
	RefCountable() : _refCount(1) {}
	virtual ~RefCountable() { }

	int32 GetRefCount() { return _refCount; }

	int32 AddRef() { return ++_refCount; }
	int32 ReleaseRef()
	{
		int32 refCount = --_refCount;

		if (refCount == 0) //
		{
			delete this;
		}

		return refCount;
	}
	

private:
	atomic<int32> _refCount;
};

template <typename T>
class TSharedPtr
{
public:
	TSharedPtr() {}
	TSharedPtr(T* ptr) { Set(ptr); }
	
	TSharedPtr(const TSharedPtr& other) { Set(other._ptr); }
	TSharedPtr(TSharedPtr&& rv) { _ptr = rv._ptr; rv._ptr = nullptr; }

	// 상속관계에서의 복사생성자
	template<typename U>
	TSharedPtr(const TSharedPtr<U>& child) { Set(static_cast<T*>(child._ptr)); }

	~TSharedPtr() { Release(); }

public: // 연산자 오버로딩
	TSharedPtr& operator=(const TSharedPtr& other)
	{
		if (_ptr != other._ptr)
		{
			Release();
			Set(other._ptr);
		}

		return *this;
	}

	// 오른값 참조를 매개변수로 받는 대입연산자
	TSharedPtr& operator=(TSharedPtr&& rv)
	{
		Release();
		_ptr = rv._ptr;
		rv._ptr = nullptr;
		return *this;
	}

	bool operator==(const TSharedPtr& other) const { return _ptr == other._ptr; }
	bool operator!=(const TSharedPtr& other) const { return _ptr != other._ptr; }
	bool operator==(T* ptr) const { return _ptr == ptr; }
	bool operator!=(T* ptr) const { return _ptr != ptr; }
	bool operator<(const TSharedPtr& other) const { return _ptr < other._ptr; }
	T*	 operator*() { return _ptr; }
	const T* operator*() const { return _ptr; }
	T*	 operator->() { return _ptr; }
	const T* operator->() const { return _ptr; }

	bool IsNull() { return _ptr == nullptr; }

private:
	void Set(T* ptr)
	{
		_ptr = ptr;
		if(ptr)
			ptr->AddRef();
	}

	void Release()
	{
		if (_ptr != nullptr)
		{
			_ptr->ReleaseRef();
			_ptr = nullptr;
		}
	}

private:
	// T... 제일 선조는 RefCountable이 와야한다.
	T* _ptr = nullptr;
};

