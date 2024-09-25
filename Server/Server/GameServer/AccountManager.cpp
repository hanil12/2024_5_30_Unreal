#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

AccountManager* AccountManager::_instance = nullptr;

void AccountManager::Login()
{
	std::lock_guard<std::mutex> lg(_mutex);

	// Login 성공, ,..?
	// -> 어떤 User인지 확인
	User* user = UserManager::GetInstance()->GetUser(10);

	// User확인 성공 및 클라이언트에게 메시지

	return;
}
