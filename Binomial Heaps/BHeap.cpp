#include "CircularDynamicArray.cpp"

#include <iostream>
using namespace std;
template <typename myType>
class node{
    public:
    myType key;
    int rank;
    node* parent;
    CircularDynamicArray<node*> child;

    node() {
        rank = 0;
        parent = NULL;
        for(int i = 0; i < child.capacity(); i++) {
            child[i] = NULL; 
        }
    }
    node(myType key) {
        rank = 0;
        parent = NULL;
        this->key = key;
         for(int i = 0; i < child.capacity(); i++) {
            child[i] = NULL; 
        }
    }
    node(myType key, int rank) {
        this->rank = rank;
        parent = NULL;
        this->key = key;
         for(int i = 0; i < child.capacity(); i++) {
            child[i] = NULL; 
        }
    }
};

template <typename myType>
class treeRoot {
    public: 
    node<myType>* root;

    treeRoot() {
        root = NULL;
    }

};

template <typename myType>
class BHeap {
    private:
    CircularDynamicArray< treeRoot <myType> >* x;
    treeRoot<myType>* min;


    void preOrderTraversal(node<myType>* cur) {
        if(cur == NULL) {
            return;
        }

        cout << cur->key << " ";
        for(int i = 0; i < cur->child.length(); i++) {
            preOrderTraversal(cur->child[i]);
        }

    }

    void pseudoInsert(node<myType>* temp) {
        treeRoot<myType> cur;
        cur.root = temp;
        while(1) { 
            if(cur.root->rank > (x->capacity() - 1)) {
                while(1) {
                    if(x->capacity() > cur.root->rank) {
                        break;
                    }
                    x->resizeDouble();
                }
            }
            if((*x)[cur.root->rank].root == NULL) {
                (*x)[cur.root->rank] = cur;
                treeRoot<myType>* tempp = &((*x)[cur.root->rank]);
                if(min == NULL) {
                    min = tempp;
                }
                else if(tempp->root->key < min->root->key) {
                    min = tempp;
                }
                else {

                }
                break;
            }
            else {
                treeRoot<myType> y = (*x)[cur.root->rank];
                if(min == &((*x)[cur.root->rank])) {     //cause min is just pointing to an index in the CDA array, and it is goin to change no matter what
                    min = NULL;
                }
                (*x)[cur.root->rank].root = NULL;   
                if(y.root->key < cur.root->key) {
                    cur.root->parent = y.root;
                    y.root->child.addFront(cur.root);
                    y.root->rank++; 
                    cur = y;
                }
                else {
                    y.root->parent = cur.root;
                    cur.root->child.addFront(y.root);
                    cur.root->rank++;
                }

            }
            
        }
    }

    void clearAll(node<myType>* cur) {
        if(cur == NULL) {
            return;
        }
        for(int i = 0; i < cur->child.length(); i++) {
            clearAll(cur->child[i]);
        }
        delete cur;
    }

    void clear() {
        for(int i = 0; i < x->capacity(); i++) {
            if((*x)[i].root != NULL) {
                node<myType>* cur = (*x)[i].root;
                (*x)[i].root = NULL;
                clearAll(cur);
            }
        }
        delete x;
    }

    void spreOrderTraversal(node<myType>* curX, node<myType>* curY) {
        if(curY == NULL) {
            return;
        }
        for(int i = 0; i < curY->child.length(); i++) {
            node<myType>* temp = new node<myType>(curY->child[i]->key,curY->child[i]->rank);
            curX->child.addEnd(temp);
        }
        for(int i = 0; i < curY->child.length(); i++) {
            spreOrderTraversal(curX->child[i], curY->child[i]);
        }
    }

    public: 
    BHeap() {
        x = new CircularDynamicArray< treeRoot<myType> >();
        min = NULL;
    }


    BHeap(myType k[], int s) {
        x = new CircularDynamicArray< treeRoot<myType> >();
        min = NULL;
        for(int i = 0; i < s; i++) {
            insert(k[i]);
        }
    }

    ~BHeap() {
        clear();
    }

    BHeap& operator=(const BHeap& src){
        if(this != &src) {
            clear();
            x = new CircularDynamicArray< treeRoot<myType> >();
            min = NULL;
            CircularDynamicArray<treeRoot <myType> >* y = src.x;

            while(1) {
                if(x->capacity() == y->capacity()) {
                    break;
                }
                x->resizeDouble();
            }

            for(int i = 0; i < y->capacity(); i++) {
                if(src.min == &((*y)[i])) {
                    min = &((*x)[i]);
                }
                if((*y)[i].root != NULL) {
                    node<myType>* curY = (*y)[i].root;
                    node<myType>* curX = new node<myType>(curY->key, curY->rank);
                    (*x)[i].root = curX;
                    spreOrderTraversal(curX, curY);
                }
            }
        }
        return *this;
    }

    BHeap(const BHeap& src) {
            x = new CircularDynamicArray< treeRoot<myType> >();
            min = NULL;
            CircularDynamicArray<treeRoot <myType> >* y = src.x;

            while(1) {
                if(x->capacity() == y->capacity()) {
                    break;
                }
                x->resizeDouble();
            }

            for(int i = 0; i < y->capacity(); i++) {
                if(src.min == &((*y)[i])) {
                    min = &((*x)[i]);
                }
                if((*y)[i].root != NULL) {
                    node<myType>* curY = (*y)[i].root;
                    node<myType>* curX = new node<myType>(curY->key, curY->rank);
                    (*x)[i].root = curX;
                    spreOrderTraversal(curX, curY);
                }
            }
    }


    myType extractMin() {
        myType minimum = min->root->key;
        int indexMin = -1;
        myType pseudoMin;
        CircularDynamicArray< node<myType>* > *pseudoChild = &(min->root->child);
        // cout<< (*pseudoChild)[1]->key<< endl;
        node<myType>* temp = min->root;
        // delete(min->root);
        min->root = NULL;

        int j = 0;
        while(1) {
            if(j > (x->capacity()-1)) { 
                min = NULL;                         
                break;
            }
            else if((*x)[j].root != NULL) {
                pseudoMin = (*x)[j].root->key;
                break;
            }
            j++;
        }

        if(min != NULL) {
            for(int i = 0; i < x->capacity(); i++) {
                if((*x)[i].root == NULL) {

                }
                else {
                    if((*x)[i].root->key < pseudoMin || (*x)[i].root->key == pseudoMin) {
                        pseudoMin = (*x)[i].root->key;
                        indexMin = i;
                    }
                }
            }

            min = &((*x)[indexMin]);
        }

        for(int i = 0; i < pseudoChild->length(); i++) {
            pseudoInsert((*pseudoChild)[i]);
        }
        delete temp;
        return minimum;
    }


    void insert(myType k) {
        node<myType>* temp = new node<myType>(k);
        treeRoot<myType> cur;
        cur.root = temp;
        while(1) { 
            if(cur.root->rank > (x->capacity() - 1)) {
                while(1) {
                    if(x->capacity() > cur.root->rank) {
                        break;
                    }
                    x->resizeDouble();
                }
            }
            if((*x)[cur.root->rank].root == NULL) {
                (*x)[cur.root->rank] = cur;
                treeRoot<myType>* tempp = &((*x)[cur.root->rank]);
                if(min == NULL) {
                    min = tempp;
                }
                else if(tempp->root->key < min->root->key) {
                    min = tempp;
                }
                else {

                }
                break;
            }
            else {
                treeRoot<myType> y = (*x)[cur.root->rank];
                if(min == &((*x)[cur.root->rank])) {     //cause min is just pointing to an index in the CDA array, and it is goin to change no matter what
                    min = NULL;
                }
                (*x)[cur.root->rank].root = NULL;   
                if(y.root->key < cur.root->key) {
                    cur.root->parent = y.root;
                    y.root->child.addFront(cur.root);
                    y.root->rank++; 
                    cur = y;
                }
                else {
                    y.root->parent = cur.root;
                    cur.root->child.addFront(y.root);
                    cur.root->rank++;
                }

            }
            
        }
    }

    void merge (BHeap<myType> &H2) {
        CircularDynamicArray< treeRoot<myType> >* H = H2.x;
        for(int i = 0; i < H->capacity(); i++) {
            if((*H)[i].root != NULL) {
                pseudoInsert((*H)[i].root);
                (*H)[i].root = NULL;
            }
        }
    }


    myType peekKey() {
        return min->root->key;
    }

    void print() {  //remove
        for(int i = 0; i < x->capacity(); i++) {
            if((*x)[i].root == NULL) {

            }
            else {
                cout << (*x)[i].root->key << " ";
                cout << (*x)[i].root->rank << endl;
            }
        }
    }

    void printKey() {
        for (int i = 0; i < x->capacity(); i++) {
            if((*x)[i].root == NULL) {

            }
            else {
                node<myType>* cur = (*x)[i].root;
                cout << "B" << i << endl;
                preOrderTraversal(cur);
                cout<< endl << endl;
                
            }
        }
    }

};

