#include <iostream>
#include <thread>

using namespace std;
void helloFunction()
{
    cout << "Hello from a function. " << endl;
}

struct HelloFunctionObject
{
    void operator()() const
    {
        cout << "Hello from a function object" << endl;
    }
};

int main()
{
    thread t1(helloFunction);

    HelloFunctionObject object;
    thread t2(object);

    thread t3([]() {
        cout << "Hello from lambda." << endl;
    });

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
