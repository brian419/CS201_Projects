#include <iostream>
#include <string>

using namespace std;


template <class T>
class CircularDynamicArray
{
private:
    T *array;
    int capacity;
    int size;
    int front;
    int back;
public:
    CircularDynamicArray();
    CircularDynamicArray(int s);
    ~CircularDynamicArray();
    void push_back(T item);
    void push_front(T item);
    void pop_back();
    void pop_front();
    T get(int index);
    void set(int index, T item);
    int getSize();
    int getCapacity();
    void print();
};

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s)
{
    capacity = s;
    size = 0;
    front = 0;
    back = 0;
    array = new T[capacity];
}

//create a destructor that deletes the array. Make the running time O(1)
template <class T>
CircularDynamicArray<T>::~CircularDynamicArray()
{
    delete [] array;
}

//create an elmtype& [](int i); 
//this function should print a message if i is out of bounds and return a reference to value of type elmtype stored in the class for this purpose. 
//Make the running time O(1)
