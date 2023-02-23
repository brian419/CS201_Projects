#include <iostream>
#include <string>

using namespace std;

template <class T>
class CircularDynamicArray //this is the class for the circular dynamic array
{
    private: //these are private variables that are used in the class
        T *array;
        int size;
        int front;
        int back;
        int capacityInt;
        bool isReversed;
        bool originalCall;
    public: //these are the public functions that are used in the class
        CircularDynamicArray() { //Default constructor. Capacity of 2 and size of 0. 
            this->capacityInt = 2;
            this->size = 0;
            this->front =0;
            this->back = 0;
            this->array = new T[capacityInt];
            this->isReversed = false; //Sets isReversed flag to false as an initializer. 
            this->originalCall = true; //Sets originalCall flag to true as an initializer. This will be used to make sure when calling if (isReversed), I don't 
            //run into an ifinite loop because I will be calling the opposite functions. ex. if (isReversed) {addFront} will call addEnd. If I don't have this originalCall flag,
            //it will call addFront again and again, etc. 
        }
        CircularDynamicArray(int s) { //Constructor for an int s. Sets capacity to s, size to s. 
            this->capacityInt = s;
            this->size = s;
            this->front = 0;
            this->back = 0;
            this->array = new T[capacityInt];
            //set isReversed to 0
            this->isReversed = false;
            this->originalCall = true;
        }
        CircularDynamicArray(const CircularDynamicArray<T> &otherArray) { //Copy constructor.
            this->capacityInt = otherArray.capacityInt;
            this->size = otherArray.size;
            this->front = front;
            this->back = back;
            this->originalCall = true;
            this->array = new T[capacityInt];
            for (int i = 0; i < size; i++)
            {
                array[i] = otherArray.array[i]; //Copies one array into the other.
            }
            
            
        }
        CircularDynamicArray<T>& operator=(const CircularDynamicArray<T> &otherArrayB) { //Assignment operator.
            if (this != &otherArrayB)
            {
                delete[] array;
                this->capacityInt = otherArrayB.capacityInt;
                this->size = otherArrayB.size;
                this->front = front;
                this->back = back;
                this->originalCall = true;
                this->array = new T[capacityInt];
                
                for (int i = 0; i < size; i++)
                {
                    array[i] = otherArrayB.array[i]; //Copies one array into the other.
                }
            }
            return *this;
        }
        ~CircularDynamicArray() { //Destructor.
            delete[] array; 
        }
        T& operator[](int i) { // Elmtype& operator[](int i); 
            if (i < 0 || i >= size) {
                cout << "Error: Index out of bounds" << endl; //prints a message if i is out of bounds        
                T *referenceValue = new T;
                return *referenceValue;
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
            if (isReversed) { //This checks if the array is reversed. If it is, it will call addFront instead of addEnd.
                originalCall = false; //This is needed so that we don't get a loop. 
                addFront(v); //This calls addFront instead of addEnd.
                originalCall = true; //Set originaCall back to true for next time.
                return; 
            }
            if (size == capacityInt) {  //This checks if the new element can't fit and doubles the capacity. 
                T *temp = new T[capacityInt * 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt * 2;
            }
            array[size] = v; //This will add the input v to the end of the array.
            back = (back + 1) % capacityInt;  //This is so we can keep track of the udpated back value
            size++;
            
        }
        void addFront(T v) {
            if (isReversed && originalCall) { //This checks if the array is reversed. If it is, it will call addEnd instead of addFront.
                originalCall = false; 
                addEnd(v);
                originalCall = true;
                return;
            }
            if (size == capacityInt) { //This checks if the new element can't fit and doubles the capacity.
                T *temp = new T[capacityInt * 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt * 2;
            }
            for (int i = size; i > 0; i--) { //This will shift all the elements in the array to the right by 1 because we are adding to the front.
                array[i] = array[i - 1];
            }
            array[0] = v; //This will add the input v to the front of the array.
            front = (front + 1) % capacityInt; //This is so we can keep track of the updated front value
            size++;  
        }
        void delEnd() {
            if (isReversed && originalCall) { //This checks if the array is reversed. If it is, it will call delFront instead of delEnd.
                originalCall = false;
                delFront(); 
                originalCall = true;
                return;
            }
            if (size < capacityInt / 4) { //This checks if the array is 25% of the array is in use after the delete. If it is, it will halve the capacity.
                T *temp = new T[capacityInt / 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i]; 
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt / 2;
            }
            back = (back - 1) % capacityInt; //This is so we can keep track of the updated back value 
            size--; 
        }
        void delFront() {
            if (isReversed && originalCall) { //This checks if the array is reversed. If it is, it will call delEnd instead of delFront.
                originalCall = false;
                delEnd();
                originalCall = true;
                return;
            }
            if (size < capacityInt / 4) { //This checks if the array is 25% of the array is in use after the delete. If it is, it will halve the capacity.
                T *temp = new T[capacityInt / 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = array[i];
                }
                delete[] array;
                array = temp;
                capacityInt = capacityInt / 2;
            }
            for (int i = 0; i < size; i++) { //This will shift all the elements in the array to the left by 1 because we are deleting from the front.
                array[i] = array[i + 1];
            }
            front = (front + 1) % capacityInt; //This is so we can keep track of the updated front value
            size--;
        }

        int length() { 
            return size; 
        }
        int capacity() {
            return capacityInt;
        }
        void clear() { //This clears the array by deleting the array. It also resets everything. 
            delete[] array;
            this->capacityInt = 2;
            this->size = 0;
            this->front = 0;
            this->back = 0;
            this->array = new T[capacityInt]; //This will create a new array, and this->capacityInt makes the capacity of the new array set to 2 again.
        }
        T QuickSelect(int k) { 

            int low = 0;
            int high = size - 1;

            // Loop until the array is partitioned around the kth smallest element
            while (low <= high) {
                //choose a random pivot element based on the size of the array
                int pivotIndex = rand() % size;
                
                T pivot = array[pivotIndex];

                // Partition the array around the pivot
                int i = low;
                int j = high;
                while (i <= j) {
                    while (array[i] < pivot) {
                        i++;
                    }
                    while (array[j] > pivot) {
                        j--;
                    }
                    if (i <= j) {
                        swap(array[i], array[j]);
                        i++;
                        j--;
                    }
                }
                return i;

        // If k is within the left partition, continue searching there
        // if (k < j) {
        //     high = j;
        // }
        // // If k is within the right partition, continue searching there
        // else if (k > i) {
        //     low = i;
        // }
        // // If the kth smallest element is found, return it
        // else {
        //     return array[k];
        // }

        if (low == high) {
            return array[low];
        }
        if (k < j) {
            high = j;
        }
        else if (k > i) {
            low = i;
        }
        else {
            return array[k];
        }

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
            for (int i = 0; i < size; i++) //Searches through the array
            {
                if (array[i] == v) //If statement checks when the value of v is found in the array
                {
                    return i; //returns the index of the value of v when found
                }
            }
            return -1;  //if not found, it returns -1
        }
        int binSearch(T v) {
            int left = 0; //first element of the array
            int right = size - 1; //last element of the array
            while (left <= right) //While we aren't at the end of the array
            { 
                int mid = (left + right) / 2; 
                if (array[mid] == v) //if the middle of the array is v, we just return where the middle is
                {
                    return mid;
                }
                else if (array[mid] < v) //if the middle of the array is less than v, we move the left to the middle + 1
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1; //if the middle of the array is greater than v, we move the right to the middle - 1
                }
            }
            return -1; //if not found, it returns -1
        }
        void reverse() {

            if (isReversed == false) { //isReversed checks if the array has been reversed. If it hasn't, we set the flag to true because reverse() calls and the array would have reversed. And vice versa. 
                isReversed = true;
            }
            else {
                isReversed = false;
            }
        }
};

