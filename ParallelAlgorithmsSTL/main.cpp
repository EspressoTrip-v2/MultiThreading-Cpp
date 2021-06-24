#include <iostream>
#include <algorithm>
#include <execution>
#include <vector>
#include <numeric>
#include <string>

using namespace std;
int main()
{

    // for_each_n
    vector<int> intVec{1, 2, 4, 5, 6, 7, 8, 9, 10};
    for_each_n(execution::par, intVec.begin(), 5, [](int &arg) { arg *= arg; });
    cout << "for_each_n: ";
    for (auto &i:intVec)cout << i << " ";
    cout << "\n\n";

    // exclusive_scan and inclusive_scan
    vector<int> resVec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    exclusive_scan(execution::par, resVec.begin(), resVec.end(), resVec.begin(),
            1, [](int fir, int sec) { return fir * sec; });
    cout << "exclusive_scan: ";
    for (auto &i:resVec)cout << i << " ";
    cout << endl;

    vector<int> resVec2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    inclusive_scan(execution::par, resVec2.begin(), resVec2.end(), resVec2.begin(),
            [](int fir, int sec) { return fir * sec; }, 1);
    cout << "inclusive_scan: ";
    for (auto &i:resVec2)cout << i << " ";
    cout << "\n\n";

    // transform_exclusive_scan and transform_inclusive_scan
    vector<int> resVec3{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> resVec4(resVec3.size());
    transform_exclusive_scan(execution::par, resVec3.begin(), resVec3.end(),
            resVec4.begin(), 0,
            [](int fir, int sec) { return fir + sec; },
            [](int arg) { return arg *= arg; });
    cout << "transform_exclusive_scan: ";
    for (auto &i:resVec4)cout << i << " ";
    cout << endl;

//    vector<string> strVec{"Only"s, "for"s, "testing"s, "purpose"s};
//    vector<int> resVec5(strVec.size());
//    transform_inclusive_scan(execution::par, strVec.begin(), strVec.end(),
//            resVec5.begin(), 0,
//            [](auto fir, auto sec) { return fir + sec; },
//            [](auto arg) { return arg.length(); });
//
//    cout << "transform_inclusive_scan: ";
//    for (auto &i: resVec5)cout << i << " ";
//    cout << "\n\n";

    // reduce and transform_reduce
    vector<string> strVec2{"Only"s, "for"s, "testing"s, "purpose"s};

    string res = reduce(execution::par, strVec2.begin() + 1, strVec2.end(),
            strVec2[0], [](auto fir, auto sec) { return fir + " : " + sec; });
    cout << "reduce: " << res << endl;

//    size_t res2 = transform_reduce(execution::par, strVec2.begin(), strVec2.end(),
//            0, [](auto s) { return s.length(); },
//            [](auto a, auto b) { return a + b; });
//    cout << "transform_reduce: " << res2 << endl;

    return 0;
}
