#include <iostream>
#include <string>
#include <random>

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
            this->isReversed = false; 
            this->originalCall = true; 
            
        }
        CircularDynamicArray(int s) {  
            this->capacityInt = s;
            this->size = s;
            this->front = 0;
            this->back = 0;
            this->array = new T[capacityInt];
            
            this->isReversed = false;
            this->originalCall = true;
        }
        CircularDynamicArray(const CircularDynamicArray<T> &otherArray) { 
            this->capacityInt = otherArray.capacityInt;
            this->size = otherArray.size;
            this->front = otherArray.front;
            this->back = otherArray.back;
            this->isReversed = otherArray.isReversed;
            this->originalCall = true;
            this->array = new T[capacityInt];
            for (int i = 0; i < size; i++)
            {
                array[i] = otherArray.array[i]; 
            }
            
            
        }
        CircularDynamicArray<T>& operator=(const CircularDynamicArray<T> &otherArrayB) { 
            if (this != &otherArrayB)
            {
                delete[] array;
                this->capacityInt = otherArrayB.capacityInt;
                this->size = otherArrayB.size;
                this->front = otherArrayB.front;
                this->back = otherArrayB.back;
                this->originalCall = true;
                this->isReversed = otherArrayB.isReversed;
                this->array = new T[capacityInt];
                
                for (int i = 0; i < capacityInt; i++)
                {
                    array[i] = otherArrayB.array[i]; 
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
                T *referenceValue = new T;
                return *referenceValue;
            }
            else {
                if (isReversed == false) {
                    return array[(front + i) % capacityInt];
                }
                else {
                    return array[(front + size - i - 1) % capacityInt]; 
                }
            }
        }
        void addEnd(T v) {
            if (isReversed  && originalCall) { 
                originalCall = false; 
                addFront(v); 
                originalCall = true; 
                return; 
            }
            if (size == capacityInt) { 
                T *temp = new T[capacityInt * 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[(front + i) % capacityInt];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt * 2;
                front = 0;
            }
            array[(front + size) % capacityInt] = v; 
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
                    temp[i + 1] = array[(front + i) % capacityInt];
                }
                delete[] array;
                front = 1;
                array = temp;
                capacityInt = capacityInt * 2;
            }
            
            front = (front - 1 + capacityInt) % capacityInt;
            array[front] = v;
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
                    temp[i] = array[(front + i) % capacityInt]; 
                }
                delete[] array;
                front = 0;
                back = size - 1;
                array = temp;
                capacityInt = capacityInt / 2;
            }
            back = (back - 1 + capacityInt) % capacityInt; 
            size--; 
        }
        void delFront() {
            if (isReversed && originalCall) {
                originalCall = false;
                delEnd();
                originalCall = true;
                return;
            }
            if (size < capacityInt / 4) { 
                T *temp = new T[capacityInt / 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[(front + i) % capacityInt]; 
                }
                delete[] array;
                front = 0;
                back = size - 1;
                array = temp;
                capacityInt = capacityInt / 2;
            }
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
        T QuickSelectHelper(T Arr[], int k, int sizeB) {
        

            int pivot = Arr[rand() % sizeB];

            T *L = new T[sizeB];
            T *E = new T[sizeB];
            T *G = new T[sizeB];

            int Lsize = 0;
            int Esize = 0;
            int Gsize = 0;

            for (int i=0; i < sizeB; i++) {
                if (Arr[i] < pivot) {
                    L[Lsize] = Arr[i];
                    Lsize++;
                } else if (Arr[i] == pivot) {
                    E[Esize] = Arr[i];
                    Esize++;
                } else if (Arr[i] > pivot) {
                    G[Gsize] = Arr[i];
                    Gsize++;
                }
            }

            if (k <= Lsize) {
                return QuickSelectHelper(L, k, Lsize);
            } else if (k <= (Lsize + Esize)) {
                return pivot;
            } else {
                return QuickSelectHelper(G, k-Lsize-Esize, Gsize);
            }
            
            
        }

        T QuickSelect(int k) { 
            T *newArray = new T[size];

            for (int i = 0; i < size; i++) {
                newArray[i] = array[(front + i)% capacityInt];
            }
            return QuickSelectHelper(newArray, k, size); 
            
        }

        void merge(T *Arr, int p, int q, int r) {
            int n1 = q - p + 1;
            int n2 = r - q ;

            T L[n1];
            T R[n2];
            for (int i=0; i < n1; i++) {
                L[i] = Arr[p + i];
            }
            for (int j=0; j < n2; j++){
                R[j] = Arr[q + j + 1];
            }
            
            int i = 0;
            int j = 0;
            int k;
            for (k = p; k <= r; k++) {
                if (i >= n1 || j >= n2) {
                    break;
                }
                if (L[i] <= R[j]) {
                    Arr[k] = L[i];
                    i = i + 1;
                } 
                else {
                    Arr[k] = R[j];
                    j = j+1;
                }
            }  
            if (i < n1) {
                for (int h = k; h <= r; h++) {
                    Arr[h] = L[i];
                    i = i + 1;
                }
            } else if (j < n2) {
                for (int h = k; h <= r; h++) {
                    Arr[h] = R[j];
                    j = j+1;
                }
            }
        }

        void mergeSort(T Arr[], int p, int r) {
            int q = (p + r) / 2;
            if (p >= r) {
                return;
            }
            mergeSort(Arr, p, q);
            mergeSort(Arr, q + 1, r);
            merge(Arr, p, q, r);
        }
        void stableSort() {
            T *newArray = new T[size];

            for (int i = 0; i < size; i++) {
                newArray[i] = array[(front + i)% capacityInt];

            }
            mergeSort(newArray, 0, size - 1);
            array = newArray;
            front = 0;
            isReversed = false;
            back = size - 1;

        }
        int linearSearch(T v) {
            for (int i = 0; i < size; i++) 
            {
                if (array[(front + i) % capacityInt] == v)
                {
                    return i; 
                }
            }
            return -1;  
        }

        int binSearchHelper(T Arr[], int l, int r, T v) {
            if (r >= l) {
                int m = l + (r - l) / 2;
                if (Arr[m] == v) {
                    return m;
                }
                if (Arr[m] > v) {
                    return binSearchHelper(Arr, l, m - 1, v);
                }
                return binSearchHelper(Arr, m + 1, r, v);
            }
            return -1;
            
        }

        int binSearch(T v) {

            return binSearchHelper(array, 0, size - 1, v);

        }

        void reverse() {

            if (isReversed == false) { 
                isReversed = true;
            }
            else {
                isReversed = false;
            }
        }
};
