#pragma once
struct User
{
	// User Info
};

class UserManager
{
	USE_LOCK;
private:
	UserManager() {}
	~UserManager() {}

public:
	static void Create() { if(_instance == nullptr) _instance = new UserManager(); }
	static void Delete() { if(_instance != nullptr) delete _instance; }
	static UserManager* GetInstance() { return _instance; }

	User* GetUser(int32 id)
	{
		WRITE_LOCK;

		// userInfo 정보 추출

		return nullptr;
	}

	void Save();

private:
	static UserManager* _instance;
};

