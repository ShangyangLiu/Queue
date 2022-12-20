/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "grid.h"
#include "vector.h"
#include "OurQueue.h"
using namespace std;

int main()
{
    cout<<"请输入一个queue:";
    OurQueue<int> queue;
    cin>>queue;
    OurQueue<int> queue1(queue);
    cout<<"将queue copy给 queue1，queue1的结果为："<<queue1<<endl;
    cout<<"queue.peek()的结果为："<<queue.peek()<<endl;
    cout<<"queue.dequeue()的结果为："<<queue.dequeue()<<endl;
    queue.enqueue(5);
    cout<<"queue.enqueue(5)"<<queue<<endl;
    if(queue == queue1)
        cout<<"现在queue==queue1"<<endl;
    else
        cout<<"现在queue ！= queue1"<<endl;

    return 0;

}








