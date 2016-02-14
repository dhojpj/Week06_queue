#include <iostream>
//#include <string>
//#include "driver.h"
#include "queue.h"

using namespace std;

int main()
{
    queue<int> i;


    i.enqueue(5);


    int r;

    i.dequeue(r);


    cout << r << endl;

    cout << i.size() << endl;





    return 0;
}
