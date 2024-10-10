#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

UserManager* UserManager::_instance = nullptr;

void UserManager::Save()
{
	WRITE_LOCK;

	cout << "Save 시도!!" << endl;
	this_thread::sleep_for(100ms);

	// DEAD LOCK 유발
	Account* account = AccountManager::GetInstance()->GetAccount(10);

	return;
}
