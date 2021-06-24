#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

struct CriticalData
{
    mutex m_mt;
};

void deadlock(CriticalData &a, CriticalData &b)
{
    cout << endl;
    unique_lock<mutex> guard1(a.m_mt, defer_lock); // Using defer_lock just passes ownership to the unique_lock
    cout << "First mutex on thread: " << this_thread::get_id() << endl;
    this_thread::sleep_for(1ms);

    unique_lock<mutex> guard2(b.m_mt, defer_lock);
    cout << "Second mutex on thread: " << this_thread::get_id() << endl;

    cout << "Get both mutex's from thread: " << this_thread::get_id() << endl;
    lock(guard1, guard2); // This locks the mutexes
    cout << endl;
}

void deadlockScoped(CriticalData &a, CriticalData &b)
{
    cout << endl;
    cout << "First (Scoped) on thread: " << this_thread::get_id() << endl;
    this_thread::sleep_for(1ms);
    cout << "Second (Scoped) on thread: " << this_thread::get_id() << endl;
    cout << "Both locked (Scoped) on thread: " << this_thread::get_id() << endl;
    scoped_lock(a.m_mt, b.m_mt);
    cout << endl;

}

int main()
{

    CriticalData c1;
    CriticalData c2;
    CriticalData c3;
    CriticalData c4;

    thread a([&]() { deadlock(c1, c2); });
    thread b([&]() { deadlock(c2, c1); });

    thread c([&]() { deadlockScoped(c3, c4); });
    thread d([&]() { deadlockScoped(c4, c3); });

    a.join();
    b.join();
    c.join();
    d.join();


    return 0;
}
