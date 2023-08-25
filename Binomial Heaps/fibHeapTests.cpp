#include <iostream>
using namespace std;
// #include "CircularDynamicArray.cpp"
#include "Heap.cpp"
#include "BHeap.cpp"


// DO COPY CONSTRUCTOR AND COPY ASSIGNMENT OPERATOR
void test1();
void test2();
void test3();
// void test4();
// void test5();
// void test6();

int A[1000000];
void removeIndex(int removeIndex);
int main(int argc, char **argv)
{
    int testToRun = argc > 1 ? atoi(argv[1]) : -2;
    while (testToRun == -2)
    {
        cout <<"Enter a number 1,2, or 3" << endl;
        cin >> testToRun;
        switch (testToRun)
        {
        case 1:
            /* code */
        case 2:
        case 3:
            break;        
        default:
            testToRun = -2;
            break;
        }
    }
    
    switch (testToRun)
    {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    // case 4:
    //     test4();
    //     break;
    //     case 5:
    //     	test5();
    //     	break;
        // case 6:
        // 	test6();
        // 	break;
    }
    return 0;
}

// Testing default constructor, inserts, and remove
//  should finish in around 5 seconds or less
void test1()
{
    BHeap<int> Z;

    // should print nothing
    Z.printKey();

    for (int i = 0; i < 1000500; i++){
        Z.insert(1000500 - i);
    }
       

    // removes all but 10 elements
    for (int i = 0; i < 1000490; i++){
        Z.extractMin();
        // cout << "extract min: " << Z.extractMin() << endl;
    } 
        

    // should print
    // Rank 1
    // 1000491 1000492
    // Rank 3
    // 1000493 1000497 1000499 1000500 1000498 1000495 1000496 1000494
    // cout << "hi" << endl;
    Z.printKey();
    // cout << "bye" << endl;

    for (int i = 0; i < 9; i++){
        Z.extractMin();
        //Z.PrintBin();
    }

    // should print nothing
    // should print
    // Rank 0
    // 1000500
    Z.printKey();

    Z.extractMin();
    // should print nothing
    Z.printKey();
    return;
}

// testing non-default constructor and remove
// all output should be the same as test 1
// should finish in around 5 seconds or less
void test2()
{
    for (int i = 0; i < 1000500; i++)
        A[i] = 1000500 - i;

    // CircularDynamicArray<HeapNode<int> *> H1;
    BHeap<int> Z(A, 1000500);//, H1);

    for (int i = 0; i < 1000490; i++) // removes all but 10 elements
        Z.extractMin();

    // should print
    // Rank 1
    // 1000491 1000492
    // Rank 3
    // 1000493 1000497 1000499 1000500 1000498 1000495 1000496 1000494
    Z.printKey();

    for (int i = 0; i < 9; i++)
        Z.extractMin();

    // should print nothing
    // should print
    // Rank 0
    // 1000500
    Z.printKey();

    Z.extractMin();

    // should print nothing
    Z.printKey();
    return;
}

// testing merge and non-default constructor
// should finish in around 5 seconds or less
void test3()
{
    int Even[15];
    int Odd[15];
    int e = 0; // even's index
    int o = 0; // odd's index

    for (int i = 1; i <= 30; i++)
    {
        if (i % 2 == 0)
        {
            Even[e] = i;
            e++;
        }
    }
    for (int i = 1; i <= 30; i++)
    {
        if (i % 2 == 1)
        {
            Odd[o] = i;
            o++;
        }
    }

    // CircularDynamicArray<BHeapNode<int> *> H1;
    // CircularDynamicArray<BHeapNode<int> *> H2;
    BHeap<int> Z(Even, 15);//, H1);
    BHeap<int> Y(Odd, 15);//, H2);

    cout << "----Z's HEAP----" << endl;
    Z.printKey();
    // should output
    //----Z's HEAP----
    // Rank 0
    // 30

    // Rank 1
    // 26 28

    // Rank 2
    // 18 22 24 20

    // Rank 3
    // 2 10 14 16 12 6 8 4

    cout << "----Y's HEAP----" << endl;
    Y.printKey();
    // should output
    //----Y's HEAP----
    // Rank 0
    // 29

    // Rank 1
    // 25 27

    // Rank 2
    // 17 21 23 19

    // Rank 3
    // 1 9 13 15 11 5 7 3

    cout << "----MERGE----" << endl;
    Z.merge(Y);
    Z.printKey();

    // should output
    //----MERGE----

    // Rank 1
    // 29 30

    // Rank 2
    // 25 26 28 27

    // Rank 3
    // 17 18 22 24 20 21 23 19

    // Rank 4
    // 1 2 10 14 16 12 6 8 4 9 13 15 11 5 7 3

    for (int i = 0; i < 29; i++)
        Z.extractMin();
    cout << "----After extracts----" << endl;
    Z.printKey();
    //should output
    //----After extracts----
    // Rank 0
    // 30
    Z.extractMin(); // empty out heap


    Z.printKey();
    // should print nothing

    cout << "----Final Result----" << endl;
    for (int i = 0; i < 10; i ++) {
        Z.insert(i);
    }

    Z.extractMin();
    Z.printKey();

    //should output
    //----Final Result----
    // Rank 0
    // 1

    // Rank 3
    // 2 4 6 7 5 8 9 3

    return;
}