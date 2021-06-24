#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex coutMutex;

class Worker
{
    string m_name;
public:
    explicit Worker(const string &&mName) : m_name(mName)
    {}
    void operator()()
    {
        for (size_t i{0}; i <= 3; i++)
        {
            this_thread::sleep_for(200ms);
            coutMutex.lock();
            cout << m_name << " : Work " << i << " done !!!" << endl;
            coutMutex.unlock();

        }
    }

};

int main()
{
    cout << "Boss: Lets start working: \n\n";

    thread herb(Worker("herb"));
    thread andrei(Worker("  Andrei"));
    thread scott(Worker("    Scott"));
    thread bjarne(Worker("     Bjarne"));
    thread bart(Worker("       Bart"));
    thread jenne(Worker("        Jenne"));

    herb.join();
    andrei.join();
    scott.join();
    bjarne.join();
    bart.join();
    jenne.join();

    cout << "Boss: Lets go home..." << endl;

    return 0;
}
