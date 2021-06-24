#include <iostream>
#include <thread>
#include <future>
#include <utility>
using namespace std;
void product(promise<int> &&intPromise, int a, int b)
{
    intPromise.set_value(a * b);
}

struct Div
{
    void operator()(promise<int> &&intPromise, int a, int b)
    {
        intPromise.set_value(a / b);
    }
};

int main()
{

    int a{20};
    int b{10};

    // define promises
    promise<int> prodPromise;
    promise<int> divPromise;

    // get the futures
    future<int> prodResult = prodPromise.get_future();
    future<int> divResult = divPromise.get_future();

    // calculate the result in a separate thread
    thread prodThread(product, move(prodPromise), a, b); // Must move promise
    Div div;
    thread divThread(div, move(divPromise), a, b);

    // Results
    cout << "20 * 10 = " << prodResult.get() << endl;
    cout << "20 / 10 = " << divResult.get() << endl;

    divThread.join();
    prodThread.join();

    return 0;
}
