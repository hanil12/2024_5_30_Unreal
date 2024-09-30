#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

int64 Caculate()
{
	int64 sum = 0;

	for (int i = 0; i < 100'0000; i++)
	{
		sum++;
	}

	for (int i = 0; i < 10; i++)
	{
		int temp = 0; // 동기로 실행됬을 때는 temp가 먼저 잡히고
					  // 비동기로 실행됬을 때는 예측할 수 없다.
	}

	return sum;
}

void PromiseWorker(std::promise<string>&& promise)
{
	promise.set_value("Set Message");
}

void TaskWorker(std::packaged_task<int64(void)>&& task)
{
	task();
}

int main()
{
	// 동기방식(synchronous)
	int64 sum = Caculate();

	// future : 미래
	{
		// 비동기방식(asynchronous)
		// std::launch::deferred => 지연해서 실행시켜주세요.
		// std::launch::async => 쓰레드를 하나 따로 만들어서 실행
		std::future<int64> future = std::async(std::launch::async, Caculate);

		// TODO .... => future가 끝나던지 끝나지 않던지 간에 이 내용들이 실행
		int t = 1;

		int64 sum = future.get(); // get : 함수가 끝날 떄 까지 기달려서 리턴값

		cout << sum << endl;
	}

	// promise 
	// 미래(future)에 결과물을 반환할 것이라는 약속(promise)을 해줘 -> 계약서
	{
		std::promise<string> promise;
		std::future<string> future = promise.get_future(); // future에 반환하겠다는 약속

		thread t(PromiseWorker, std::move(promise)); // promise한테 일 시키기

		// future.wait(); // future가 잘 세팅되어있는지 확인... 끝날 때까지 대기
		std::future_status status = future.wait_for(10ms); // 0.01초동안 대기하면서 future가 끝났는지 확인.
		if (status == std::future_status::ready)
		{
			// TODO : future가 세팅이 잘되어있다. => 즉시실행 가능
		}

		string value = future.get(); // 비동기 방식으로 future에 값이 잘 세팅이 되어있는지 확인하고 반환.

		cout << value << endl;

		t.join();
	}

	// packaged_task : 일감을 만들어서 넘겨주는 방법
	{
		std::packaged_task<int64()> task(Caculate);
		std::future<int64> future = task.get_future();

		thread t(TaskWorker, std::move(task));

		int64 sum = future.get();

		cout << sum << endl;

		t.join();
	}

	// Cacluate하는데 Event방식, SpinLock 방식처럼 Lock,thread만들고 하는 작업들을 최소화
	// ... 작은 작업들을 비동기 방식으로 할 때 자주 쓴다.
	// => future

	return 0;
}