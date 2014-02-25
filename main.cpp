#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

#include "Reflectable/reflectable.h"

struct Foo
{
    std::string str;
    int i;
};

std::ostream& operator<<(std::ostream& left, const Foo& right)
{
    return left << "str: " << right.str << ", " << "i: " << right.i;
}

/// \brief A super basic printer
class SamplePrinter
{
    public:
        /// \brief Int serialization
        void operator () (int x)
        {
            std::cout << "int: " << x << std::endl;
        }

        /// \brief Float serialization
        void operator () (float x)
        {
            std::cout << "float: " << x << std::endl;
        }

        /// \brief Double serialization
        void operator () (double x)
        {
            std::cout << "double: " << x << std::endl;
        }

        /// \brief String serialization
        void operator () (const std::string& x)
        {
            std::cout << "string: " << x << std::endl;
        }

        /// \brief The generic case
        template <typename X>
        void operator () (const X& x)
        {
            std::cout << "other: " << x << std::endl;
        }

    private:
};

struct Test : public Reflectable<struct name_,      std::string,
                                struct health_,    int,
                                struct foo_,       Foo>
{
    Test() : name(get<name_>()), health(get<health_>()), foo(get<foo_>())
    {
    }

    std::string& name;
    int& health;
    Foo& foo;
};

struct TestNormal
{
    std::string name;
    int health;
    Foo foo;
};

int main()
{
    Test test;
    test.get<name_>() = "bob";
    test.get<health_>() = 42;
    test.get<foo_>().str = "hello";
    test.get<foo_>().i = 24;

    test.iterate(SamplePrinter());

    std::cout << "\n\nBenchmarks:\n\n";

    clock_t time;

    // ******************************************
    // Raw for loop

    time = clock();
    for (int i = 0; i < 100000000; i++);
    time = clock()-time;
    std::cout << "Raw for loop: " << static_cast<float>(time)/CLOCKS_PER_SEC << "s\n";

    // ******************************************
    // Regular benchmark

    TestNormal testNormal;

    time = clock();
    for (int i = 0; i < 100000000; i++)
    {
        testNormal.foo.i = i;
    }
    time = clock()-time;
    std::cout << "Regular access: " << static_cast<float>(time)/CLOCKS_PER_SEC << "s\n";

    // ******************************************
    // Reflectable benchmark

    time = clock();
    for (int i = 0; i < 100000000; i++)
    {
        test.get<foo_>().i = i;
    }
    time = clock()-time;
    std::cout << "Reflectable access: " << static_cast<float>(time)/CLOCKS_PER_SEC << "s\n";

    // ******************************************
    // Reflectable with reference benchmark

    time = clock();
    for (int i = 0; i < 100000000; i++)
    {
        test.foo.i = i;
    }
    time = clock()-time;
    std::cout << "Reflectable with reference access: " << static_cast<float>(time)/CLOCKS_PER_SEC << "s\n";

    return 0;
}
