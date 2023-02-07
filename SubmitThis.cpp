#include <iostream>
#include <string>

using namespace std;

//initizlie / create a template class of T that I can use for any data type.
//this class CircularDynamicArray will be a circular dynamic array.
template <class T>
class CircularDynamicArray
{
    private:
        
        T *array; //this is the pointer to an array of type T
        int size; //this is the size of the array
        int front; //this is the front of the array
        int back; //this is the back of the array
        int capacityInt; //this is the capacity of the array

    public: 

        CircularDynamicArray(); //this is the default constructor
        CircularDynamicArray(int s); //this is the constructor that takes in an int
        CircularDynamicArray(const CircularDynamicArray<T> &other); //this is the copy constructor
        CircularDynamicArray<T>& operator=(const CircularDynamicArray<T> &other); //this is the assignment operator
        ~CircularDynamicArray(); //this is the destructor
        T& operator[](int i); //this is the overloaded [] operator that returns the value at the index
        void addEnd(T v); //this is the addEnd function that adds to the end of the array
        void addFront(T v); //this is the addFront function that adds to the front of the array
        void delEnd(); //this is the delEnd function that deletes the end of the array
        void delFront(); //this is the delFront function that deletes the front of the array
        int length(); //this is the length function that returns the size of the array
        int capacity(); //this is the capacity function that returns the capacity of the array
        void clear(); //this is the clear function that clears the array
        T QuickSelect(int k); //this is the QuickSelect function that returns the kth smallest element
        void stableSort(); //this is the stableSort function that sorts the array
        int linearSearch(T e); //this is the linearSearch function that returns the index of the element
        int binSearch(T e); //this is the binSearch function that returns the index of the element
        void reverse(); //this is the reverse function that reverses the array
        


};

template <class T> //this is the default constructor
CircularDynamicArray<T>::CircularDynamicArray()
{
    this->capacityInt = 2; //this is the capacity of the array set to 2
    this->size = 0; //this is the size of the array set to 0
    this->back = 0; //this is the back of the array set to 0
    this->array = new T[capacityInt]; //this is the array of type T set to a new array of type T with a capacity of 2
}

template <class T> //this is the constructor that takes in an int s
CircularDynamicArray<T>::CircularDynamicArray(int s)
{
    this->capacityInt = s; //this is the capacity of the array set to s
    this->size = s; //this is the size of the array set to s 
    this->front = 0; //this is the front of the array set to 0
    this->back = 0; //this is the back of the array set to 0
    this->array = new T[capacityInt]; //this is the array of type T set to a new array of type T with a capacity of s
}

template <class T> //this is the copy constructor
CircularDynamicArray<T>::CircularDynamicArray(const CircularDynamicArray<T> &other)
{
    this->capacityInt = other.capacityInt; //this is the capacity of the array set to the capacity of the other array
    this->size = other.size; //this is the size of the array set to the size of the other array
    this->front = other.front; //this is the front of the array set to the front of the other array
    this->back = other.back; //this is the back of the array set to the back of the other array
    this->array = new T[capacityInt]; //this is the array of type T set to a new array of type T with a capacity of the other array
    for (int i = 0; i < size; i++) //this is a for loop that goes through the array
    {
        array[i] = other.array[i]; //this is the array at index i set to the other array at index i
    }


}

template <class T>
CircularDynamicArray<T>& CircularDynamicArray<T>::operator=(const CircularDynamicArray<T> &other)
{

    if (this != &other) //this is if the array is not equal to the other array
    {
        delete[] array; //this is the array deleted
        this->capacityInt = other.capacityInt; //this is the capacity of the array set to the capacity of the other array
        this->size = other.size; //this is the size of the array set to the size of the other array
        this->front = other.front; //this is the front of the array set to the front of the other array
        this->back = other.back; //this is the back of the array set to the back of the other array
        this->array = new T[capacityInt]; //this is the array of type T set to a new array of type T with a capacity of the other array
        for (int i = 0; i < size; i++) //this is a for loop that goes through the array
        {
            array[i] = other.array[i]; //this is the array at index i set to the other array at index i
        }
    }
    return *this; //this is the array returned
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray() //this is the destructor
{
    delete[] array; //this is the array deleted
}

template <class T>
T& CircularDynamicArray<T>::operator[](int i) //this is the overloaded [] operator that returns the value at the index
{
    if (i < 0 || i > size) //this is if the index is less than 0 or greater than the size
    {
        cout << "Index out of bounds" << endl; //this is an error message when the index is out of bounds
    }
    return array[i]; //this is the array at index i returned

}

template <class T>
void CircularDynamicArray<T>::addEnd(T v) //this is the addEnd function that adds to the end of the array
{
    if (size == capacityInt) //this is if the size is equal to the capacity
    {
        T *temp = new T[capacityInt * 2]; //this is a new array of type T with a capacity of the capacity times 2
        for (int i = 0; i < size; i++) //this for loop goes through the array and sets the temp array to the array
        {
            temp[i] = array[i];
        }
        delete[] array; //this is the array deleted
        array = temp; //this is the array set to the temp array
        capacityInt = capacityInt * 2; //this is the capacity set to the capacity times 2 when the array is full
    }
    array[size] = v; //this is the array at the size set to v
    size++; //this is the size incremented
}

template <class T>
void CircularDynamicArray<T>::addFront(T v) //this is the addFront function that adds to the front of the array
{
    if (size == capacityInt) //this is if the size is equal to the capacity
    {
        T *temp = new T[capacityInt * 2]; //this is a new array of type T with a capacity of the capacity times 2
        for (int i = 0; i < size; i++) //this for loop goes through the array and sets the temp array to the array
        {
            temp[i] = array[i]; //this is the temp array at index i set to the array at index i
        }
        delete[] array; //this is the array deleted
        array = temp; //this is the array set to the temp array
        capacityInt = capacityInt * 2; //this is the capacity set to the capacity times 2 when the array is full
    }
    for (int i = size; i > 0; i--) //this is a for loop that goes through the array backwards
    {
        array[i] = array[i - 1]; //this is the array at index i set to the array at index i minus 1
    }
    array[0] = v; //this is the array at index 0 set to v
    size++; //this is the size incremented
}

template <class T>
void CircularDynamicArray<T>::delEnd() //this is the delEnd function that deletes from the end of the array
{
    size--; //this is the size decremented
    if (size < (capacityInt / 4)) //this if statement checks if the size is less than the capacity divided by 4
    {
        T *temp = new T[capacityInt / 2]; //this is a new array of type T with a capacity of the capacity divided by 2
        for (int i = 0; i < size; i++) //this for loop goes through the array and sets the temp array to the array
        {
            temp[i] = array[i]; //this is the temp array at index i set to the array at index i
        }
        delete[] array; //this is the array deleted
        array = temp; //this is the array set to the temp array
        capacityInt = capacityInt / 2; //this is the capacity set to the capacity divided by 2 when the array is full
    }
}

template <class T>
void CircularDynamicArray<T>::delFront() //this is the delFront function that deletes from the front of the array
{
    for (int i = 0; i < size; i++) //this is a for loop that goes through the array
        {
            array[i] = array[i + 1]; //this is the array at index i set to the array at index i plus 1
        }
        size--; //this is the size decremented
        if (size < (capacityInt / 4)) //this if statement checks if the size is less than the capacity divided by 4
        {
            T *temp = new T[capacityInt / 2]; //this is a new array of type T with a capacity of the capacity divided by 2
            for (int i = 0; i < size; i++) //this for loop goes through the array and sets the temp array to the array
            {
                temp[i] = array[i]; //this is the temp array at index i set to the array at index i
            }
            delete[] array; //this is the array deleted
            array = temp; //this is the array set to the temp array
            capacityInt = capacityInt / 2; //this is the capacity set to the capacity divided by 2 when the array is full
        }

}



template <class T>
int CircularDynamicArray<T>::length() //this is the length function that returns the size
{
    return size;
}

template <class T>
int CircularDynamicArray<T>::capacity() //this is the capacity function that returns the capacity
{
    return capacityInt;
}

template <class T>
void CircularDynamicArray<T>::clear() //this is the clear function that clears the array
{
    delete[] array; //this is to delete the array
    this->capacityInt = 2; // this sets the capacity of the array to 2
    this->size = 0; //this sets the size of the array to 0
    this->front = 0; //this sets the front of the array to 0
    this->back = 0; //this sets the back of the array to 0
    this->array = new T[capacityInt]; //this is a new array of type T with a capacity of 2
}

template <class T> 
T CircularDynamicArray<T>::QuickSelect(int k) //this is the QuickSelect function that returns the kth smallest element
{

    i// //int pivot = rand() % size;
            // //T pivotValue = array[pivot];


            // T pivotValue = array[size / 2];

            // int left = 0;
            // int right = size - 1;
            // int i = 0;
            // int j = size - 1;
            // while (i <= j) {
            //     while (array[i] < pivotValue) {
            //         i++;
            //     }
            //     while (array[j] > pivotValue) {
            //         j--;
            //     }
            //     if (i <= j) {
            //         T temp = array[i];
            //         array[i] = array[j];
            //         array[j] = temp;
            //         i++;
            //         j--;
            //     }
            // }
            // if (k <= j) {
            //     return QuickSelect(k);
            // }
            // else if (k >= i) {
            //     return QuickSelect(k);
            // }
            // else {
            //     return array[k]-1;
            // }
}


template <class T>
void CircularDynamicArray<T>::stableSort() //this is the stableSort function that sorts the array
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
int CircularDynamicArray<T>::linearSearch(T v)  //this is the linearSearch function that returns the index of the value or -1 if not found
{

    for (int i=0; i<size; i++) {
        if (array[i] == v) {
            return i;
        }
    }
    return -1;
}

template <class T>
int CircularDynamicArray<T>::binSearch(T v) //this is the binSearch function that returns the index of the value or -1 if not found
{
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
void CircularDynamicArray<T>::reverse() //this is the reverse function that reverses the array
{
    T temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}