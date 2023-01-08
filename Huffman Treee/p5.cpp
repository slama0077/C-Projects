#include <iostream>
#include <vector>
#include <string>
#include <fstream>
/*This program accepts 3 text files as command line parameters that contains in-order traversal of a hoffman code tree, level-order traversal of the same tree, and encoded text in ASCII 0s and 1s respectively.
It makes the hoffman code tree from two tree traversals and decodes the encoded text. Hoffman code tree has been helpful in both memory and runtime efficiency. Plus, it can also be 
stretched to make a secured way for communication. To complete this project, the idea of recursion and linked-list is used.*/




using namespace std;

class nodes {  //this class helps to create nodes of the tree, each node contains a root, inorder vector, levelorder vector, left pointer, and right pointer
    public: 
    int root;
    vector <int> inOrder;
    vector <int> levelOrder;
    nodes* left;
    nodes* right;

    nodes() {   //default constructor of node class
        this->root = 0;
        this->left = NULL;
        this->right = NULL;
    }

    nodes(vector<int> inOrder, vector <int> levelOrder, nodes* left, nodes* right) {   //creates node with necessary information provided by the user
        this->inOrder = inOrder;
        this->levelOrder = levelOrder;
        this->left = left;
        this->right = right;
        this->root = levelOrder.at(0);
    }
};




class head {   //this class contains the root as an object (headH) of the entire tree
    public: 
    nodes* headH;
    head() {  //default constructor of head class
        headH = NULL;
    }



    void fillHead(vector<int> inOrder, vector <int> levelOrder) {  //this method fills the headH object to create a larger tree
        nodes* temp = new nodes(inOrder, levelOrder, NULL, NULL);  //a temporary node is created, which is pointed by the headH 
        headH = temp;
    }


    void makeTree() {  //this method creates a current node that points headH and intiliazes the creation of larger tree by calling makeTreeordered method
        nodes* cur = headH;
        makeTreeOrdered(cur);
    }



    int find(vector<int> list, int temp) {  //this function helps to find whether an integer is in the vector or not, which is extensively used in the creation of the tree later
        int counter = 0;
        for (int i = 0; i < list.size(); i++) {
            if(temp == list.at(i)) {
                return counter;
            }
            else {
                counter++;
            }
        }
        return -1;   //if the integer is not found it returns -1
    }


    void makeTreeOrdered(nodes* cur) {   //this method which will be triggered by makeTree() method is going to create the Hoffman tree by using recursion
        
        
        if(cur->inOrder.size() == 1) {   //basecase of recursion. if the size of the vector is 1, which means that the only element in the vector is the root itself, it returns and the recursion stops
            return;
        }


        int index = find(cur->inOrder, cur->root);  //for headH we already know the root, so it uses find() function to find the exact index of the root in inorder to initiate partition 
        vector<int> inOrderL;
        vector<int> inOrderR;               //these vectors are instantiated to complete partition
        vector<int> levelOrderL;
        vector<int> levelOrderR;
        int found;

        for(int i = 0; i < index; i++) {       //all elements on the left side to the index of inordertraversal is filled in inOrderL (inOrderleft)
            inOrderL.push_back(cur->inOrder.at(i));
        }


        for(int i = index + 1; i < cur->inOrder.size(); i++) {   //similarly to the right as well
            inOrderR.push_back(cur->inOrder.at(i));
        }


        for(int i = 0; i < cur->levelOrder.size(); i++) {      //now to fill levelorderL and levelorderR, findfunction is used
            found = find(inOrderL, cur->levelOrder.at(i));  //inOrderL is taken as a prototype
            if (cur->levelOrder.at(i) == cur->root) {   //if it's root no action is taken
                
            }
            else {
                if(found == -1) {              //if the find function returns -1, that means it doesn't belong to the left side of levelOrder. so, levelorderR is filed with those eleemnts
                    levelOrderR.push_back(cur->levelOrder.at(i));
                }
                else {                         //similarly, if it returns anything besides 1, levelOrderL is filled
                    levelOrderL.push_back(cur->levelOrder.at(i));
                }
            }
        }
        nodes *curL = new nodes(inOrderL, levelOrderL, NULL, NULL);   //now the node is created using these vectors
        nodes *curR = new nodes(inOrderR, levelOrderR, NULL, NULL);
        cur->left = curL;                                           //and it is linked to the current node
        cur->right = curR;
        makeTreeOrdered(curL);     //calls makeTreeOrdered function again with curL (currentLeft) and curR (currentRight) as arguments and uses the idea of recursion to make tree
        makeTreeOrdered(curR);
    }
};



template <typename myType>
void fileRead(ifstream& file, vector<myType>& list) {   //this method reads the file and stores the data in respective vectors
    myType temp;
    while(file >> temp) {
        list.push_back(temp);
    }
}

void printTree(nodes* headH, vector<char> encoded) {  
    /*This method decodes the message that is stored in encoded.txt, as ASCII value 0s and 1s, which is already stored on vector<>encoded object. The idea is to traverse through the 
    vector and traverse through the built tree simultaneously. Once the end of the tree is hit, or say once a node with no left or right branch is reached, it decodes the root of that
    node by converting that int data type into char data type.*/

    int counter = 0;
    while(counter < encoded.size()) {  //this while loop runs until the counter doesnt exceed the vector size
        nodes* cur = headH;   //a current node is created to traverse through the tree
        while(cur->right != NULL && cur->left != NULL) { //this while loop runs until the node with no branches is found
            if(encoded.at(counter) == '1') {   //if the ASCII value is 1 it goes to the right 
                cur = cur->right;
                counter++;
            }
            else if(encoded.at(counter) == '0') { // 0 to left
                cur = cur->left;
                counter++;
            }
        }
        cout << char(cur->root);   //prints out the obtained data by converting into char data type
    }

}

int main(int argc, char** argv) {
    ifstream ifInOrder;
    ifstream ifLevelOrder;   //file streams
    ifstream ifEncode;
    vector <int> inOrder;
    vector <int> levelOrder;
    vector <char> encoded;
    if(argc != 4) {   //4 command line arguments are required
        cout << "Incorrect usage of files" << endl;
        return 0;
    }
    ifInOrder.open(*(argv + 1));
    ifLevelOrder.open(*(argv+2));
    ifEncode.open(*(argv +3));
    if(!ifInOrder.is_open()) {
        cout << "Couldn't open the inorder file"<< endl;
        return 1;
    }
    if(!ifLevelOrder.is_open()) {
        cout << "Couldn't open levelorder file" << endl;
        return 2;
    }
    if(!ifEncode.is_open()) {
        cout << "Couldn't open encode file" << endl;
        return 3;
    }
    fileRead(ifInOrder, inOrder);
    fileRead(ifLevelOrder, levelOrder);  //triggers the file read function to read the file and store in necessary vectors
    fileRead(ifEncode, encoded);
    head* tree = new head();
    tree->fillHead(inOrder, levelOrder);  //creates head and fills the head
    tree->makeTree();              //calls the makeTree() method which calls makeTreeOrdered() to create the entire tree
    nodes* cur = tree->headH;
    printTree(cur, encoded);  //decodes and prints the decoded message
    return 4;
}