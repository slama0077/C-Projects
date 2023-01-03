#include <iostream>
#include <string>

#include "p3.h"

using namespace std;



//this file contains the implementation of all the methods defined in p3.h header file

Info::Info() { //default constructor
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {  //this method creates an info object of a specified contact that has name, value and pointer to the next info
    this->name = name;
    this->value = value;
    this->next = next;
}
int Info::isSameInfo(Info* rhs) {  //checks if the info is the same 
    if (this -> name == rhs -> name) {
        return 1;
    }
    else {
        return 0;
    }
}


int Info::infoCompare(Info* rhs) {  //compares if the info's name to check if it is either bigger or smaller to create ordered info list
    if(this -> name < rhs -> name) {
        return 1;
    }
    else {
        return 0;
    }
}

Contact::Contact() {  //default constructor for contact class
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {  //creates a contact object that has first name, last name, and the head pointer of the info
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}


int Contact::isSameContact(Contact* rhs) {   //checks if the contact is the same to avoid collisions
    if((this->first == rhs->first) && (this->last == rhs->last)) {
        // cout << "Same" <<endl; //remove
        return 1;
    }
    else {
        // cout << "not same" << endl; //remove
        return 0;
    }
}


int Contact::contactCompare(Contact* rhs) {   //heirarchical comparison of the contacts.the herirachy is last name and first name
    if((this->last) < (rhs->last)) return 1;
    if((this->last) > (rhs->last)) return -1;
    if((this->first) < (rhs->first)) return 1;
    if((this -> first) > (rhs->first)) return -1;
    return 0;
}


ContactList::ContactList() {  //default  constructor of contactlist class
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {  //returns the no. of contacts in the list.
    return this->count;
}



// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {  //prints the contact and its information 
    Contact* cur = headContactList;
    for(cur; cur != nullptr; cur = cur->next) {  //this for loop checks whether the contact is in the list or not
        if((cur->first == first) && (cur->last == last)) {  
            break;
        }
    }
    if(cur == nullptr) {  //if the contact is not on the list returns false otherwise prints the informationd
        return false;
    }
    os << "Contact Name: " << cur->first << " " << cur->last << endl;   //prints contact name and information using for loop in linked list
    for(Info* curI = cur->headInfoList; curI != nullptr; curI = curI -> next) {  
            os << "\t" << curI -> name << " | " << curI -> value << endl;
        }
    return true;
}



// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {  //prints all the contacts in the list and their stored information 
    for(Contact* cur = headContactList; cur != nullptr; cur=cur->next) {
        os << "Contact Name: " << cur->first << " " << cur->last << endl;
        for(Info* curI = cur->headInfoList; curI != nullptr; curI = curI -> next) {
            os << "\t" << curI -> name << " | " << curI -> value << endl;
        }
    }

}



// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {  //this method adds contact in the contact list which is not ordered, first come first serve
    Contact* temp = new Contact(first, last);  //creates a contact object
    if(headContactList == nullptr) {   //if the head pointer of the contact list is null, the head pointer points to the new contact created
        headContactList = temp;
        count++;
    }
    else {    
        Contact* cur = headContactList;
        while(cur != nullptr) {  //checks whether the contact is already on the list or not
            if(temp->isSameContact(cur) == 1) {  //returns false if the contact is already on the list
                return false;
            }
            cur = cur->next;
        }
        cur = headContactList;
        while(cur -> next != nullptr) {   //this adds the created contact object to the end of the contact list
            cur = cur->next;
        }
        cur->next = temp;
        count++;
    }
    return true;
}



// adds info to the back of a contact's info list
// 1. returns false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, updates the infoValue and returns true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {  
    Contact* cur = headContactList;
    for(cur; cur != nullptr; cur = cur->next) {  //checks availability of contact
        if((cur->first == first) && (cur->last == last)) {
            break;
        }
    }
    if(cur == nullptr) {
        return false;
    }
    Info* temp = new Info(infoName, infoVal);  //creates an info object 
    if(cur->headInfoList == nullptr) {   //if there is no info, head pointer of the info list points at the new info object
        cur->headInfoList = temp;
    }
    else {
        Info* curI = cur->headInfoList;
        while(curI != nullptr) {     //updates the info value if same info name is found
            if((temp->isSameInfo(curI)) == 1) {
                curI->value = temp->value;
                return true;
            }
            curI = curI->next;
        }
        curI = cur->headInfoList;
        while(curI -> next != nullptr) {
            curI = curI-> next;
        }
        curI -> next = temp;     //adds info to the back of the info list
    }
    return true;
}




// adds a contact to the list in ascending order by last name
//     if last names are equal, then orders by first name ascending
// 1. returns false and does nothing if the contact is already in the list
// 2. otherwise returns true and adds the contact to the list
// - compares strings with the built-in comparison operators: <, >, ==, etc.
bool ContactList::addContactOrdered(std::string first, std::string last) {
    Contact* temp = new Contact(first, last);   
    if(headContactList == nullptr) { 
        headContactList = temp;
        count++;
    }
    else {
        Contact* cur = headContactList;
        while(cur != nullptr) {
            if(temp->isSameContact(cur) == 1) { //checks if the new contact is already in the list
                return false;
            }
            cur = cur->next;
        }
        if(temp->contactCompare(headContactList) > 0) { //compares the new object with head, if smaller adds before head
            temp->next = headContactList;
            headContactList = temp;
            count++;
        }
        else {
            cur = headContactList -> next;
            Contact* prev = headContactList;  //uses two pointers current and previous to find the correct spot of the new contact
            while(cur != nullptr) {  //finds the current contact that is just bigger than the new contact
                if(temp->contactCompare(cur) > 0) {
                    break;
                }
            cur = cur->next;
            prev= prev->next;
        }
        prev->next = temp;  
        temp->next = cur;  //inserts the new contact between the current and the previous contact
        count++;
        }

    }

    return true;
}



// adds info to a contact's info list in ascending order by infoName
// 1. returns false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, updates the infoValue and returns true
// 3. otherwise adds the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact* cur = headContactList;
    for(cur; cur != nullptr; cur = cur->next) {
        if((cur->first == first) && (cur->last == last)) {
            break;
        }
    }
    if(cur == nullptr) {  
        return false;
    }
    Info* temp = new Info(infoName, infoVal);
    if(cur->headInfoList == nullptr) {  //if the infolist is empty the headpointer of the infolist points to the new info object
        cur->headInfoList = temp;
    }
    else {
        Info* curI = cur->headInfoList;
        while(curI != nullptr) {
            if((temp->isSameInfo(curI)) == 1) {
                curI->value = temp->value;    //updates the infovalue if same infoname
                return true;
            }
            curI = curI->next;
        }
        if(temp->infoCompare(cur->headInfoList) == 1) {  //checks if the new info is smaller than the head info, if smaller adds the new info before headinfo
            temp->next = cur->headInfoList;
            cur->headInfoList = temp;    //the headpointer now points at the new info
        }
        else {
            curI = cur->headInfoList->next;  //same idea as used in addcontactordered
            Info* prevI = cur->headInfoList;
            while(curI != nullptr) {
                if(temp->infoCompare(curI) == 1) {
                    break;
                }
                curI = curI->next;
                prevI = prevI -> next;
            }
            prevI->next = temp;
            temp->next = curI;
        }

    }
    return true;
}



// removes the contact and its info from the list
// 1. returns false and does nothing if the contact is not in the list
// 2. otherwise returns true and removes the contact's info first to avoid memory leakage and removes the contact after that
// updates the count
bool ContactList::removeContact(std::string first, std::string last) {
    Contact* cur = headContactList;
    for(cur; cur != nullptr; cur = cur->next) {
        if((cur->first == first) && (cur->last == last)) {
            break;
        }
    }
    if(cur == nullptr) {  //when contact is not found
        return false;
    }
    if(headContactList->first == first && headContactList->last == last) {  //if headcontactlist is to be removed
        Contact* prevHead = headContactList;  //creates a pointer that points at the headcontactlist that should be deleted
        headContactList = headContactList->next;  //new headcontactlist to preserve orderness
        Info* temp = prevHead->headInfoList;
        while(temp != nullptr) {   //deletes all the info asssociated with the contact to avoid memory leakage
            Info* prevTemp = temp;
            temp = temp->next;
            delete prevTemp;
        }
        delete prevHead;  //deletes the headcontactlist
        count--;
    }
    else {      //if other contacts is to be removed
        cur = headContactList->next; 
        Contact* prev = headContactList;   //use of two pointers current and previous to remove the needed contact and also preserve orderness
        while(cur != nullptr) {
            if((cur->first == first) && (cur->last == last)) {  //cur points at the contact that needs to be removed
            break;
            }
            cur = cur->next;
            prev = prev-> next;
        }
        prev->next = cur->next;  //previous' next and current's next are linked, leaving current behind
        Info* temp = cur->headInfoList;
        while(temp != nullptr) {  //removes all the info associated with the cur's contact
            Info* prevTemp = temp;
            temp = temp->next;
            delete prevTemp;
        }
        delete cur;   //deletes current preserving orderness and without memory leakage
        count--;
    }
    return true;
}



// removes the info from a contact's info list
// 1. returns false and do nothing if the contact is not in the list
// 2. returns false and do nothing if the info is not in the contact's info list
// 3. otherwise returns true and removes the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    Contact* cur = headContactList;
    for(cur; cur != nullptr; cur = cur->next) {
        if((cur->first == first) && (cur->last == last)) {
            break;
        }
    }
    if(cur == nullptr) {
        return false;
    }
    Info* curI = cur->headInfoList;
    while(curI != nullptr) {
        if(curI->name == infoName) {
            break;
        }
        curI = curI->next;
    }
    if(curI == nullptr) {
        return false;
    }
    if(cur->headInfoList->name == infoName) {  //if head pointer of the info list is to be removed 
        Info* prevHead = cur->headInfoList;
        cur->headInfoList = cur->headInfoList->next;
        delete prevHead;
    }
    else {  //if other info is to be removed, uses the idea of the remove contact
        curI = cur->headInfoList->next;
        Info* prevI = cur->headInfoList;
        while(curI != nullptr) {
            if(curI->name ==  infoName) {
                break;
            }
            curI = curI->next;
            prevI = prevI->next;
        }
        prevI->next = curI->next;
        delete(curI);
    }
    return true;
}



void ContactList::clear() {  //uses removecontact to remove everything for destructor
    Contact* cur = headContactList;
    while(cur != nullptr) {
        removeContact(cur->first, cur->last);
        cur = cur->next;
    }
}


// destroys the list by removing all contacts and their infos
ContactList::~ContactList() {  //destructor of contactlist
    clear();
}


// deep copies the source list
//copy constructor
ContactList::ContactList(const ContactList &src) {
    headContactList = nullptr;
    for(Contact* cur= src.headContactList; cur!=nullptr; cur = cur->next) {
        addContact(cur->first, cur->last);
        for(Info* curI = cur->headInfoList; curI != nullptr; curI = curI->next) {
            addInfo(cur->first, cur->last, curI->name, curI->value);
        }
    }
}


// removes all contacts and their infos then deep copies the source list
//assignment constructor
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {
        clear();
        for(Contact* cur= src.headContactList; cur!=nullptr; cur = cur->next) {
            addContact(cur->first, cur->last);
            for(Info* curI = cur->headInfoList; curI != nullptr; curI = curI->next) {
                addInfo(cur->first, cur->last, curI->name, curI->value);
        }
    }
    }
    return *this;
}