#include <iostream>
#include <future>
#include <thread>
using namespace std;

int main()
{
    cout << endl;

    // Thread
    int res;
    thread t1([&]() {
        res = 2000 + 11;
    });
    t1.join();
    cout << "res: " << res << endl;

    // Async tasks
    auto fut = async([] { return 2000 + 11; });
    cout << "fut.get(): " << fut.get() << endl;
    cout << endl;
    return 0;
}
