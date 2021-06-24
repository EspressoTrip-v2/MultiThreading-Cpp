#include <iostream>
#include <string>
#include <mutex>
#include <thread>

using namespace std;

mutex coutMutex;
thread_local string s{"Hello from"}; // Like static variables for threads

void first()
{
    s += " first";
}

void second()
{
    s += " second";
}

void third()
{
    s += " third";
}
void addLocalThread(const string &s2)
{
    s += s2;

    first();
    second();
    third();

    lock_guard<mutex> guard(coutMutex);
    cout << s << endl;
    cout << "&s : " << &s << endl;
    cout << "Thread: " << this_thread::get_id() << endl;
    cout << endl;
}

int main()
{

    thread t1(addLocalThread, " t1:");
    thread t2(addLocalThread, " t2:");
    thread t3(addLocalThread, " t3:");
    thread t4(addLocalThread, " t4:");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
