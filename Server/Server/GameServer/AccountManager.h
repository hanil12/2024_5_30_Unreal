#pragma once

struct Account
{
	// ID, Password, Name
};

class AccountManager
{
	USE_LOCK;

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
		WRITE_LOCK;

		return nullptr;
	}

	void Login();

private:
	static AccountManager* _instance;
};

