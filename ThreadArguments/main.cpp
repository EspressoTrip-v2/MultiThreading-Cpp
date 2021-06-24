#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class Sleeper
{
    int &m_i;
public:
    explicit Sleeper(int &mI) : m_i(mI)
    {}

    void operator()(int k)
    {
        for (size_t i{0}; i <= 5; i++)
        {
            this_thread::sleep_for(100ms);
            m_i += k;
        }

        cout << "ID: " << this_thread::get_id() << endl;
    }
};

int main()
{
    int valSleeper{1000};
    cout << "Hardware capable thread number: " << thread::hardware_concurrency() << endl;

    thread t(Sleeper(valSleeper), 5);
    //t.detach(); // Causes issues as main thread finishes before child
    t.join();

    cout << "valSleeper = " << valSleeper << endl;

    return 0;
}
