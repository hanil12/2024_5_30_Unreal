#include "pch.h"

// window
// linux

void HelloThread()
{
    cout << "Hello Thread!!" << endl;
}

int main()
{
    // 쓰레드 생성
    // t는 새로운 쓰레드
    std::thread t(HelloThread);

    cout << t.hardware_concurrency() << endl;
    cout << t.get_id() << endl;
    cout << "Hello Main" << endl;

    // thread 멤버함수
    // - join
    // - joinable : 
    // - detach : 쓰레드 분리
    // - hardware_concurrency : 현재 운용가능한 쓰레드 개수
    // - get_id : 쓰레드 아이디

    // t가 끝날 때 까지 기다려서 합친다. => thread 종료
    t.join();
}