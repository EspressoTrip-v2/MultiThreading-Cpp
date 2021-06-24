#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std;

void getAnswer(promise<int> &intPromise)
{
    this_thread::sleep_for(3s);
    intPromise.set_value(42);
}
int main()
{
    cout << endl;
    promise<int> answerPromise;
    auto fut = answerPromise.get_future();

    thread answerThread(getAnswer, ref(answerPromise));

    future_status status;
    do
    {
        status = fut.wait_for(0.2s);
        cout << "...Doing something else" << endl;
    } while (status != future_status::ready);

    cout << endl;
    cout << "The Answer: " << fut.get() << "\n";

    answerThread.join();

    return 0;
}
