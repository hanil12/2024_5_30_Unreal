#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

UserManager* UserManager::_instance = nullptr;

void UserManager::Save()
{
	// lock, atomic : All or Nothing
	std::lock_guard<std::mutex> lg(_mutex);

	// Account 확인
	Account* account = AccountManager::GetInstance()->GetAccount(10);
	
	// 계정정보 수정 혹은 저장
	// DB에 저장

	return;
}
