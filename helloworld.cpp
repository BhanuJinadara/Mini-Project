#include <iostream>
#include "queue.h"


using namespace std;

int main(){

    Queue queue = Queue();
    
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display();
    
    return 0;
}
