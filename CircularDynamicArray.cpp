//Create a dynamic array class called "CircularDynamicArray" class. It should manage the storage of an array that can grow and shrink. The class should be implemented using templates. As items are added and removed from both the front and end of the array, the items will always be referenced using indices 0...size-1

#include <iostream>
#include <string>

using namespace std;

//code a circulardynamic array. Default constructor. The array should be a capacity of 2 and size 0. Make the running time O(1)
//for this constructor the array should be of capacity and size s.

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
