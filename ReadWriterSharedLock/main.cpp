#include <iostream>
#include <map>
#include <shared_mutex>
#include <string>
#include <thread>

using namespace std;
map<string, int> teleBook{{"Juan",    1981},
                          {"Scott",   1976},
                          {"Ritchie", 1983}};
shared_timed_mutex teleBookMutex;

void addTpTeleBook(const string &name, int number)
{
    lock_guard<shared_timed_mutex> writerLock(teleBookMutex);
    cout << "STARTING UPDATE " << name << endl;
    this_thread::sleep_for(500ms);

    teleBook[name] = number;
    cout << "ENDING UPDATE " << name << endl;
}

void printNumber(const string &name)
{
    shared_lock<shared_timed_mutex> readerLock(teleBookMutex);
    auto search = teleBook.find(name);
    if (search != teleBook.end())
        cout << name << " : " << teleBook[name] << endl;
    else
        cout << name << " : Not found" << endl;
}
int main()
{
    thread reader1([]() { printNumber("Juan"); });
    thread reader2([]() { printNumber("Scott"); });
    thread w1([]() { addTpTeleBook("Scott", 1978); });
    thread reader3([]() { printNumber("Juan"); });
    thread reader5([]() { printNumber("Scott"); });
    thread w2([]() { addTpTeleBook("Bjarne", 1977); }); // This causes a race better to double check in printNumber
    thread reader4([]() { printNumber("Bjarne"); });
    thread reader6([]() { printNumber("Ritchie"); });
    thread reader7([]() { printNumber("Bjarne"); });
    thread reader8([]() { printNumber("Juan"); });

    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
    reader5.join();
    reader6.join();
    reader7.join();
    reader8.join();

    w1.join();
    w2.join();

    return 0;
}
