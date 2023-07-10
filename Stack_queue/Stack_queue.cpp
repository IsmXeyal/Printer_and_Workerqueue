#include <iostream>
#include <cassert>

using namespace std;

#include"Queue.h"

int main() {
    Queue<Worker*>* workerQueue = new Queue<Worker*>();

    workerQueue->enqueue(new Worker("Xeyal", "Ismayilov", 20, 9));
    workerQueue->enqueue(new Worker("Tuqay", "Memmedov", 25, 6));
    workerQueue->enqueue(new Worker("Yaqut", "Memmedova", 24, 4));
    workerQueue->enqueue(new Worker("Ahmed", "Ahmedov", 32, 3));

    Printer printer(workerQueue);

    printer.start();

    workerQueue->clear();
    delete workerQueue;

	return 0;
}