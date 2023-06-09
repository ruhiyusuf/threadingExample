#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <stdio.h>

class foo
{
private:
    int val;

public:
    void run()
    {
        while (1)
        {
            printf("%d\n", val);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    foo()
    {
        val = 0;
    }

    void inc()
    {
        val++;
    }
};

class foo2
{
    public:
    
    foo * otherClass;
    foo2 (foo *other){
        otherClass = other;
    }
    void increment(){
        int i = 0;
        while (i < 200)
        {
            otherClass->inc();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        }
    }
};

int main()
{
    foo myClass;
    std::thread t(&foo::run, &myClass);
    t.detach(); 

    std::thread t1(&foo2::increment, t);
    t1.detach();

    // while(1)
    // {
    //     myClass.inc();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    t.join();
    t1.join();
    return 1;
}

//first thread running on a forever loop that prints very 2 seconds
// second thread increments (in the constructur tell it how much to increment)
// code to detach, join and wait for the increment to happen, and then wait for value at the end, and then print