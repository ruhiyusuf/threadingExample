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
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

    void dec()
    {
        val--;
    }

    int getVal() {
        return val;
    }
};

class foo2
{
    public:
    
    foo2 (){
    }

    void increment(foo *target, int count, int sleep){
        while(count-- > 0)
        {
            target->inc();
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
        }

    }

    void decrement(foo *target, int sleep) {
        while(target->getVal() > 0) 
        {
            target->dec();
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
        }
    }
};

int main()
{
    foo myClass;
    foo2 incram1;
    foo2 incram2;

    // int count = 20;
    std::thread t(&foo::run, &myClass);
    std::thread t2(&foo2::increment, &incram1, &myClass, 20, 100);
    std::thread t3(&foo2::increment, &incram2, &myClass, 10, 500);


    t.detach(); 
    // t2.detach(); 
    // t3.detach();

    t2.join();
    t3.join();
    printf("exited out of t2 and t3");
    std::thread t4(&foo2::decrement, &incram1, &myClass, 500);

    t4.detach();
    while(1);
    return 1;
}

//first thread running on a forever loop that prints very 2 seconds
// second thread increments (in the constructur tell it how much to increment)
// code to detach, join and wait for the increment to happen, and then wait for value at the end, and then print

// decrement to zero only after done incrementing
