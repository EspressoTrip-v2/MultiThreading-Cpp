#include <iostream>
#include <exception>
#include <thread>
#include <future>
#include <utility>
using namespace std;

struct Div
{
    void operator()(promise<int> &&intPromise, int a, int b)
    {
        try
        {
            if (b == 0)
            {
                string errMessage = "Illegal division by zero error: "s + to_string(a) + " / " + to_string(b);
                throw runtime_error{errMessage};
            }
            intPromise.set_value(a / b);
        }
        catch (...)
        {
            intPromise.set_exception(current_exception());
        }
    }
};

void executeDiv(int nom, int denom)
{
    Div div;
    promise<int> divPromise;
    auto divResult = divPromise.get_future();
    thread t(div, move(divPromise), nom, denom);

    try
    {
        auto result = divResult.get();
        cout << nom << " / " << denom << " = " << result << endl;

    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }

    t.join();
}

int main()
{
    executeDiv(10, 10);
    executeDiv(20, 5);
    executeDiv(20, 0);

    return 0;
}
