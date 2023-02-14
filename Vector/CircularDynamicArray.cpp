#include <iostream>
using namespace std;

template <typename myType>
class CircularDynamicArray {
    private: 
    int reversed;
    int cap;
    int size;
    int front;
    int end;
    myType error;
    myType* array;

    void resizeDouble() {
        myType* arrayb = array;
        cap = cap * 2;

        array = new myType[cap];
        for(int i = 0; i < size; i++) {
            *(array + i + 1) = *(arrayb + front);
            front = (front + 1) % size;
        }
        front = 1;
        end = size;
        delete[] arrayb;
    }
    
    void resize(myType* arrayA, myType* arrayB) {
        int f = front;
        for(int i = 0; i < size; i++) {
            *(arrayB + i) = *(arrayA + f);
            f = (f + 1) % cap;
        }
    }


    void resizeHalf() {
        myType* arrayb  = array;
        int c = cap;
        cap = cap/2;
        array = new myType[cap];

        for(int i = 0; i < size; i++) {
            *(array + i + 1) = *(arrayb + front);
            front = (front + 1) % c;
        }
        front = 1;
        end = size;
        delete[] arrayb;
    }


    void Merge(myType* numbers, int i, int j, int k) { 
        int mergedSize;                            // Size of merged partition
        int mergePos;                              // Position to insert merged number
        int leftPos;                               // Position of elements in left partition
        int rightPos;                              // Position of elements in right partition
        myType* mergedNumbers = NULL;

        mergePos = 0;
        mergedSize = k - i + 1;
        leftPos = i;                               // Initialize left partition position
        rightPos = j + 1;                          // Initialize right partition position
        mergedNumbers = new myType[mergedSize];       // Dynamically allocates temporary array
                                                // for merged numbers
    
        // Add smallest element from left or right partition to merged numbers
        while (leftPos <= j && rightPos <= k) {
            if (numbers[leftPos] < numbers[rightPos]) {
                mergedNumbers[mergePos] = numbers[leftPos];
                ++leftPos;
            }
            else {
                mergedNumbers[mergePos] = numbers[rightPos];
                ++rightPos;
            
            }
            ++mergePos;
        }
    
    // If left partition is not empty, add remaining elements to merged numbers
        while (leftPos <= j) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
            ++mergePos;
        }
    
    // If right partition is not empty, add remaining elements to merged numbers
        while (rightPos <= k) {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;
            ++mergePos;
        }
    
    // Copy merge number back to numbers
        for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
            numbers[i + mergePos] = mergedNumbers[mergePos];
        }
        delete[] mergedNumbers;
    }


    void MergeSort(myType* numbers, int i, int k) {
        int j;
    
        if (i < k) {
            j = (i + k) / 2;  // Find the midpoint in the partition
        
        // Recursively sort left and right partitions
            MergeSort(numbers, i, j);
            MergeSort(numbers, j + 1, k);
        
        // Merge left and right partition in sorted order
            Merge(numbers, i, j, k);
        }
    }

    int binarySearch(int l, int h, myType e) {
        int temph = h;
        if (l > h) {
            temph = h + cap;
        }
        int k = ((l + temph)/2) % cap;

        if(*(array + k) == e) {
            return k;
        }
        else if(l == h) {
            return -1;
        }
        else {
            if(e > *(array +  k)) {
                return binarySearch(k +1, h, e);
            }
            else {
                return binarySearch(l, k, e);
            }
        }

    }

    myType aQuickSelect(myType* arr, int k, int s) {
        int pivotindex = (s-1)/2;
        myType pivot = *(arr + pivotindex);
        myType* less = new myType[s];
        int sizeL = 0;
        myType* exact = new myType [s];
        int sizeE = 0;
        myType* great = new myType[s];
        int sizeG = 0;
        for(int i = 0; i < s; i++) {
            if(*(arr + i) < pivot) {
                *(less + sizeL) = *(arr + i);
                sizeL++;
            }
            else if(*(arr + i) == pivot) {
                *(exact + sizeE) = *(arr + i); 
                sizeE++;
            }
            else {
                *(great + sizeG) = *(arr + i);
                sizeG++;
            }
        }

        if(k <= sizeL) {
            return aQuickSelect(less, k, sizeL);
        }
        else if(k <= (sizeL + sizeE)) {
            return pivot;
        }
        else {
            return aQuickSelect(great, k-sizeL-sizeE, sizeG);
        }

    }

    // void print() {
    //     int temp2 = end;
    //     int temp = front;
    //     if(reversed == 1) {
    //         for(int i = 0; i < size; i++) {
    //             cout << *(array + temp) << endl;
    //             temp = (temp + 1) % cap;
    //         }
    //     }
    //     else {
    //         for(int i = 0; i < size; i++) {
    //             cout << *(array + temp2) << endl;
    //             temp2--;
    //             if(temp2 < 0) {
    //                 temp2 = temp2 + cap;
    //             }
    //         }
    //     }
    //     cout << "front: " <<front << endl;
    //     cout << "end: " << end << endl;
    // }


    public:
    CircularDynamicArray() {
        reversed = 1;
        cap = 2;
        size = 0;
        front = 0;
        end = 0;
        array = new myType[2];
    }

    CircularDynamicArray(int s) {
        reversed = 1;
        cap = s;
        size = s;
        front = 0;
        end = s - 1;
        array = new myType[s];
    }
    ~CircularDynamicArray() {
        delete[] array;
    }
    CircularDynamicArray& operator=(const CircularDynamicArray& src) {
        // cout << "In the copy assignment operator" << endl;
        if(this != &src) {
            delete[] array;
            size = src.size;
            cap = src.cap;
            error = src.error;
            front = src.front;
            end = src.end;
            reversed = src.reversed;
            int f = front;
            myType *arrayb = src.array;
            array = new myType[cap];
            for(int i = 0; i < size; i++) {
                *(array + f) = *(arrayb + f);
                f = (f + 1) % cap;
            }
        }
        return *this;
    }

    CircularDynamicArray(const CircularDynamicArray& src) {
        //    cout << "In the copy constructor" << endl;
           array = new myType[src.cap];
           size = src.size;
           cap = src.cap;
           front = src.front;
           end = src.end;
           error = src.error;
           reversed = src.reversed;
           myType *arrayb = src.array;
           int f = front;
            for(int i = 0; i < size; i++) {
                *(array + f) = *(arrayb + f);
                f = (f+1) % cap;
            }
    }

    myType& operator[](int i){

        if(i >= cap || i < 0) {
            cout << "Out of bounds reference: " << i << endl;
            return error;
        }
        if(reversed == 1) {
            i = (front+i) % cap;
        }
        if(reversed == -1) {
            i = end - i;
            if(i < 0) {
                i = i + cap;
            }
        }
        return *(array + i);
    }

    void addEnd (myType v) {
        if(reversed == -1) {
            reversed++;
            addFront(v);
        }
        else {
            if(size == 0) {
                *(array + end) = v;
                size++;
            }

            else if(size == cap) {
                // cout << "Doubling the size:" << endl; //
                resizeDouble();
                end = (end + 1) % cap;
                *(array + end) = v;
                size++;
            }
            else {
                end = (end+1) % cap;
                *(array + end) = v;
                size++;
            }
        }
        if(reversed == 0) {
            reversed--;
        }

    }

    void addFront (myType v) {
        if(reversed == -1) {
            reversed++;
            addEnd(v);
        }
        else {
            if(size == 0) {
                *(array + front) = v;
                size++;
            }

            else if(size == cap) {
                // cout << "Doubling the size:" << endl;
                resizeDouble();
                front = front - 1;
                *(array + front) = v;
                size++;
            }

            else {
                front--;
                if (front < 0) {
                    front = cap - 1;
                }
                *(array + front) = v;
                size++;
            }
        }
        if(reversed == 0) {
            reversed--;
        }

    }

    void delEnd() {
        if(reversed == -1) {
            reversed = 0;
            delFront();
        }
        else {
            if(size == 0) {
                if(reversed == 0) {
                    reversed--;
                }
                return;
            }

            else if(size == 1) {
                size--;
                end = front;
                if(reversed == 0) {
                    reversed--;
                }
                return;
            }
            else {
                end--;
                size--;
                if(end < 0) {
                    end = cap - 1;
                }
            }

            if(size ==  cap/4) {
                // cout << "Shrinking the size" << endl;
                resizeHalf();
            }
            if(reversed == 0) {
                reversed--;
            }
        }
    }

    void delFront() {
        if(reversed == -1) {
            reversed++;
            delEnd();
        }
        else {
            if(size == 0) {
                if(reversed == 0) {
                    reversed--;
                }
                return;
            }
            if(size == 1) {
                size--;
                front = end;
                if(reversed == 0) {
                    reversed--;
                }
                return;
            }
            else {
                front = (front + 1) % cap;
                size--;
            }

            if(size == cap/4) {
                // cout << "Shrinking the size" << endl;
                resizeHalf();
            }
            if(reversed == 0) {
                reversed--;
            }
        }
    }

    void stableSort() {
        reversed = 1;
        myType* arrayb = new myType[size];
        resize(array, arrayb);
        MergeSort(arrayb, 0, size-1);
        int f = front;
        for(int i = 0; i < size; i++) {
            *(array + f) = *(arrayb + i);
            f = (f + 1) % cap;
        }
        delete[] arrayb;
    }


    int binSearch(myType e) {
        int l = front;
        int h = end;
        int i = binarySearch(l,h, e);
        if(i == -1) {
            return i;
        }
        if(reversed == 1) {
            i = (i - front + cap) % cap;
        }
        else {
            i = (end - i + cap) % cap;
        }
        return i;

    }


    int linearSearch(myType e) {
        int f = front;
        for(int i = 0; i < size; i++) {
            if(*(array + f) == e) {
                if(reversed == 1) {
                    f = (f - front + cap) % cap;
                }
                else {
                    f = (end - f + cap) % cap;
                }
                return f;
            }
            f = (f+1) % cap;
        }
        return -1;
    }

    myType QuickSelect(int k) {
        if(k < 0 || k > size) {
            cout << "Reference outside of the scope" << endl;
            return error;
        }
        myType x;
        myType* arrayb = new myType[size];
        resize(array, arrayb);
        x = aQuickSelect(arrayb, k, size);
        return x;
        
    }
    void reverse() {
        reversed *=  -1;
    }

    void clear() {
        delete array;
        size = 0;
        cap = 2;
        front = 0;
        end = 0;
        array = new myType[cap];
    }


    int length() {
        return size;
    }
    
    int capacity() {
        return cap;
    }

};
