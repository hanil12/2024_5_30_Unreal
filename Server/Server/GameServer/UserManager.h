#pragma once
struct User
{
	// User Info
};

class UserManager
{
private:
	UserManager() {}
	~UserManager() {}

public:
	static void Create() { if(_instance == nullptr) _instance = new UserManager(); }
	static void Delete() { if(_instance != nullptr) delete _instance; }
	static UserManager* GetInstance() { return _instance; }

	User* GetUser(int32 id)
	{
		std::lock_guard<std::mutex> lg(_mutex);

		// userInfo 정보 추출

		return nullptr;
	}

	void Save();

private:
	std::mutex _mutex;
	static UserManager* _instance;
};

