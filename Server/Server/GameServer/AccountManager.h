#pragma once

struct Account
{
	// ID, Password, Name
};

class AccountManager
{
private:
	AccountManager(){}
	~AccountManager() {}

public:
	static void Create()
	{
		if(_instance == nullptr) _instance = new AccountManager();
	}

	static void Delete()
	{
		if(_instance != nullptr) delete _instance;
	}

	static AccountManager* GetInstance()
	{
		return _instance;
	}

	Account* GetAccount(int32 id)
	{
		std::lock_guard<std::mutex> lg(_mutex);

		return nullptr;
	}

	void Login();


private:
	std::mutex _mutex;
	static AccountManager* _instance;
};

