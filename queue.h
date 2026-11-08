#include <iostream>
using namespace std;


class Queue
{
private:
    int size, front, rear, capacity;
    int *arr;

public:
    Queue() {

        capacity = 100; 
        front = 0;
        rear = -1;
        size = 0;
        arr = new int[capacity];

    }
    void enqueue(int value) {
        if (size >= capacity){
            cout<< "Queue overflow!"<< endl;
            return;
        }
        rear = (rear + 1) % capacity; 
        arr[rear] = value;
        size++;
    }
    void dequeue(){
        if (size == 0){
            cout<< "Queue is empty" << endl;
            return;
        }
        
        front = (front + 1) % capacity;
        size--;
    }
    int peek() {
        if (size <= 0) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[front];
    }

     bool isEmpty() {
        return size == 0;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }


};