#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    struct Element {
        T value;
        int priority;
    };

    Element* data = nullptr;
    int size = 0;
    int full_size = 10;
    bool isSorted = false;

    void resize() {
        full_size += 1;
        Element* new_data = new Element[full_size];
        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

public:
    Queue() {
        data = new Element[full_size];
    }

    Queue(int size) {
        full_size = size;
        data = new Element[full_size];
    }

    Queue(Element* array, int size) {
        full_size = size;
        data = new Element[full_size];
        for (int i = 0; i < size; i++) {
            data[i] = array[i];
        }
    }

    ~Queue() {
        delete[] data;
    }

    bool is_full() { return size == full_size; }
    bool is_empty() { return size == 0; }

    Element GetPriorityElement() {
        Element max = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i].priority < max.priority) {
                max = data[i];
            }
        }
        return max;
    }

    Element GetLessPriorityElement() {
        Element min = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i].priority > min.priority) {
                min = data[i];
            }
        }
        return min;
    }

    Element SortPriority() {
        Element temp;
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
        data[size].value = value;
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
            Element max = GetPriorityElement();
            for (int i = 0; i < size; i++) {
                if (data[i].priority == max.priority) {
                    for (int j = i; j < size - 1; j++) {
                        data[j] = data[j + 1];
                    }
                    break;
                }
            }
        } else {
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
            return GetPriorityElement().value;
        } else {
            return data[0].value;
        }
    }

    T back() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return T();
        }

        if (!isSorted) {
            return GetLessPriorityElement().value;
        } else {
            return data[size - 1].value;
        }
    }

    void show() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << "Value: " << data[i].value << ", Priority: " << data[i].priority << endl;
        }
    }
};

int main() {
    Queue<int> q;
    q.InsertWithPriority(1, 5);
    q.InsertWithPriority(2, 4);
    q.InsertWithPriority(3, 3);
    q.InsertWithPriority(4, 2);
    q.InsertWithPriority(5, 1);

    cout << "front element = " << q.front() << endl;
    cout << "back element = " << q.back() << endl;
    q.PullHighestPriorityElement();
    cout << "front element = " << q.front() << endl;
    cout << "back element = " << q.back() << endl;
    q.show();
    q.PullHighestPriorityElement();
    q.PullHighestPriorityElement();
    q.PullHighestPriorityElement();
    q.PullHighestPriorityElement();
    q.show();
    for (int i = 0; i < 22; i++) {
        q.InsertWithPriority(i, i);
    }
    if (q.is_full()) {
        cout << "Queue is full" << endl;
    }
}


