#include <iostream>
#include <future>
#include <thread>
#include <deque>
using namespace std;

// Package task is a wrapper for a callable
class SumUp
{
public:
    long long int operator()(int beg, int end)
    {
        long long int sum{0};
        for (auto i{beg}; i < end; i++)sum += i;
        return sum;
    }
};

int main()
{
    cout << endl;
    SumUp s1;
    SumUp s2;
    SumUp s3;
    SumUp s4;

    // Wrap the tasks
    packaged_task<int(int, int)> sumTask1(s1);
    packaged_task<int(int, int)> sumTask2(s2);
    packaged_task<int(int, int)> sumTask3(s3);
    packaged_task<int(int, int)> sumTask4(s4);

    // create the futures
    future<int> sumResult1 = sumTask1.get_future();
    future<int> sumResult2 = sumTask2.get_future();
    future<int> sumResult3 = sumTask3.get_future();
    future<int> sumResult4 = sumTask4.get_future();

//    sumTask1(1, 2000);
//    sumTask2(1, 30);
//    sumTask3(1, 200);
//    sumTask4(1, 1000);
//
//    cout << sumResult1.get() << endl;
//    cout << sumResult2.get() << endl;
//    cout << sumResult3.get() << endl;
//    cout << sumResult4.get() << endl;

    // Push tasks on container
    deque<packaged_task<int(int, int)>> allTasks;
    allTasks.push_back(move(sumTask1));
    allTasks.push_back(move(sumTask2));
    allTasks.push_back(move(sumTask3));
    allTasks.push_back(move(sumTask4));

    int begin{1};
    int increment{2500};
    int end = begin + increment;

    // Perform each calculation in a separate thread
    while (!allTasks.empty())
    {
        packaged_task<int(int, int)> myTask = move(allTasks.front());
        allTasks.pop_front();

        thread sumThread(move(myTask), begin, end);
        begin = end;
        end += increment;
        sumThread.detach();
    }

    // Pick up results
    auto sum = sumResult1.get() + sumResult2.get() +
               sumResult3.get() + sumResult4.get();

    cout << "sum of 0 .. 10000 = " << sum << endl;
    cout << endl;

    return 0;
}
