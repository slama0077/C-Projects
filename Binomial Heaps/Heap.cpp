#include "CircularDynamicArray.cpp"
#include <iostream>
using namespace std;
template <typename myType> 
class Heap {
    private: 
    CircularDynamicArray<myType>* x;

    myType findMin(myType l, myType r, int* check) {
        if(l < r) {
            return l;
        }
        else {
            *check = 1;
            return r;
        }
    }

    void perlocateDown(int q) {
        int size = x->length();

        while(1) {
            int check = 0;
            myType temp;
            if(2*q + 1 > size-1) {
                check = -1;
            }
            else if(2*q + 1 == size-1) {
                temp = (*x)[2*q+1];
            }
            else {
                temp = findMin((*x)[2*q+1], (*x)[2*q+2], &check);
            }

            if(temp > (*x)[q] || temp == (*x)[q] || check == -1) {
                break;
            }

            else {
                if(check == 0) {
                    temp = (*x)[q];
                    (*x)[q] = (*x)[2*q+1];
                    (*x)[2*q+1] = temp;
                    q = 2*q + 1;
                }

                else {
                    temp = (*x)[q];
                    (*x)[q] = (*x)[2*q+2];
                    (*x)[2*q+2] = temp;
                    q = 2*q + 2;
                }
            }
        }
    }

    void clear() {
    delete x;
    }

    public:
    Heap() {
        x = new CircularDynamicArray<myType>();
    }

    ~Heap() {
        clear();
    }

    Heap& operator=(const Heap& src){
        if(this != &src) {
            // clear();
            x = new CircularDynamicArray<myType>();
            CircularDynamicArray<myType>* y = src.x;
            for(int i = 0; i < y->length(); i++) {
                x->addEnd((*y)[i]);
            }
        }
        return *this;
    }

    Heap(const Heap& src) {
        x = new CircularDynamicArray<myType>;
        CircularDynamicArray<myType>* y = src.x;
        for(int i = 0; i < y->length(); i++) {
            x->addEnd((*y)[i]);
        }
    }


    Heap(myType k[], int s) {
        x = new CircularDynamicArray<myType>(s);
        for(int i = 0; i < s; i++) {
            (*x)[i] = k[i];
        }
        int q = x->length() - 1;
        if(q%2 == 1) {
            if((*x)[q] < (*x)[(q-1)/2]) {
                myType temp = (*x)[q];
                (*x)[q] = (*x)[(q-1)/2];
                (*x)[(q-1)/2] = temp;
                perlocateDown(q);                                       //not necessary, but can be used
            }
            q--;
        }
        while(1) {
            if(q == 0 || q < 0) {
                break;
            }
            if((*x)[q] < (*x)[q-1] && (*x)[q] < (*x)[(q-1)/2]) {
                myType temp = (*x)[q];                           
                (*x)[q] = (*x)[(q-1)/2];
                (*x)[(q-1)/2] = temp;
                perlocateDown(q);                                          //use the while loop of extract min.
            }

            else if((*x)[q-1] < (*x)[q] && (*x)[q-1] < (*x)[(q-2)/2]) {
                myType temp = (*x)[q-1];
                (*x)[q-1] = (*x)[(q-2)/2];
                (*x)[(q-2)/2] = temp;
                perlocateDown(q-1);
            }

            else {

            }
            q = q-2;
        }
    }

    
    void insert(myType k) {
        x->addEnd(k);
        int q = x->length() - 1;
        while(q > 0 && (*x)[q] < (*x)[(q-1)/2]) {
            myType temp = (*x)[q];
            (*x)[q] = (*x)[(q-1)/2];
            (*x)[(q-1)/2] = temp;
            q = (q-1)/2;
        }
    }

    myType extractMin() {
        int size = x->length();
        myType min = (*x)[0];
        (*x)[0] = (*x)[size-1];
        x->delEnd();
        size--;
        int q = 0;

        while(1) {
            int check = 0;
            myType temp;
            if(2*q + 1 > size-1) {
                check = -1;
            }
            else if(2*q + 1 == size-1) {
                temp = (*x)[2*q+1];
            }
            else {
                temp = findMin((*x)[2*q+1], (*x)[2*q+2], &check);
            }

            if(temp > (*x)[q] || temp == (*x)[q] || check == -1) {
                break;
            }

            else {
                if(check == 0) {
                    temp = (*x)[q];
                    (*x)[q] = (*x)[2*q+1];
                    (*x)[2*q+1] = temp;
                    q = 2*q + 1;
                }

                else {
                    temp = (*x)[q];
                    (*x)[q] = (*x)[2*q+2];
                    (*x)[2*q+2] = temp;
                    q = 2*q + 2;
                }
            }
        }
        return min;
    }

    myType peekKey() {
        return (*x)[0];
    }

    void printKey() {
        for(int i = 0; i < x->length(); i++) {
            cout << (*x)[i] << " ";
        }
        cout<<endl;
    }
};
