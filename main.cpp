#include <iostream>
using namespace std;


template <class T>
class Queue {
private:
	T* data = nullptr;
	int size = 0;
	int full_size = 10;
	void resize() {
		full_size += full_size + 1;
		T* new_data = new T[full_size];
		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
	}
public:
	Queue()
	{
		data = new T[full_size];
	}

	Queue(int size)
	{
		full_size = size;
		data = new T[full_size];
	}

	Queue(T* array, int size)
	{
		full_size = size;
		data = new T[full_size];
		for (int i = 0; i < size; i++)
		{
			data[i] = array[i];
		}
	}
	~Queue()
	{
		delete[] data;
	}
		

	bool is_full() { return size == full_size; }
	bool is_empty() { return size == 0; }
	void enqueue(T value)
	{
		if (is_full()) {
			resize();
		}
		data[size] = value;
		size++;
	}

	void dequeue() {
		if (is_empty())
		{
			cout << "Queue is empty" << endl;
		}
		T value = data[0];
		for (int i = 0; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}

	T front() {
		if (is_empty())
		{
			cout << "Queue is empty" << endl;
			return T();
		}
		return data[0];
	}
	T back() {
		if (is_empty())
		{
			cout << "Queue is empty" << endl;
			return T();
		}
		return data[size - 1];
	}
};


int main() {
	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	
	cout << "front element = " << q.front() << endl;
	cout << "back element = " << q.back() << endl;
	q.dequeue();
	cout << "front element = " << q.front() << endl;
	cout << "back element = " << q.back() << endl;
}