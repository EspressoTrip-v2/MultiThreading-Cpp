#include <iostream>
#include <thread>

using namespace std;

class scoped_thread
{
    thread _t;
public:
    explicit scoped_thread(thread &t) : _t(move(t))
    {
        if (!_t.joinable()) throw logic_error("No thread");
        cout << "Create thread ID: " << _t.get_id() << endl;
    }
    ~scoped_thread()
    {
        cout << "Joined thread ID: " << _t.get_id() << endl;

        _t.join();
    }

    scoped_thread(scoped_thread &) = delete;
    scoped_thread &operator=(scoped_thread &) = delete;
};

int main()
{
    cout << "Main thread ID: " << this_thread::get_id() << endl;
    thread t1([]() { cout << "Lambda callable" << endl; });
    scoped_thread thread(t1);
    return 0;
}
