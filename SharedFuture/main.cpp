#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <utility>
using namespace std;

mutex coutMutex;

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
        lock_guard<mutex> guard(coutMutex);

        cout << "threadId( " << this_thread::get_id() << " ): ";

        cout << "20 / 10 = " << shaFut.get() << endl;
    }
};

int main()
{
    cout << endl;

    // define the promises
    promise<int> divPromise;

    // get futures
    shared_future<int> divResult = divPromise.get_future();

    Div div;
    thread divThread(div, move(divPromise), 20, 10);

    Requester req;
    thread sThread1(req, divResult);
    thread sThread2(req, divResult);
    thread sThread3(req, divResult);
    thread sThread4(req, divResult);
    thread sThread5(req, divResult);

    divThread.join();

    sThread1.join();
    sThread2.join();
    sThread3.join();
    sThread4.join();
    sThread5.join();

    return 0;
}
