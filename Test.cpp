//This will be a test file to practice Circular Dynamic Arrays

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
        elmtype& operator[](int i);
        void addEnd(elmtype v);
        void addFront(elmtype v);
        void delEnd();
        void delFront();
        int length();
        int capacity();
        void clear();
        Elmtype QuickSelect(int k);
        Elmtype WCSelect(int k);
        void stableSort();
        int linearSearch(elmtype e);
        int binSearch(elmtype e);
        void reverse();

};

template <class T>
CircularDynamicArray<T>::CircularDynamicArray() //this is the default constructor
{
    capacity = 2;
    size = 0;
    front = 0;
    back = 0;
    array = new T[capacity];
}
{
    capacity = 2;
    size = 0;
    front = 0;
    back = 0;
    array = new T[capacity];
}


template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s) //this is the CircularDynamicArray(int s) constructor
{
    capacity = s;
    size = 0;
    front = 0;
    back = 0;
    array = new T[capacity];
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray() //this is the destructor
{
    delete [] array;
}

template <class T>
elmtype& CircularDynamicArray<T>::operator[](int i) //this is the operator function that prints a message if i is out of bounds and returns a reference to a 
                                                    //value of type elmtype stored in the class
{
    if (i < 0 || i >= size)
    {
        cout << "Error: Index out of bounds" << endl;
        return array[0];
    }
    else
    {
        return array[i];
    }
}

template <class T>
void CircularDynamicArray<T>::addEnd(elmtype v) //this is the addEnd function. It increases the size of the array by 1, stores v at the end of the array. 
                                                //If the array is full, it doubles the capacity of the array when the new element doesn't fit. 
{
    if (size == capacity)
    {
        T *temp = new T[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        delete [] array;
        array = temp;
        capacity *= 2;
    }
    array[size] = v;
    size++;
}

template <class T>
void CircularDynamicArray<T>::addFront(elmtype v) //this is the addFront function. it increases the size of the array by 1, stores v at the front of the array. 
                                                  //If the array is full, it doubles the capacity of the array when the new element doesn't fit. The new element 
                                                  //should be the item returned at index 0.
{
    if (size == capacity)
    {
        T *temp = new T[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        delete [] array;
        array = temp;
        capacity *= 2;
    }
    for (int i = size; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = v;
    size++;
}

template <class T>
void CircularDynamicArray<T>::delEnd() //this is the delEnd function. This reduces the size of the array by 1 at the end. Only shrinks the capacity
                                       //when 25% of the array is in use after deletion. 
{
    if (size == 0)
    {
        cout << "Error: Array is empty" << endl;
    }
    else
    {
        size--;
    }
}



template <class T>
void CircularDynamicArray<T>::delFront() //this is the delFront function. This reduces the size of the array by 1 at the front. Only shrinks the capacity
                                         //when 25% of the array is in use after deletion.
{
    if (size == 0)
    {
        cout << "Error: Array is empty" << endl;
    }
    else
    {
        for (int i = 0; i < size - 1; i++)
        {
            array[i] = array[i + 1];
        }
        size--;
    }
}

template <class T>
int CircularDynamicArray<T>::length() //this is the length function that returns the size of the array.
{
    return size;
}

template <class T>
int CircularDynamicArray<T>::capacity() //this is the capacity function that returns the capacity of the array.
{
    return capacity;
}

template <class T>
void CircularDynamicArray<T>::clear() //this is the clear function that frees any space currently used and starts over with an array capacity of 2 and size of 0.
{
    size = 0;
}

template <class T>
Elmtype CircularDynamicArray<T>::QuickSelect(int k) //this is the QuickSelect function that returns the kth smallest value in the array using the QuickSelect
                                                    //algorithm. It also chooses a random pivot element. 
    if (k < 0 || k >= size)
    {
        cout << "Error: Index out of bounds" << endl;
        return array[0];
    }
    else
    {
        int left = 0;
        int right = size - 1;
        while (left <= right)
        {
            int pivot = array[(left + right) / 2];
            int i = left;
            int j = right;
            while (i <= j)
            {
                while (array[i] < pivot)
                {
                    i++;
                }
                while (array[j] > pivot)
                {
                    j--;
                }
                if (i <= j)
                {
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    i++;
                    j--;
                }
            }
            if (left < j && k <= j)
            {
                right = j;
            }
            else if (i < right && k >= i)
            {
                left = i;
            }
            else
            {
                return array[k];
            }
        }
    }
}
{
    if (k < 0 || k >= size)
    {
        cout << "Error: Index out of bounds" << endl;
        return array[0];
    }
    else
    {
        return array[k];
    }
}

template <class T>
Elmtype CircularDynamicArray<T>::WCSelect(int k) //this is the WCSelect function that returns the kth smallest element in the array using the worst case 
                                                //O(N) algorithm.
{
    if (k < 0 || k >= size)
    {
        cout << "Error: Index out of bounds" << endl;
        return array[0];
    }
    else
    {
        return array[k];
    }
}

template <class T>
void CircularDynamicArray<T>::stableSort() //this is the stableSort function that sorts the values in the array using a comparison based on 
                                           //O(N lg N) algorithm. The sort is stable. 
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                T temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

template <class T>
int CircularDynamicArray<T>::linearSearch(elmtype e) //this is the linearSearch function that performs a linear search of the array looking for the item e. It returns 
                                                     //the index of the item if found, or -1 is returned.
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == e)
        {
            return i;
        }
    }
    return -1;
}

template <class T>
int CircularDynamicArray<T>::binSearch(elmtype e) //this is the binSearch function that performs a binary search of the array looking for the item e. 
                                                  //It returns the index of the item if found, or -1 is returned. This method assumes that the array is in 
                                                  //increasing order. 
{
    int low = 0;
    int high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (array[mid] == e)
        {
            return mid;
        }
        else if (array[mid] < e)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}



template <class T> 
void CircularDynamicArray<T>::reverse() //This if the reverese function that reverses the order of the array in the user's view of the array. 
{
    T *temp = new T[size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = array[size - i - 1];
    }
    delete [] array;
    array = temp;
}