#include <iostream>
#include <future>
#include <chrono>

using namespace std;


int main()
{
    cout << endl;
    auto begin = chrono::system_clock::now();

    auto asyncLazy = async(launch::deferred,
            []() { return chrono::system_clock::now(); });

    auto asyncEager = async(launch::async,
            []() { return chrono::system_clock::now(); });

    this_thread::sleep_for(1s);

    auto lazyStart = asyncLazy.get() - begin;
    auto eagerStart = asyncEager.get() - begin;

    auto lazyDuration = chrono::duration<double>(lazyStart).count();
    auto eagerDuration = chrono::duration<double>(eagerStart).count();

    cout << "asyncLazy evaluation after: " << lazyDuration << " seconds." << endl;
    cout << "asyncEager evaluation after: " << eagerDuration << " seconds." << endl;

    cout << endl;

    return 0;
}
