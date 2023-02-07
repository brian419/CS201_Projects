#include <iostream>
#include <string>
#include <random>
#include <new>

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
        bool isReversed;
        bool originalCall;
    public: 
        CircularDynamicArray() {
            this->capacityInt = 2;
            this->size = 0;
            this->front =0;
            this->back = 0;
            this->array = new T[capacityInt];
            //set isReversed to 0
            this->isReversed = false;
            this->originalCall = true;
        }
        CircularDynamicArray(int s) {
            this->capacityInt = s;
            this->size = s;
            this->front = 0;
            this->back = 0;
            this->array = new T[capacityInt];
            //set isReversed to 0
            this->isReversed = false;
            this->originalCall = true;
        }
        CircularDynamicArray(const CircularDynamicArray<T> &test) {
            this->capacityInt = test.capacityInt;
            this->size = test.size;
            this->front = front;
            this->back = back;
            this->originalCall = true;
            this->array = new T[capacityInt];
            for (int i = 0; i < size; i++)
            {
                array[i] = test.array[i];
            }
            
            
        }
        CircularDynamicArray<T>& operator=(const CircularDynamicArray<T> &other) {
            if (this != &other)
            {
                delete[] array;
                this->capacityInt = other.capacityInt;
                this->size = other.size;
                this->front = front;
                this->back = back;
                this->originalCall = true;
                this->array = new T[capacityInt];
                
                for (int i = 0; i < size; i++)
                {
                    array[i] = other.array[i];
                }
            }
            return *this;

        }
        ~CircularDynamicArray() {
            delete[] array;
        }
        T& operator[](int i) {
            if (i < 0 || i >= size) {
                cout << "Error: Index out of bounds" << endl;
                //return;
            }
            else {
                if (isReversed == false) {
                    return array[i];
                }
                else {
                    return array[size - i - 1]; //this returns the value at the index i from the end of the array
                }
            }
        }
        void addEnd(T v) {
            if (isReversed) {
                originalCall = false;
                addFront(v);
                originalCall = true;
                return;
            }
            if (size == capacityInt) { 
                T *temp = new T[capacityInt * 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt * 2;
            }
            array[size] = v;
            //back = array[size];
            back = (back + 1) % capacityInt;
            size++;
            

        }
        void addFront(T v) {
            if (isReversed && originalCall) {
                originalCall = false;
                addEnd(v);
                originalCall = true;
                return;
            }
            if (size == capacityInt) {
                T *temp = new T[capacityInt * 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt * 2;
            }
            for (int i = size; i > 0; i--) {
                array[i] = array[i - 1];
            }
            array[0] = v;
            //front = array[0];
            front = (front + 1) % capacityInt;
            size++;  
        
        }
        void delEnd() {
            if (isReversed && originalCall) {
                originalCall = false;
                delFront();
                originalCall = true;
                return;
            }
            if (size < capacityInt / 4) {
                T *temp = new T[capacityInt / 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt / 2;
            }
            //back = array[size - 1];   
            back = (back - 1) % capacityInt;  
            size--;

        
        }
        void delFront() {
            //delete from the front of the array
            if (isReversed && originalCall) {
                originalCall = false;
                delEnd();
                originalCall = true;
                return;
            }
            if (size < capacityInt / 4) {
                T *temp = new T[capacityInt / 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt / 2;
            }
            for (int i = 0; i < size; i++) {
                array[i] = array[i + 1];
            }
            //front = array[0];
            front = (front + 1) % capacityInt;
            size--;


        }

        int length() {
            return size;
        }
        int capacity() {
            return capacityInt;
        }
        void clear() {
            delete[] array;
            this->capacityInt = 2;
            this->size = 0;
            this->front = 0;
            this->back = 0;
            this->array = new T[capacityInt];
        }
        T QuickSelect(int k) {
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
                return array[k]-1;
            }
        }
        void stableSort() {
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
        int linearSearch(T v) {
            for (int i = 0; i < size; i++)
            {
                if (array[i] == v)
                {
                    return i;
                }
            }
            return -1; 
        }
        int binSearch(T v) {
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
        void reverse() {
            // int temp = front;
            // front = back;
            // back = temp;
            if (isReversed == false) {
                isReversed = true;
            }
            else {
                isReversed = false;
            }
        }
};

