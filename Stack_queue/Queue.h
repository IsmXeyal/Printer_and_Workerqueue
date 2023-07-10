#pragma once

const int Maxsize = 10;
typedef unsigned short int ushort;

template<class T>
class Queue {
private:
	T _arr[Maxsize];
	int _front = -1;
	int _rear = -1;
	int _size = 0;

public:
	int getSize();
	int getFront();
	int getRear();
	bool isEmpty();
	bool isFull();
	void enqueue(T newItem);
	T dequeue();
	T peek();
	void clear();

	template<class T>
	friend ostream& operator<<(ostream& print, const Queue<T>& queue);

	friend class Worker;
	friend class Printer;
};

template<class T>
int Queue<T>::getSize() {
	return this->_size;
}

template<class T>
int Queue<T>::getFront() {
	if (isEmpty()) {
		assert(!"Queue is empty!");
		return -1;
	}
	return this->_arr[this->_front];
}

template<class T>
int Queue<T>::getRear() {
	if (isEmpty()) {
		assert(!"Queue is empty!");
		return -1;
	}
	return this->_arr[this->_rear];
}

template<class T>
bool Queue<T>::isEmpty() {
	return (_front == -1);
}

template<class T>
bool Queue<T>::isFull() {
	return (_rear == Maxsize - 1);
}

template<class T>
void Queue<T>::enqueue(T newItem) {
	if (isFull()) {
		assert(!"Queue is full!");
		return;
	}

	if (_front == -1)
		_front = 0;

	_rear++;
	_arr[_rear] = newItem;
	_size++;
}

template<class T>
T Queue<T>::dequeue() {
	T element;
	if (isEmpty()) {
		assert(!"Queue is empty!");
	}

	element = _arr[_front];
	if (_rear == _front) {
		_front = -1;
		_rear = -1;
	}
	else
		_front++;

	_size--;
	return element;
}

template<class T>
T Queue<T>::peek() {
	if (isEmpty()) {
		assert(!"Queue is empty!");
	}
	return this->_arr[this->_front];
}

template<class T>
void Queue<T>::clear() {
	_front = -1;
	_rear = -1;
	_size = 0;
}

template<class T>
ostream& operator<<(ostream& print, const Queue<T>& queue) {
	for (int i = 0; i < queue._size; i++)
		print << queue._arr[i] << " ";
	return print;
}

class Worker {
	static ushort _static_id;
	ushort _id;
	char* _name;
	char* _surname;
	ushort _age;
	ushort _pageCount;

public:
	Worker() = delete;
	Worker(const char* name, const char* surname, ushort age, ushort pageCount) {
		size_t len = strlen(name);
		if (len >= 3) {
			if (this->_name != NULL)
				delete[] this->_name;

			this->_name = new char[++len];
			strcpy_s(this->_name, len, name);
		}
		else {
			assert(!"Wrong Name!");
		}

		size_t len1 = strlen(surname);
		if (len1 >= 3) {
			if (this->_surname != NULL)
				delete[] this->_surname;

			this->_surname = new char[++len1];
			strcpy_s(this->_surname, len1, surname);
		}
		else{
			assert(!"Wrong Surname!");
		}

		_id = ++_static_id;
		this->_age = age;
		this->_pageCount = pageCount;
	}

	ushort getId() { return this->_id; }
	char* getName() { return this->_name; }
	char* getSurname() { return this->_surname; }
	ushort getAge() { return this->_age; }
	ushort getPageCount() { return this->_pageCount; }

	void Show() {
		cout << "Id: " << (_id != 0 ? _id : 0) << endl;
		cout << "Name: " << (_name != nullptr ? _name : "NULL") << endl;
		cout << "Surname: " << (_surname != nullptr ? _surname : "NULL") << endl;
		cout << "Age: " << (_age != 0 ? _age : 0) << endl;
		cout << "PageCount: " << (_pageCount != 0 ? _pageCount : 0) << endl;
	}

	friend class Printer;

	template<class T>
	friend class Queue;
};

ushort Worker::_static_id = 0;

class Printer {
	Queue<Worker*>* WorkerQueue;

public:
	Printer(Queue<Worker*>* queue) {
		this->WorkerQueue = queue;
	}

	void start() {
		while (!WorkerQueue->isEmpty()) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			Worker* currentWorker = WorkerQueue->peek();
			currentWorker->Show();
			cout << endl;
			for (ushort i = 1; i <= currentWorker->_pageCount; i++) {
				cout << "Page No_: " << i << endl;
			}
			currentWorker->_pageCount = 0;
			WorkerQueue->dequeue();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
	}
};