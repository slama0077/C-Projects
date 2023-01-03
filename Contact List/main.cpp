#include <iostream>
#include <string>               //with this file, the user can interact with the program to perform actions to create the contactlist
#include "p3.h"
                                //this program uses three-layers-deep linked lists to create a contactlist with different infos of each created contact in linear time. 
using namespace std;
                                

int main(int argc, char *argv[]) {
    bool printPrompts = true;        //a generic bool data type used everywhere in the file to proceed the task
    if (argc == 2 && string(argv[1]) == "no") {
        printPrompts = false;
    }

    ContactList *list = new ContactList();

    string cmd, first, last, infoName, infoVal;   //according to the command, stored in cmd string, given by user calls to the classes and their methods is done
    while (1) {
        if (printPrompts) cout << "Enter a command or \"help\" to get a command list: ";
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "addContact") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list->addContact(first, last)) {    //calls addcontact method and if the contact already exists then prints this
                cout << "Error: " << first << " " << last << " already exists" << endl;
            }
        }
        else if (cmd == "addInfo") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter info name: ";
            cin >> infoName;
            if (printPrompts) cout << "\tEnter info value: ";
            cin >> infoVal;
            if (!list->addInfo(first, last, infoName, infoVal)) {   //calls addinfo method and if the contact doesn't exits then prints this:
                cout << "Error: " << first << " " << last << " does not exist" << endl;
            }
        }
        else if (cmd == "printContact") {
            if (printPrompts) cout << "\tEnter first name: ";   
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list->printContact(cout, first, last)) {  //calls printcontact method
                cout << "Error: " << first << " " << last << " does not exist" << endl;
            }
            cout << endl;
        }
        else if (cmd == "count") {
            cout << "\nThere are " << list->getCount() << " contacts" << endl;  //calls the getcount method to get the number of contacts in the list
        }
        else if (cmd == "print") {
            list->print(cout);
            cout << endl;
        }
        else if (cmd == "addContactOrdered") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list->addContactOrdered(first, last)) {
                cout << "Error: " << first << " " << last << " already exists" << endl;
            }
        }
        else if (cmd == "addInfoOrdered") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter info name: ";
            cin >> infoName;
            if (printPrompts) cout << "\tEnter info value: ";
            cin >> infoVal;
            if (!list->addInfoOrdered(first, last, infoName, infoVal)) {
                cout << "Error: " << first << " " << last << " does not exist" << endl;
            }
        }
        else if (cmd == "removeInfo") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter info name: ";
            cin >> infoName;
            if (!list->removeInfo(first, last, infoName)) {   //calls removeinfo method, if the contact doesn't exist then prints this:
                cout << "Error: " << first << " " << last << " or " << infoName << " does not exist" << endl;
            }
        }
        else if (cmd == "removeContact") {
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list->removeContact(first, last)) {
                cout << "Error: " << first << " " << last << " does not exist" << endl;
            }
        }
        else if (cmd == "destroy") { 
            delete list;
            list = new ContactList();
        }
        else if (cmd == "copycon" || cmd == "copy=") {
            ContactList *list2;   //new contactlist object list2 created
            if (cmd == "copycon") {  
                list2 = new ContactList(*list);  //calls the copy constructor 
            }
            else {
                list2 = new ContactList();
                *list2 = *list;   //calls the assignment constructor
            }

            if (printPrompts) cout << "\tAdd contact to copied list:" << endl;
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (!list2->addContact(first, last))   //calls addcontact method for the list2 object, if the contact is already there then prints this:
            {
                cout << "Error: " << first << " " << last << " already exists" << endl;
            }
            
            if (printPrompts) cout << "\tAdd info to copied list:" << endl;
            if (printPrompts) cout << "\tEnter first name: ";
            cin >> first;
            if (printPrompts) cout << "\tEnter last name: ";
            cin >> last;
            if (printPrompts) cout << "\tEnter info name: ";
            cin >> infoName;
            if (printPrompts) cout << "\tEnter info value: ";
            cin >> infoVal;
            if (!list2->addInfo(first, last, infoName, infoVal))
            {
                cout << "Error: " << first << " " << last << " or " << infoName << "does not exist" << endl;
            }

            cout << "Original list:" << endl;  //prints out the original list
            list->print(cout);
            cout << endl;

            cout << "Copied list:" << endl;  //prints out the copied list
            list2->print(cout);
            cout << endl;

            delete list2;
        }
        else if (cmd == "help") {
            cout << "Valid commands:" << endl;
            cout << "addContact" << endl;
            cout << "addInfo" << endl;
            cout << "printContact" << endl;
            cout << "count" << endl;
            cout << "print" << endl;
            cout << "addContactOrdered" << endl;
            cout << "addInfoOrdered" << endl;
            cout << "removeContact" << endl;
            cout << "removeInfo" << endl;
            cout << "destroy" << endl;
            cout << "copycon" << endl;
            cout << "copy=" << endl;
            cout << "help" << endl;
            cout << "quit" << endl;
        }
        else {
            cout << "Invalid command specified - " << cmd << endl;
        }
        if (printPrompts) cout << endl;
    }
    return 0;
}
