#include <iostream>
#include <string>

using namespace std;

template <class T>
class CircularDynamicArray
{
    private:
        
        T *array;
        int size;
        int front;
        int back;
        int capacityInt; 

    public: 

        CircularDynamicArray();
        CircularDynamicArray(int s);
        CircularDynamicArray(const CircularDynamicArray<T> &other);
        CircularDynamicArray<T>& operator=(const CircularDynamicArray<T> &other);
        ~CircularDynamicArray();
        T& operator[](int i);
        void addEnd(T v);
        void addFront(T v);
        void delEnd();
        void delFront();
        int length();
        int capacity();
        void clear();
        T QuickSelect(int k);
        T WCSelect(int k);
        void stableSort();
        int linearSearch(T e);
        int binSearch(T e);
        void reverse();
        


};

template <class T>
CircularDynamicArray<T>::CircularDynamicArray()
{
    this->capacityInt = 2;
    this->size = 0;
    this->front = 0;
    this->back = 0;
    this->array = new T[capacityInt];
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s)
{
    this->capacityInt = s;
    this->size = s;
    this->front = 0;
    this->back = 0;
    this->array = new T[capacityInt];
}

//create copy constructor
template <class T>
CircularDynamicArray<T>::CircularDynamicArray(const CircularDynamicArray<T> &other)
{
    this->capacityInt = other.capacityInt;
    this->size = other.size;
    this->front = other.front;
    this->back = other.back;
    this->array = new T[capacityInt];
    for (int i = 0; i < size; i++)
    {
        array[i] = other.array[i];
    }
}

//create assignment operator
template <class T>
CircularDynamicArray<T>& CircularDynamicArray<T>::operator=(const CircularDynamicArray<T> &other)
{

    if (this != &other)
    {
        delete[] array;
        this->capacityInt = other.capacityInt;
        this->size = other.size;
        this->front = other.front;
        this->back = other.back;
        this->array = new T[capacityInt];
        for (int i = 0; i < size; i++)
        {
            array[i] = other.array[i];
        }
    }
    return *this;
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray()
{
    delete[] array;
}

template <class T>
T& CircularDynamicArray<T>::operator[](int i)
{
    if (i < 0 || i > size)
    {
        cout << "Index out of bounds" << endl;
    }
    return array[i];

}

template <class T>
void CircularDynamicArray<T>::addEnd(T v)
{
    if (size == capacityInt)
    {
        T *temp = new T[capacityInt * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
        capacityInt = capacityInt * 2;
    }
    array[size] = v;
    size++;
}

template <class T>
void CircularDynamicArray<T>::addFront(T v)
{
    if (size == capacityInt)
    {
        T *temp = new T[capacityInt * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
        capacityInt = capacityInt * 2;
    }
    for (int i = size; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = v;
    size++;
}

template <class T>
void CircularDynamicArray<T>::delEnd()
{
    size--;
    if (size < (capacityInt / 4))
    {
        T *temp = new T[capacityInt / 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
        capacityInt = capacityInt / 2;
    }
}

template <class T>
void CircularDynamicArray<T>::delFront()
{
    for (int i = 0; i < size; i++)
        {
            array[i] = array[i + 1];
        }
        size--;
        if (size < (capacityInt / 4))
        {
            T *temp = new T[capacityInt / 2];
            for (int i = 0; i < size; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacityInt = capacityInt / 2;
        }

}



template <class T>
int CircularDynamicArray<T>::length()
{
    return size;
}

template <class T>
int CircularDynamicArray<T>::capacity()
{
    return capacityInt;
}

template <class T>
void CircularDynamicArray<T>::clear()
{
    delete[] array;
    this->capacityInt = 2;
    this->size = 0;
    this->front = 0;
    this->back = 0;
    this->array = new T[capacityInt];
}

template <class T> 
T CircularDynamicArray<T>::QuickSelect(int k)
{

    int pivot = rand() % size;
    T pivotValue = array[pivot];
    int left = 0;
    int right = size - 1;
    int i = 0;
    int j = size - 1;
    while (i <= j) {
        while (array[i] < pivotValue) {
            i++;
        }
        while (array[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            T temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (k <= j) {
        return QuickSelect(k);
    }
    else if (k >= i) {
        return QuickSelect(k);
    }
    else {
        return array[k] - 1;
    }
}


template <class T>
void CircularDynamicArray<T>::stableSort()
{
    for (int i=0; i<size; i++) {
        for (int j=0; j<size-1; j++) {
            if (array[j] > array[j+1]) {
                T temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

template <class T>
int CircularDynamicArray<T>::linearSearch(T v) 
{

    for (int i=0; i<size; i++) {
        if (array[i] == v) {
            return i;
        }
    }
    return -1;
}

template <class T>
int CircularDynamicArray<T>::binSearch(T v)
{

    //binary search of the array looing for the item 2. return the index of the item if found or -1 if not found.
    int low = 0;
    int high = size - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (array[mid] == v) {
            return mid;
        }
        else if (array[mid] < v) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;

}

template <class T>
void CircularDynamicArray<T>::reverse()
{
    T temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}