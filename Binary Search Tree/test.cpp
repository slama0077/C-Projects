#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template <typename myType>
class binary {
    public: 
    myType data;
    binary<myType>* left;
    binary <myType>* right;
    binary();
    binary(myType data, binary<myType>* left, binary<myType>* right);
};
template <typename myType>
class doublyBinary {
    public:
    binary<myType>* prev;
    binary<myType>* cur;
    
    doublyBinary() {
        prev = NULL;
        cur = NULL;
    }
};
template <typename myType>
class root {
    public:
    binary<myType>* rootH;
    root();
    void addNumbers(myType data);
    void lastRootAdd(binary<myType>* cur, binary<myType>* temp);
    void preOrder();
    void preOrderTraversal(binary<myType>* cur);
    void postOrder();
    void postOrderTraversal(binary<myType>* cur);
    void inOrder();
    void inOrderTraversal(binary<myType>* cur);
    void nodeSearch();
    binary<myType>* nodeSearchTraversal(binary<myType>* cur, myType data);
    void removeDataX();
    doublyBinary<myType>* findParentChildX(doublyBinary<myType>* temp, myType data);
    doublyBinary<myType>* findSuccessor(doublyBinary<myType>*temp);
};

template <typename myType>
binary<myType>::binary() {
    data = 0;
    left = NULL;
    right = NULL;
}
template <typename myType>
binary<myType>::binary(myType data, binary<myType>* left, binary<myType>* right) {
    this->data = data;
    this->left = left;
    this->right = right;
}
template <typename myType>
root<myType>::root() {
    rootH = NULL;
}
template <typename myType>
void root<myType>::lastRootAdd(binary<myType>* cur, binary<myType>* temp){
    if(temp->data  < cur->data) {    //checks whether the new data is small than current data
        if(cur->left == NULL) {      // curr data has no child and is bigger than the new data then it is put on the left
            cur->left = temp;
        }
        else {
            lastRootAdd(cur->left, temp); //otherwise recursion
        }
    }
    else {
        if(cur->right == NULL) { //same with the righ if the number collides then it goes to the right
            cur->right = temp;
        }
        else {
            lastRootAdd(cur->right, temp); //recursion
        }
    }
}


template <typename myType>
void root<myType>::addNumbers(myType data) {
    binary<myType> *temp = new binary<myType>(data, NULL, NULL);
    if(rootH == NULL) {
        rootH = temp;
    }
    else {
        binary<myType>* cur = rootH;
        lastRootAdd(cur, temp);
    }
}

template <typename myType>
void root<myType>::preOrder() {
    binary<myType>* cur = rootH;
    cout << "Your preorder traversal list: " << endl;
    preOrderTraversal(cur);
    cout << endl;
}

template <typename myType>
void root<myType>::preOrderTraversal(binary<myType>* cur) {
    if(cur == NULL) {
        return;
    }
    cout<< cur->data << " ";
    preOrderTraversal(cur->left);
    preOrderTraversal(cur->right);
}


template <typename myType>
void root<myType>:: postOrder() {
    binary<myType>* cur = rootH;
    cout << "Your postorder traversal list: " << endl;
    postOrderTraversal(cur);
    cout << endl;
}


template <typename myType>
void root<myType>::postOrderTraversal(binary<myType>* cur) {
    if(cur == NULL) {
        return;
    }
    postOrderTraversal(cur->left);
    postOrderTraversal(cur->right);
    cout << cur->data << " ";
}


template <typename myType>
void root<myType>:: inOrder() {
    binary<myType>* cur = rootH;
    cout << "Your inorder traversal list: " << endl;
    inOrderTraversal(cur);
    cout << endl;
}


template <typename myType>
void root<myType>::inOrderTraversal(binary<myType>* cur) {
     if(cur == NULL) {
        return;
    }
    inOrderTraversal(cur->left);
    cout<< cur->data << " ";
    inOrderTraversal(cur->right);
}


template <typename myType>
void root<myType>:: nodeSearch() {
    myType searchData;
    cout << "What data are you looking for?"<< endl;
    cin >> searchData;
    binary<myType>* cur = rootH;
    binary<myType>* temp = nodeSearchTraversal(cur, searchData);
    if(temp == nullptr) {
        cout << "Sorry, didn't find the data (" << searchData << ") you are looking for." << endl;
    }
    else {
        cout << "Data found:" << temp->data << endl;
    }

}


template <typename myType>
binary<myType>* root<myType>:: nodeSearchTraversal(binary<myType>* cur, myType data) {
    if(cur == NULL) {
        return nullptr;
    }
   else if(cur->data == data) {
        return cur;
    }
    else {
        if(data < cur->data) {
           return nodeSearchTraversal(cur->left, data);
            // return nullptr;
        }
        else {
           return nodeSearchTraversal(cur->right, data);
            // return nullptr;
        }
    }
}


template <typename myType>
void root<myType>::removeDataX() {
    myType data;
    cout << "What data do you want to remove from the list?" << endl;
    cin >> data;
    doublyBinary<myType>* temp = new doublyBinary<myType>();
    temp->cur = rootH;
    doublyBinary<myType>* temp2 = findParentChildX(temp, data);
    if(temp2 == NULL) {
        cout << "Data is not on the list" << endl;
        return;
    }
    binary<myType>* par = temp2->prev;
    binary<myType>* cur = temp2->cur;
    // cout << par->data << endl;
    cout << cur->data << endl;
    if(cur->left == NULL && cur->right == NULL) {
        if(cur->data < par->data) {
            par->left = NULL;
            delete cur;
            return;
        }
        else {
            par->right = NULL;
            delete cur;
            return;
        }
    }

    else if(cur ->left == NULL) {
        if(cur->data < par->data) {
            par->left = cur->right;
        }
        else {
            par->right = cur->right;
        }
        delete cur;
    }
    else if(cur->right == NULL) {
        if(cur->data < par->data) {
            par->left = cur->left;
        }
        else {
            par->right = cur->left;
        }
        delete cur;
    }
    
    else {
        doublyBinary<myType>* x = new doublyBinary<myType>();
        x->cur = cur->right;
        x->prev = cur;
        doublyBinary<myType>* x2 = findSuccessor(x);
        cur->data = x2->cur->data;
        if(cur->right->data == x2->cur->data) {
            cur->right = NULL;
            delete (x2->cur);
        }
        else if(x2->cur->right == NULL) {
            x2->prev->left = NULL;
            delete(x2->cur);
        }
        else {
            x2->prev->left = x2->cur->right;
            delete(x2->cur);
        }
    }

}


template <typename myType>
doublyBinary<myType>* root<myType>:: findSuccessor(doublyBinary<myType>* temp) {
    if(temp->cur->left == NULL) {
        // cout << temp->cur->data << endl;
        return temp;
    }
    else {
        temp->prev = temp->cur;
        temp->cur = temp->cur->left;
        return findSuccessor(temp);
    }
}


template <typename myType>
doublyBinary<myType>* root<myType>::findParentChildX(doublyBinary<myType>* temp, myType data) {
    // cout << temp->cur->data << "XX" << endl;
    if(temp->cur == NULL) {
        return NULL;
    }
    if(temp->cur->data == data) {
        // cout << temp->cur->data << endl;
        return temp;
    }
    else if(data < temp->cur->data) {
        temp->prev = temp->cur;
        // cout << "prev: " << temp->prev->data << endl;
        temp->cur = temp->cur->left;
        // cout << "cur: " << temp->cur->data << endl;
        return findParentChildX(temp, data);
    }
    // if(data > temp->cur->data) {
    else {
        temp->prev = temp->cur;
        // cout << "prev: "<< temp->prev->data << endl;
        temp->cur = temp->cur->right;
        // cout <<"cur: " << temp->cur->data << endl;
        return findParentChildX(temp, data);
    }
};




int main() {
    ifstream ifSS;
    // root<int>* tree = new root<int>();
    root<string>* tree = new root<string>();
    string data;
    string fileName;
    cout << "Type the filename: " << endl;
    cin >> fileName;
    
    ifSS.open(fileName);
    if(!ifSS.is_open()) {
        cout << "Couldn't find the data" << endl;
        return 1;
    }
    while(ifSS >> data) {
        tree->addNumbers(data);
    }
    string command;
    cout << "What's your command from the list?" << endl << "PreOrder, PostOrder, InOrder, NodeSearch, RemoveData , Quit" << endl ;
    cin >> command;
    
    while(1) {
        if(command == "Quit") break;
        else if(command == "PreOrder") {
            tree->preOrder();
        }
        else if(command == "PostOrder") {
             tree->postOrder();
        }
        else if(command == "InOrder") {
            tree->inOrder();
        }
        else if(command == "NodeSearch") {
            tree->nodeSearch();
        }
        else if(command == "RemoveData") {
            tree->removeDataX();
        }
        else {
            cout << "Your command is wrong. Please type another command or quit." << endl;
        }
        cout << "What's your next command?" << endl;
        cin >> command;
    }
    ifSS.close();
    return 0;
}