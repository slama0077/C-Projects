#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

//this program finds the common data set between two files and sorts them in O(nlgn). Some optimization techniques have been implementded.


class stringSort {
    public: 
    string data;

};


stringSort* fillRepeatedArray2(string repeatedArrayS, int&num) {
    istringstream RA(repeatedArrayS);
    istringstream RA2(repeatedArrayS);
    stringSort* PRA = NULL;
    string temp;
    while (RA >> temp) {
        num++;
    }
    PRA = new stringSort[num];
    for(int i = 0; i < num; i++) {
        RA2 >> temp;
        (PRA + i) -> data = temp;
    }
    return PRA;
}



void binarySearch(string temp, stringSort *PA, int lowVal, int highVal, ostringstream& RA) {
    int midVal = (lowVal + highVal)/2;
    if((PA + midVal)->data == temp) {
        RA << temp << endl;
    }
    else if(lowVal == highVal) {

    }
    else {
        if (temp > (PA + midVal)->data) {
            binarySearch(temp, PA, midVal + 1, highVal, RA);
        }
        else {
            binarySearch(temp, PA, lowVal, midVal, RA);
        }
    }
}


void repeatedString(string stringArray, stringSort* PA, int numC, string &repeatedArrayS) {
    istringstream SA(stringArray);
    ostringstream RA;
    string temp;
    while(SA >> temp) {
        binarySearch(temp, PA, 0, numC, RA);
    }
    repeatedArrayS = RA.str();
}


int Partition(stringSort* array, int i, int k) {
    int l;
    int h;
    int midpoint;
    string pivot;
    string temp;
    bool done;
    midpoint = i + (k-i)/2;
    pivot = (array + midpoint) -> data;
    done = false;
    l = i;
    h = k;
    while (!done) {
        while (((array + l)->data) < pivot) {
            l++;
        }
        while (pivot < ((array + h) -> data)) {
            h--;
        }
        if(l >= h) {
            done = true;
        }
        else {
            temp = (array + l) -> data;
            (array + l) -> data = (array + h) -> data;
            (array + h) -> data = temp;
            l++;
            h--;
        }
    }
    return h;
}


void QuickSort(stringSort* array, int i, int k) {
    int j;
    if(i >= k) {
        return;
    }
    j = Partition(array, i, k);
    QuickSort(array, i, j);
    QuickSort(array, j+1, k);
}



stringSort* fileRead3(ifstream & ifSS1, int &num, ifstream& ifSS1x) {
    stringSort* pA = NULL;
    string temp;
    while(ifSS1 >> temp) {
        num = num + 1;
    }
    pA = new stringSort[num];
    for(int i = 0; i < num; i++) {
        ifSS1x >> temp;
        (pA+i)->data = temp;
    }
    return pA;
}



void fileRead4(istream &ifSS2, string &stringArray) {
    ostringstream SA;
    string temp;
    while(ifSS2 >> temp) {
        SA << temp << endl;
    }
    stringArray = SA.str();
}


int* fileRead1(ifstream &ifSS1, int &num, ifstream &ifSS1x) {
    int *pA = NULL;
    int temp;

    while(ifSS1 >> temp) {  //reading data drom the file to create exact memory for the array
        num = num + 1;
    }

    pA = new int[num];

    for(int i = 0; i < num; i++) { //add data in the pointerArrayt
        ifSS1x >> temp;
        *(pA + i) = temp;
    }

    return pA;
}


void fileRead2(istream &ifSS2, string &integerArray) { //creates an array that has data from file 2
    ostringstream IA;
    int temp;
    while(ifSS2 >> temp) {
        IA << temp << endl;
    }
    integerArray = IA.str();
}


void Merge(int numbers[], int i, int j, int k) { 
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
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
void MergeSort(int numbers[], int i, int k) {
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


void binarySearch(int number, int *PA, int lowVal, int highVal, ostringstream &RA) { //applying binary search logn
    int midVal = (lowVal + highVal)/2;
    if(*(PA + midVal) == number) {
        RA << number << endl;
    }

    else if(lowVal == highVal) {
        return;
    }

    else {
        if (number > *(PA + midVal)) {
            binarySearch(number, PA, midVal + 1, highVal, RA);
        }
        else {
            binarySearch(number, PA, lowVal, midVal, RA);
        }
    }
}


void repeatedNumber(string integerArray, int* PA, int numC, string &repeatedArrayI) { //finding the common set using bainary search O(nlgn)
    istringstream IA(integerArray);
    ostringstream RA;
    int number;
    while (IA >> number) {
       binarySearch(number, PA, 0, numC, RA);
    }
    repeatedArrayI = RA.str(); //outputs the data in this string
}


int* fillRepeatedArray(string repeatedArrayI, int &num) {
    istringstream RA(repeatedArrayI);
    istringstream RA2(repeatedArrayI);
    int * PRA = NULL;
    int data;
    while(RA >> data) {
        num++;
    }
    PRA = new int[num];
    for(int i = 0; i < num; i++) {
        RA2 >> data;
        *(PRA + i) = data;
    }
    return PRA;

}



int main(int argc, char** argv) {
    ifstream ifSS1;
    ifstream ifSS2;

    if(argc != 4) {
        cout << "Incorrect usage of files" << endl;
    }
    ifSS1.open(*(argv + 2));
    ifSS2.open(*(argv + 3));

    if(!ifSS1.is_open()) {
        cout << "Couldn't open the first input file" << endl;
    }

    if(!ifSS2.is_open()) {
        cout << "Couldn't open the second input file" << endl;
    }


    string c = *(argv+1);


    if(c == "i") {
        ifstream ifSS1x;
        ifSS1x.open(*(argv+2));
        int *pointerArray = NULL;
        string integerArray;
        string repeatedArrayI;
        int numConstant = 0;
        int numRepeated= 0;
        int* repeatedArray = NULL;

        pointerArray = fileRead1(ifSS1, numConstant, ifSS1x);

        fileRead2(ifSS2, integerArray);

        MergeSort(pointerArray, 0, numConstant- 1); //sorts the pointer array to apply binary search later using mergesort

        repeatedNumber(integerArray, pointerArray, numConstant, repeatedArrayI);

        repeatedArray = fillRepeatedArray(repeatedArrayI, numRepeated);

        MergeSort(repeatedArray, 0, numRepeated -1); 

        /* sorts the repeated array again. there's a teddy bit optimmization in this.
        could've sorted the intial data from the another file and could have
        escaped this sorting again at the end. however, didn't do that and instead sorted the repeated data because sorting 
        sorting the repeated item, which is less, takes way less time than sorting the huge data set itself */

        for(int i = 0; i < numRepeated; i++) {
            if((i+1) == numRepeated) {
                cout << *(repeatedArray + i) << endl;
            }
            else {
                if(*(repeatedArray+i) == *(repeatedArray+ i +1)) {

                }
                else {
                cout << *(repeatedArray+i) << endl;
                }
            }
        }
        delete pointerArray;
        delete repeatedArray;
    }


    if (c == "s") {  //repeats the same thing again, however this time uses Quicksort instead of mergesort
        ifstream ifSS1x;
        ifSS1x.open(*(argv + 2));
        stringSort *pointerArray = NULL;
        string stringArray;
        string repeatedArrayS;
        int numConstant = 0;
        int numRepeated = 0;
        stringSort* repeatedArray = NULL;
        pointerArray = fileRead3(ifSS1, numConstant, ifSS1x);
        fileRead4(ifSS2, stringArray);
        QuickSort(pointerArray, 0, numConstant -1);
        repeatedString(stringArray, pointerArray, numConstant, repeatedArrayS);
        repeatedArray = fillRepeatedArray2(repeatedArrayS, numRepeated);
        QuickSort(repeatedArray, 0, numRepeated - 1);

        for(int i = 0; i < numRepeated; i++) {
            if((i+1) == numRepeated) {
                cout << (repeatedArray + i) -> data << endl;
            }
            else {
                if((repeatedArray + i) -> data == (repeatedArray + i + 1) -> data) {

                }
                else {
                    cout << (repeatedArray + i) -> data << endl;
                }
            }
        }
        
        delete[] pointerArray;
        delete[] repeatedArray;

        ifSS1.close();
        ifSS1x.close();
    }
    return 0;
}