#include <iostream>
using namespace std;

const int MAX = 100;

class QueueArray {
private:
    int arr[MAX];
    int front; // Index of the front element
    int rear; // Index of the rear element
    int size; // Current size of the queue

public:
    QueueArray() {
        front = 0;
        rear = -1;
        size = 0;
    }

    // Enqueue
    void enqueue(int value) {
        if (size >= MAX) {
            cout << "Queue overflow!" << endl;
            return;
        }
        rear = (rear + 1) % MAX; // Circular increment
        arr[rear] = value;
        size++;
    }

    // Dequeue
    int dequeue() {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return INT_MIN;
        } else {
            int temp = arr[front];
            front = (front + 1) % MAX;
            size--;
            return temp;
        }
    }

    // Peek
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

    // Display
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[(front + i) % MAX] << " ";
        }
        cout << endl;
    }
};