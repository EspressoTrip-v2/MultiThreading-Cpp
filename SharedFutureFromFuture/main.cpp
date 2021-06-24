#include <iostream>
#include <future>
#include <thread>
#include <utility>
#include <mutex>
using namespace std;

mutex cMutex;

struct Div
{
    void operator()(promise<int> &&intPromise, int a, int b)
    {
        intPromise.set_value(a / b);
    }
};

struct Requester
{
    void operator()(shared_future<int> shaFut)
    {
        lock_guard<mutex> lck(cMutex);

        cout << "Thread : " << this_thread::get_id() << " -> ";
        cout << "20 / 10 = " << shaFut.get() << endl;

    }
};

int main()
{
    cout << boolalpha << endl;

    // promise
    promise<int> divPromise;

    // future
    future<int> divResult = divPromise.get_future();
    cout << "divResult.valid(): " << divResult.valid() << endl;

    Div div;
    thread divThread(div, move(divPromise), 20, 10);
    cout << "divResult.valid(): " << divResult.valid() << endl;

    // create shared future from future
    shared_future<int> sharedResult = divResult.share();
    cout << "divResult.valid(): " << divResult.valid() << "\n\n";

    Requester req;
    thread sThread1(req, sharedResult);
    thread sThread2(req, sharedResult);
    thread sThread3(req, sharedResult);
    thread sThread4(req, sharedResult);
    thread sThread5(req, sharedResult);

    divThread.join();
    sThread1.join();
    sThread2.join();
    sThread3.join();
    sThread4.join();
    sThread5.join();

    return 0;
}
