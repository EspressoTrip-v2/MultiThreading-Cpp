#include <iostream>
#include <future>
#include <functional>
#include <utility>
#include <vector>
using namespace std;
//@formatter:off
void calcProducts(packaged_task < int(int, int) > &task,
const vector<pair<int, int>> &pairs
)
{
for (
auto &pair
:pairs)
{
auto fut = task.get_future();
task(pair
.first, pair.second);
cout << pair.first << " * " << pair.second << " = " << fut.
get()
<<
endl;
task.
reset();
}
}
//@formatter:on
int main()
{

    cout << endl;
    vector<pair<int, int>> allPairs;
    allPairs.emplace_back(make_pair(1, 2));
    allPairs.emplace_back(make_pair(3, 4));
    allPairs.emplace_back(make_pair(5, 6));
    allPairs.emplace_back(make_pair(7, 8));

    packaged_task<int(int, int)> task{[](int fir, int sec) { return fir * sec; }};

    calcProducts(task, allPairs);
    cout << endl;

    thread t(calcProducts, ref(task), ref(allPairs));
    t.join();


    return 0;
}
