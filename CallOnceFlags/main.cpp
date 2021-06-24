#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

once_flag onceFlag;
void do_once()
{
    call_once(onceFlag, []() { cout << "Only once." << endl; });
}

void do_once2()
{
    call_once(onceFlag, []() { cout << "Only once2" << endl; });
}

int main()
{

    thread t1(do_once);
    thread t2(do_once);
    thread t3(do_once2);
    thread t4(do_once2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
