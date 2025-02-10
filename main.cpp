

// I haven’t done it yet, 
// I want to try to have time to parse doubly linked lists 
// to wednesday + write a database for the project so as not to let the team down. 
// The task is interesting, it can be implemented up to the level of realism that I would like to do








// I haven’t done it yet, 
// I want to try to have time to parse doubly linked lists 
// to wednesday + write a database for the project so as not to let the team down. 
// The task is interesting, it can be implemented up to the level of realism that I would like to do











#include <iostream>
#include <random>
using namespace std;

class Passenger {
public:
    static int id;
    int priority;
};

class Station {
private:
    int middlePassengerTime;
public:
    int MaxPassenger;
    bool isEnd;
    Station() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(12, 25);
        MaxPassenger = dis(gen);
        setPassengerTime();
        // cin to set isEnd`
        cout << "Is it end station? 1-yes, 0-no" << endl;
        cin >> isEnd;
    }
    void setPassengerTime() {
        int morning;
        int day;
        int evening;
        int night;
        cout << "Enter morning time: ";
        cin >> morning;
        cout << "Enter day time: ";
        cin >> day;
        cout << "Enter evening time: ";
        cin >> evening;
        cout << "Enter night time: ";
        cin >> night;

        cout << "choose time: 1-morning, 2-day, 3-evening, 4-night" << endl;
        int choose;
        cin >> choose;

        if (choose == 1) {
            middlePassengerTime = morning;
        }
        else if (choose == 2) {
            middlePassengerTime = day;
        }
        else if (choose == 3) {
            middlePassengerTime = evening;
        }
        else if (choose == 4) {
            middlePassengerTime = night;
        }
        else {
            cout << "wrong choose" << endl;
        }
    }
};

class Bus {
private:
    Station s;
    int middleArriveTime;
public:
    static int busId;
    int places;

    Bus() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(4, 25);
        places = dis(gen);
        setMiddleArriveTime();
        busId++;
    }
    int isFull() {
        return places == 0;
    }

    void BusArrive() {
        cout << "Bus arrived" << endl;
        if (s.isEnd) {
            cout << "End station all places free" << endl;
        }
    }

    void BusLeft() {
        if (isFull()) {
            cout << "Bus lefting" << endl;
        }
    }

    void setMiddleArriveTime() {
        int morning;
        int day;
        int evening;
        int night;
        // cin for all times
        cout << "Enter morning time: ";
        cin >> morning;
        cout << "Enter day time: ";
        cin >> day;
        cout << "Enter evening time: ";
        cin >> evening;
        cout << "Enter night time: ";
        cin >> night;

        cout << "choose time: 1-morning, 2-day, 3-evening, 4-night" << endl;
        int choose;
        cin >> choose;

        if (choose == 1) {
            middleArriveTime = morning;
        }
        else if (choose == 2) {
            middleArriveTime = day;
        }
        else if (choose == 3) {
            middleArriveTime = evening;
        }
        else if (choose == 4) {
            middleArriveTime = night;
        }
        else {
            cout << "wrong choose" << endl;
        }
    }

    template <typename T>
    class Queue {
    private:
        Bus b;
        Passenger* data = nullptr;
        int size = 0;
        int full_size = b.places;
        bool isSorted = false;

        

    public:
        Queue() {
            data = new Passenger[full_size];
        }

        ~Queue() {
            delete[] data;
        }

        bool is_full() { return size == full_size; }
        bool is_empty() { return size == 0; }

        Passenger GetPriorityElement() {
            Passenger max = data[0];
            for (int i = 1; i < size; i++) {
                if (data[i].priority < max.priority) {
                    max = data[i];
                }
            }
            return max;
        }

        Passenger GetLessPriorityElement() {
            Passenger min = data[0];
            for (int i = 1; i < size; i++) {
                if (data[i].priority > min.priority) {
                    min = data[i];
                }
            }
            return min;
        }

        Passenger SortPriority() {
            Passenger temp;
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
				cout << "Station is full" << endl;
				return;
            }
            data[size].priority = priority;
            isSorted = false;
            size++;
        }

        void PullHighestPriorityElementInBus() {
            if (is_empty()) {
                cout << "No Passengers" << endl;
                return;
            }
            if (b.isFull()) {
                cout << "Bus is full" << endl;
                return;
            }
            else {
                if (!isSorted) {
                    Passenger max = GetPriorityElement();
                    for (int i = 0; i < size; i++) {
                        if (data[i].priority == max.priority) {
                            for (int j = i; j < size - 1; j++) {
                                data[j] = data[j + 1];
                            }
                            break;
                        }
                    }
                }
                else {
                    for (int i = 0; i < size - 1; i++) {
                        data[i] = data[i + 1];
                    }
                }
                size--;
            }
        }

        T front() {
            if (is_empty()) {
                cout << "Queue is empty" << endl;
                return T();
            }
            if (!isSorted) {
                return GetPriorityElement().priority;
            }
            else {
                return data[0].priority;
            }
        }

        T back() {
            if (is_empty()) {
                cout << "Queue is empty" << endl;
                return T();
            }

            if (!isSorted) {
                return GetLessPriorityElement().priority;
            }
            else {
                return data[size - 1].priority;
            }
        }

        void show() {
            if (is_empty()) {
                cout << "Queue is empty" << endl;
                return;
            }
            for (int i = 0; i < size; i++) {
                cout << "Priority: " << data[i].priority << endl;
            }
        }
    };

    int getMiddleArriveTime() {
        return middleArriveTime;
    }
};

int main() {
    Bus bus;
    bus.BusArrive();
    bus.BusLeft();

    Bus::Queue<int> queue;
    queue.InsertWithPriority(1, 10);
    queue.InsertWithPriority(2, 5);
    queue.InsertWithPriority(3, 15);

    queue.show();
    queue.PullHighestPriorityElementInBus();
    queue.show();

    return 0;
}
