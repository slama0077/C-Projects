#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

void fileRead (istream &ifSS, string &firstArray, string &secondArray, string &integerArray) {
    ostringstream FA;
    ostringstream SA;
    ostringstream IA;
    int number;
    string currString;
    ifSS >> currString;
    while (!ifSS.eof()) {
        FA << currString << " "; //outputting the source identifier 
        ifSS >> currString;
        SA  << currString << " "; //outputting the destination identifier
        ifSS >> number;
        IA << number << " ";  //outputting the bandwidth
        ifSS >> currString;
    }
    firstArray = FA.str();
    secondArray = SA.str();  //getting those information back to strings
    integerArray = IA.str();
}


void toupper(string &firstArray, string &secondArray) {  //making source and destination identifiers to uppercase
    int len = firstArray.size();
    for(int i = 0; i < len; i++) {
        firstArray.at(i) = toupper(firstArray.at(i));
    }
    int len2 = secondArray.size();
      for(int j = 0; j < len2; j++) {
        secondArray.at(j) = toupper(secondArray.at(j));
    }
}


void addArrays(string &firstarray, string& secondArray, string &collectionArray) { //merging source and destination identifiers to a single object to check uniqueness later
    ostringstream CA;
    istringstream FA(firstarray);
    istringstream SA(secondArray);
    string currstr;
    while (FA >> currstr) {
        CA << currstr << " ";
        SA >> currstr;
        CA << currstr << " ";
    }
    collectionArray = CA.str();
}



void unique(string &collectionArray, string &uniqueIdentifier) {  //finds all unique identifiers
    istringstream CA(collectionArray);
    bool x = true;
    string currString1;
    string currString2;
    CA >> uniqueIdentifier;
    while(CA >> currString1) {
        istringstream UI(uniqueIdentifier);
        while(UI >> currString2) {
            if(currString2 == currString1) {
                x = false;
                break;
            }
        }
        if (x == true) {
            uniqueIdentifier = uniqueIdentifier + "\n" + currString1;
        }
        x = true;
    }
}




int totalfromfunc(string &firstArray, string &integerArray, string &currStr) {
    istringstream FA(firstArray);
    istringstream IA(integerArray);
    string currStrf;
    int from;
    int totalfrom = 0;
    while (FA >> currStrf) {
        IA >> from;
        if(currStrf == currStr) {
            totalfrom = totalfrom + from;
        }
    }
    return totalfrom;
}



int totaltofunc(string &secondArray, string &integerArray, string &currStr) {
    istringstream SA(secondArray);
    istringstream IA(integerArray);
    string currStrto;
    int to;
    int totalto = 0;
    while (SA >> currStrto) {
        IA >> to;
        if(currStrto == currStr) {
            totalto = totalto + to;
        }
    }
    return totalto;
}


void bandwidth1(string &firstArray, string &secondArray, string &uniqueIdentifier, string& integerArray, ofstream &ofSS) {
    istringstream UI (uniqueIdentifier);
    ostringstream FR;
    float ratio = 0;
    int totalFrom = 0;
    int totalTo = 0;
    string currStr;
    while(UI >> currStr) {   //scans the string from the unique identifier
        totalFrom = totalfromfunc(firstArray, integerArray, currStr); //calculates the total bandwidth from the source identifier
        totalTo = totaltofunc(secondArray, integerArray, currStr);  //calculates the total bandwidth to the destination identifier
        if(totalFrom != 0 && totalTo != 0) {
            ratio = (float)totalTo/totalFrom;
            ofSS<< currStr << " " << totalFrom << " " << totalTo << " " << fixed << setprecision(2) << ratio <<endl; 
            /*if the identifier is on both source and destination
            calcualtes the total source and total destination bandwidth and its ratio*/
            FR << currStr << " " << totalFrom << " " << totalTo << " " << ratio <<endl;
        }

    }
    
}


int main(int argc, char** argv) {
    ifstream ifSS;
    ofstream ofSS;
    string collectionArray;
    string uniqueIdentifier;
    string firstArray;
    string secondArray;
    string integerArray;
    string finalResult;
    if(argc != 3) {
        cout << "Incorrect usage of file" << endl;
        return 1;
    }

    ifSS.open(argv[1]);
    ofSS.open(argv[2]);

    if(!ifSS.is_open()) {
        cout << "Couldn't open input file" << endl;
        return 2;
    }

    if(!ofSS.is_open()) {
        cout << "Couldn't open output file" << endl;
        return 3;
    }


    fileRead(ifSS, firstArray, secondArray, integerArray); //passed through reference
    toupper(firstArray, secondArray);
    addArrays(firstArray, secondArray, collectionArray);
    unique(collectionArray, uniqueIdentifier);
    ofSS << uniqueIdentifier << endl <<endl;
    bandwidth1(firstArray, secondArray, uniqueIdentifier, integerArray, ofSS);

    ifSS.close();
    ofSS.close();
    return 0;
}
