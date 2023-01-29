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

//create a foo function 


template <class T>
CircularDynamicArray<T>::CircularDynamicArray()
{
    capacityInt = 2;
    size = 0;
    front = 0;
    back = 0;
    array = new T[capacityInt];
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s)
{
    capacityInt = s;
    size = s;
    front = 0;
    back = 0;
    array = new T[capacityInt];
    
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray()
{
    delete[] array;
}

template <class T>
T& CircularDynamicArray<T>::operator[](int i)
{
    if (i < 0 || i >= size)
    {
        cout << "Index out of bounds" << endl;
    }
    else
    {
        return array[i];
    }
}

template <class T>
void CircularDynamicArray<T>::addEnd(T v)
{
    //add the element to the end of the array.
    for (int i = 0; i < size; i++)
    {
        //array[i] = array[i + 1];
    }
    array[size] = v;
    size++;
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



}

//add a addFront fucntion that stores the input v at the beginning of the array and increases the size of the array by 1. Should double capactiy when the new element doesn't fit.
template <class T>
void CircularDynamicArray<T>::addFront(T v)
{
    for (int i = size; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = v;
    size++;
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
}

//the delEnd() function should shrink the capacity when only 25% of the array is being used
template <class T>
void CircularDynamicArray<T>::delEnd()
//use a for loop to iterate to the back of the array and delete the last element. Also update the size.
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

//implement the int capacity function
template <class T>
int CircularDynamicArray<T>::capacity()
{
    return capacityInt;
}

template <class T>
void CircularDynamicArray<T>::clear()
{
    size = 0;
    front = 0;
    back = 0;
}

template <class T>
T CircularDynamicArray<T>::QuickSelect(int k)
{
    if (k < 0 || k >= size)
    {
        cout << "Index out of bounds" << endl;
    }
    else
    {
        int left = 0;
        int right = size - 1;
        while (left <= right)
        {
            int pivot = array[left];
            int i = left + 1;
            int j = right;
            while (i <= j)
            {
                while (i <= j && array[i] <= pivot)
                {
                    i++;
                }
                while (i <= j && array[j] > pivot)
                {
                    j--;
                }
                if (i < j)
                {
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
            T temp = array[left];
            array[left] = array[j];
            array[j] = temp;
            if (j == k)
            {
                return array[j];
            }
            else if (j < k)
            {
                left = j + 1;
            }
            else
            {
                right = j - 1;
            }
        }
    }
}


template <class T>
T CircularDynamicArray<T>::WCSelect(int k) //bad, it fails the phase1main test
{
    if (k < 0 || k >= size)
    {
        cout << "Index out of bounds" << endl;
    }
    else
    {
        int left = 0;
        int right = size - 1;
        while (left <= right)
        {
            int pivot = array[left];
            int i = left + 1;
            int j = right;
            while (i <= j)
            {
                while (i <= j && array[i] >= pivot)
                {
                    i++;
                }
                while (i <= j && array[j] < pivot)
                {
                    j--;
                }
                if (i < j)
                {
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
            T temp = array[left];
            array[left] = array[j];
            array[j] = temp;
            if (j == k)
            {
                return array[j];
            }
            else if (j < k)
            {
                left = j + 1;
            }
            else
            {
                right = j - 1;
            }
        }
    }
}


template <class T>
void CircularDynamicArray<T>::stableSort()
{
    int i, j, k;
    for (i = 1; i < size; i++)
    {
        T temp = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > temp)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

template <class T>

int CircularDynamicArray<T>::linearSearch(T v) //bad, it fails the phase1main test
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == v)
        {
            return i;
        }
    }
    return -1;
}

template <class T>
int CircularDynamicArray<T>::binSearch(T v)
{
    int left = 0;
    int right = size - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (array[mid] == v)
        {
            return mid;
        }
        else if (array[mid] < v)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

template <class T>
void CircularDynamicArray<T>::reverse()
{
    int i = 0;
    int j = size - 1;
    while (i < j)
    {
        T temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
}