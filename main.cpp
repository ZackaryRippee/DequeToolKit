#include <iostream>
#include "deque.h" 
using namespace std;

int main() {
    Deque deque(4);

    cout << "Starting minor stress test" << endl;
    for (int i = 0; i < 50000; i++){
        deque.push_back(i);
        if (i % 5000 == 0){
	  cout << "Pushed " << i << " elements" << endl;
        }
    }

    cout << "Deque after pushes: ";
    for (size_t i = 0; i < 10 && i < deque.size(); i++){
        cout << deque[i] << " ";
    }
    cout << endl << "Size after pushes: " << deque.size() << endl;

    cout << "Popping elements.." << endl;
    for (int i = 0; i < 5000; i++){
        deque.pop_front();
        deque.pop_back();
        if (i % 500 == 0){
	  cout << "Popped " << (2 * i) << " elements." << endl;
        }
    }

    cout << "Deque after pops: ";
    if (!deque.empty()){
        cout << "Front: " << deque.front() << ", Back: " << deque.back() << endl;
    } else {
        cout << "Deque is empty." << endl;
    }
    cout << "Is empty? " << (deque.empty() ? "Yes" : "No") << endl;
    cout << "Size: " << deque.size() << endl;

    return 0;
}
