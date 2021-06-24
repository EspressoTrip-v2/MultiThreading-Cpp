#include <iostream>


class MySingleton
{
    MySingleton() = default;
    ~MySingleton() = default;
public:
    MySingleton(const MySingleton &) = delete;
    MySingleton &operator=(const MySingleton &) = delete;
    static MySingleton &getInstance()
    {
        static MySingleton instance;
        return instance;
    }
};

int main()
{
    MySingleton::getInstance();
    return 0;
}
