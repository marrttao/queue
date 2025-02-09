#include <iostream>
#include <random>
#include <windows.h> 
using namespace std;

template <typename T>
class Client {
public:
    int PrintsValue;
    int priority;
    Client() {
		PrintsValue = 0;
		priority = 0;
    }
    Client(int Priority) {
        this->priority = Priority;
    }
    void SetPrints() {
        cout << "Enter the number of prints: ";
        cin >> PrintsValue;
    }
};

class Printer {
public:
    int PrintsValue;
    int time_to_print;
    Printer(Client<int> c) {
        PrintsValue = c.PrintsValue;
    }
    void _print(Client<int> c) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(100, 500);
        
        int* PrintTotalTime = new int;
		*PrintTotalTime = 0;
		for (int i = 0; i < c.PrintsValue; i++) {
            
            time_to_print = dis(gen);
			*PrintTotalTime += time_to_print;
            Sleep(time_to_print);
			cout << "Printing page " << i + 1 << endl;
		}
		cout << endl << "Printing for client completed" << endl << endl;
		show_stats(*PrintTotalTime, c.PrintsValue);
		delete PrintTotalTime;
    }

    void show_stats(int TotalTime, int PrintsValue) {
		cout << "Total time to print: " << TotalTime << "ms" << endl;
		cout << "Total number of pages printed: " << this->PrintsValue << endl;
	}
};

template <typename T>
class Queue {
private:
    Client<int>* data = nullptr; 
    int size = 0;
    int full_size = 10;
    bool isSorted = false;

    void resize() {
        full_size += 1;
        Client<int>* new_data = new Client<int>[full_size]; 
        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

public:
    Queue() {
        data = new Client<int>[full_size]; 
    }

    Queue(int size) {
        full_size = size;
        data = new Client<int>[full_size]; 
    }

    Queue(Client<int>* array, int size) { 
        full_size = size;
        data = new Client<int>[full_size]; 
        for (int i = 0; i < size; i++) {
            data[i] = array[i];
        }
    }

    ~Queue() {
        delete[] data;
    }

    bool is_full() { return size == full_size; }
    bool is_empty() { return size == 0; }

    Client<int> GetPriorityElement() { 
        Client<int> max = data[0]; 
        for (int i = 1; i < size; i++) {
            if (data[i].priority < max.priority) {
                max = data[i];
            }
        }
        return max;
    }

    Client<int> GetLessPriorityElement() { 
        Client<int> min = data[0]; 
        for (int i = 1; i < size; i++) {
            if (data[i].priority > min.priority) {
                min = data[i];
            }
        }
        return min;
    }

    Client<int> SortPriority() { 
        Client<int> temp; 
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (data[i].priority > data[j].priority) {
                    temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
        isSorted = true;
        return data[0];
    }

    void InsertWithPriority(T value, int priority) {
        if (is_full()) {
            resize();
        }
        data[size].PrintsValue = value;
        data[size].priority = priority;
        isSorted = false;
        size++;
    }

    void PullHighestPriorityElement() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return;
        }

        if (!isSorted) {
            Client<int> max = GetPriorityElement();
            for (int i = 0; i < size; i++) {
                if (data[i].priority == max.priority) {
                    for (int j = i; j < size - 1; j++) {
                        data[j] = data[j + 1];
                    }
                    break;
                }
            }
            Printer p(max);
            p._print(max);
        }
        else {
            for (int i = 0; i < size - 1; i++) {
                data[i] = data[i + 1];
            }
        }

        size--;
    }

    T front() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return T();
        }
        if (!isSorted) {
            return GetPriorityElement().PrintsValue; 
        }
        else {
            return data[0].PrintsValue; 
        }
    }

    T back() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return T();
        }

        if (!isSorted) {
            return GetLessPriorityElement().PrintsValue; 
        }
        else {
            return data[size - 1].PrintsValue; 
        }
    }

    void show() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << "Value: " << data[i].PrintsValue << ", Priority: " << data[i].priority << endl; 
        }
    }
};

int main() {

	// i havent compare queue with printer cause i do like in shop, i have queue and printer is printer
    // i havent compare queue with printer cause i do like in shop, i have queue and printer is printer
    // i havent compare queue with printer cause i do like in shop, i have queue and printer is printer
    // i havent compare queue with printer cause i do like in shop, i have queue and printer is printer
    // i havent compare queue with printer cause i do like in shop, i have queue and printer is printer
    // i havent compare queue with printer cause i do like in shop, i have queue and printer is printer


    Queue<int> printerQueue;
    Client<int> client1(2);
    client1.PrintsValue = 10;
    Client<int> client2(3);
    client2.PrintsValue = 5;
    Client<int> client22(3);
    client22.PrintsValue = 7;
    Client<int> client3(1);
    client3.PrintsValue = 20;

   
    printerQueue.InsertWithPriority(client1.PrintsValue, client1.priority);
    printerQueue.InsertWithPriority(client2.PrintsValue, client2.priority);
    printerQueue.InsertWithPriority(client3.PrintsValue, client3.priority);
	printerQueue.InsertWithPriority(client22.PrintsValue, client22.priority);


   
    cout << endl << "Initial Queue:" << endl;
    printerQueue.show();

 
    cout << endl << "Processing highest priority client:" << endl;
    printerQueue.PullHighestPriorityElement();

    cout << endl << "Queue after processing one client : " << endl;
    printerQueue.show();
    printerQueue.PullHighestPriorityElement();
    printerQueue.PullHighestPriorityElement();
    printerQueue.PullHighestPriorityElement();

    return 0;
}
