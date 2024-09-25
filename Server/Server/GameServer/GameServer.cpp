#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

void Func1()
{
	for (int32 i = 0; i < 10000; i++)
	{
		UserManager::GetInstance()->Save();
	}
}

void Func2()
{
	for (int32 i = 0; i < 10000; i++)
	{
		AccountManager::GetInstance()->Login();
	}
}

int main()
{
	AccountManager::Create();
	UserManager::Create();

	std::thread t1(Func1);
	std::thread t2(Func2);

	t1.join();
	t2.join();

	cout << "Done" << endl;

	AccountManager::Delete();
	UserManager::Delete();
}