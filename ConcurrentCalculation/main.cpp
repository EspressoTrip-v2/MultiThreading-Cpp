#include <iostream>
#include <random>
#include <vector>
#include <future>
#include <numeric>
using namespace std;

static const int NUM = 1'000'000;

long long getDotProduct(vector<int> &v, vector<int> &w)
{

    auto vSize = v.size();
    auto future1 = async([&]() {

        return inner_product(&v[0], &v[vSize / 4], &w[0], 0LL);
    });

    auto future2 = async([&]() {

        return inner_product(&v[vSize / 4], &v[vSize / 2], &w[vSize / 4], 0LL);
    });

    auto future3 = async([&]() {
        return inner_product(&v[vSize / 2], &v[vSize * 3 / 4], &w[vSize / 2], 0LL);

    });

    auto future4 = async([&]() {

        return inner_product(&v[vSize * 3 / 4], &v[vSize], &w[vSize * 3 / 4], 0LL);
    });

//    return future1.get() + future2.get() + future3.get() + future4.get();
    return future1.get() + future2.get() + future3.get() + future4.get();
}

int main()
{
    cout << endl;
    // Random number generator
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<int> dist(0, 100);


    // Fill the vectors
    vector<int> v, w;
    v.reserve(NUM);
    w.resize(NUM);


    for (size_t i{0}; i < NUM; i++)
    {
        v.push_back(dist(engine));
        w.push_back(dist(engine));
    }

    cout << "getDotProduct(v, w): " << getDotProduct(v, w) << endl;
    cout << endl;


    return 0;
}
