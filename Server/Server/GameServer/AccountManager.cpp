#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

AccountManager* AccountManager::_instance = nullptr;

void AccountManager::Login()
{
	WRITE_LOCK;

	cout << "LogIn 시도" << endl;
	this_thread::sleep_for(100ms);

	// DEAD LOCK 유발
	User* user = UserManager::GetInstance()->GetUser(10);

	return;
}
