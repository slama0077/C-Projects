#ifndef _P3_H_
#define _P3_H_

//this is the header file that contains class and method defintions which will be implemented in p3.cpp file that contains method implementation

#include <iostream>
#include <string>

//have commented out the class and its functionality and the private members of those classes. the functionality of public members (methods) will be done in p3.cpp file



class Info { //this class helps to create an ovject of info for the contacts created
public:
    std::string name;
    std::string value;
    Info *next;

    Info(); 
    Info(std::string name, std::string value, Info *next = nullptr);
    int isSameInfo(Info* rhs);
    int infoCompare(Info* rhs);
};

class Contact {  //this class helps to create an object of contact that has first and last name. this also contains the head pointer of the info for each contact
public:
    std::string first;
    std::string last;
    Contact *next;
    Info *headInfoList;  //head pointer of the infos that will be created for each contact

    Contact();
    Contact(std::string first, std::string last, Contact *next = nullptr);
    int isSameContact(Contact* rhs);
    int contactCompare(Contact* rhs);
};

class ContactList {  //this class contains head pointer of the contact and different methods that will be accesed to create, print, and remove the contact list 
private:
    Contact *headContactList;  //head pointer of the contacts that will be created
    int count;
public:
    ContactList();

    int getCount();
    
    bool printContact(std::ostream &os, std::string first, std::string last);
    void print(std::ostream &os);

    bool addContact(std::string first, std::string last);
    bool addInfo(std::string first, std::string last, std::string infoName, std::string infoVal);

    bool addContactOrdered(std::string first, std::string last);
    bool addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal);
    
    bool removeContact(std::string first, std::string last);
    bool removeInfo(std::string first, std::string last, std::string infoName);

    ~ContactList();
    ContactList(const ContactList &src);
    const ContactList &operator=(const ContactList &src);
    void clear();
};

#endif
