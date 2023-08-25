#include <iostream>
#include <string>

using namespace std;
template<typename keytype, typename valuetype>
class nodes {
    public:
        keytype key;
        valuetype value;
        string color;
        int leftChild;
        int rightChild;
        nodes* left;
        nodes* right;
        nodes* parent;
        nodes() {
            color = "NA";
            left = NULL;
            right = NULL;
            parent = NULL;
            leftChild = 0;
            rightChild = 0;
        }

        nodes(keytype key, valuetype value, string color, int leftChild, int rightChild) {
            this->key = key;
            this->value = value;
            this->color = color;
            this->leftChild = leftChild;
            this->rightChild = rightChild;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
        }
};

template <typename keytype, typename valuetype>
class RBTree {

   private: 
    nodes<keytype, valuetype>* nil;
    nodes<keytype, valuetype>* root;
    int count;
    
    void leftRotate(nodes<keytype, valuetype>* x) {
        nodes<keytype, valuetype>* y = x->right;
        x->right = y->left;
        if(y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil) {
            root = y;
        }
        else if(x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        x->rightChild = y ->leftChild;
        y->leftChild = y->leftChild + x->leftChild + 1;
    }

    void rightRotate(nodes<keytype, valuetype>* x) {
        nodes<keytype, valuetype>* y = x->left;
        x->left = y->right;
        if(y->right != nil) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
        x->leftChild = y->rightChild;
        y->rightChild = y->rightChild + x->rightChild + 1;
    }

    void insertFixup(nodes<keytype, valuetype>* z) {
        nodes<keytype, valuetype>* y;
        while(z->parent->color == "red") {
            if(z->parent == z->parent->parent->left) {
                y = z->parent->parent->right;
                if(y->color == "red") {
                    z->parent->color = "black";
                    y->color = "black";
                    z->parent->parent->color = "red";
                    z = z->parent->parent;            
                }
                else if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                    z->parent->color = "black";
                    z->parent->parent->color = "red";
                    rightRotate(z->parent->parent);
                }
                else {
                    z->parent->color = "black";
                    z->parent->parent->color = "red";
                    rightRotate(z->parent->parent);
                }
            }
            else {
                y = z->parent->parent->left;
                if(y->color == "red") {
                    z->parent->color = "black";
                    y->color = "black";
                    z->parent->parent->color = "red";
                    z = z->parent->parent;
                }
                else if(z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                    z->parent->color = "black";
                    z->parent->parent->color = "red";
                    leftRotate(z->parent->parent);
                }
                else {
                    z->parent->color = "black";
                    z->parent->parent->color = "red";
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = "black";
    }

    int checkOrdered(keytype* k, int s) {
        for(int i = 0; i < (s-1); i++) {
            if (*(k+i+1) > *(k + i)) {                
            }
            else {
                return 0;
            }
        }
        return 1;
    }

    int checkPerfect(int s) {
        int i = 1;
        int h = -1;
        
        while(1) {
            s = s - i;
            i = i*2;
            h++;
            if(s < 0 || s == 0) {
                break;
            }
        }
        if(s == 0) {
            return -1;
        }
        else {
            return h;
        }
    }

    void insertChad(keytype k, valuetype v, int height, int depth) {
        nodes<keytype, valuetype>* z = new nodes<keytype,valuetype>(k, v, "NA", 0, 0);
        nodes<keytype, valuetype>* y = nil;
        nodes<keytype, valuetype>* x = root;

        while(x != nil) {
            y = x;
            if(z->key < x->key) {
                x->leftChild++;
                x = x->left;
            }
            else {
                x->rightChild++;
                x = x->right;
            }
        }
        z->parent = y;
        if(y == nil) {
            root = z;
        }
        else if(z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
       
        if(height < 0) {
            z->color = "black";
        }
        else if(depth < height) {
            z->color = "black";
        }
        else {
            z->color = "red";
        }
        count++;

    }


    void sortedInsertion(keytype* k, valuetype* v, int s, int l, int h, int d) {

        if(s > l) {
            return;
        }
        int m = (s + l)/2;
        insertChad(k[m], v[m],h,d);
        d++;
        sortedInsertion(k, v, s, m-1, h, d);
        sortedInsertion(k, v, m+1, l, h, d);
    }

    void inOrderTraversalOrdered(nodes<keytype, valuetype>* cur) {
        if(cur == nil) {
            return;
        }
        inOrderTraversalOrdered(cur->left);
        cout << cur->key << " ";
        inOrderTraversalOrdered(cur->right);
    }


    void insertchadl(keytype k, valuetype v, string color) {
        nodes<keytype, valuetype>* z = new nodes<keytype,valuetype>(k, v, color, 0, 0);
        nodes<keytype, valuetype>* y = nil;
        nodes<keytype, valuetype>* x = root;

        while(x != nil) {
            y = x;
            if(z->key < x->key) {
                (x->leftChild)++;
                x = x->left;
            
            }
            else {
                (x->rightChild)++;
                x = x->right;
            }
        }
        z->parent = y;
        if(y == nil) {
            root = z;
        }
        else if(z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        count++;
    }

    void preOrderTraversalOrdered(nodes<keytype, valuetype>* cur) {
        if(cur == nil) {
            return;
        }
        cout << cur->key << " ";
        preOrderTraversalOrdered(cur->left);
        preOrderTraversalOrdered(cur->right);
    }
    void spreOrderTraversalOrdered(nodes<keytype, valuetype>* cur, nodes<keytype, valuetype>* snil) {
        if(cur == snil) {
            return;
        }
        insertchadl(cur->key, cur->value, cur->color);
        spreOrderTraversalOrdered(cur->left, snil);
        spreOrderTraversalOrdered(cur->right, snil);
    }

    void postOrderTraversalOrdered(nodes<keytype, valuetype>* cur) {
        if(cur == nil) {
            return;
        }
        postOrderTraversalOrdered(cur->left);
        postOrderTraversalOrdered(cur->right);
        cout<< cur->key << " ";
    }

    nodes<keytype,valuetype>* nodeSearch(nodes<keytype, valuetype>* cur, keytype k) {
        if (cur == nil) {
            return nil;
        }
        else if(cur->key == k) {
            return cur;
        }
        else {
            if(k < cur->key) {
                return nodeSearch(cur->left, k);
            }
            else {
               return nodeSearch(cur->right, k);
            }
        }

    }

    nodes<keytype, valuetype>* selectChad(int pos) {
        nodes<keytype, valuetype>* cur = root;
        if(pos < 1 || pos > count || root == nil) {
            cout << "Invalid position" << endl;
            return nil;
        }
        else {
            while(1) {
                int x = 1;
                x = x + cur->leftChild;
                if(pos == x) {
                    break;
                }
                else if(pos > x) {
                    pos = pos - x;
                    cur = cur->right;
                }
                else {
                    cur = cur->left;
                }
            }
        
        }
        return cur;
    }

    nodes<keytype,valuetype>* pseudonegatives(nodes<keytype, valuetype>* cur, keytype k) {
        if (cur == nil) {
            return nil;
        }
        else if(cur->key == k) {
            return cur;
        }
        else {
            if(k < cur->key) {
                cur->leftChild--;
                return pseudonegatives(cur->left, k);
            }
            else {
                cur->rightChild--;
               return pseudonegatives(cur->right, k);
            }
        }

    }


    nodes<keytype,valuetype>* pseudopositives(nodes<keytype, valuetype>* cur, keytype k) {
        if (cur == nil) {
            return nil;
        }
        else if(cur->key == k) {
            return cur;
        }
        else {
            if(k < cur->key) {
                cur->leftChild++;
                return pseudopositives(cur->left, k);
            }
            else {
                cur->rightChild++;
               return pseudopositives(cur->right, k);
            }
        }

    }

    nodes<keytype, valuetype>* TreeMax(nodes<keytype, valuetype>* cur) {
        while(cur->right != nil) {
            cur->rightChild--;
            cur = cur->right;
        }
        return cur;
    }

    void Transplant(nodes<keytype, valuetype>* u, nodes<keytype, valuetype>* v) {
        if(u->parent == nil) {
            root = v;
        }
        else if(u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteFixup(nodes<keytype, valuetype>* x) {
        while(x != root && x->color == "black") {
            if(x == x->parent->left) {
                nodes <keytype, valuetype>* w = x->parent->right;
                if(w->color == "red") {
                    w->color = "black";
                    x->parent->color = "red";
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == "black" && w->right->color == "black") {
                    w->color = "red";
                    x = x->parent;

                }
                else if(w->right->color == "black") {
                    w->left->color = "black";
                    w->color = "red";
                    rightRotate(w);
                    w = x->parent->right;
                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->right->color = "black";
                    leftRotate(x->parent);
                    x = root;
                }
                else {
                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->right->color = "black";
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                nodes <keytype, valuetype>* w = x->parent->left;
                if(w->color == "red") {
                    w->color = "black";
                    x->parent->color = "red";
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if(w->left->color == "black" && w->right->color == "black") {
                    w->color = "red";
                    x = x->parent;

                }
                else if(w->left->color == "black") {
                    w->right->color = "black";
                    w->color = "red";
                    leftRotate(w);
                    w = x->parent->left;
                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->left->color = "black";
                    rightRotate(x->parent);
                    x = root;
                }
                else {
                    w->color = x->parent->color;
                    x->parent->color = "black";
                    w->left->color = "black";
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = "black";
    }

    void clearAll(nodes<keytype, valuetype>* cur) {
        if(cur == nil) {
            return;
        }
        // cout << cur->key << " ";
       nodes<keytype, valuetype>* tempL = cur->left;
       nodes<keytype, valuetype>* tempR = cur->right;
        clearAll(tempL);
        clearAll(tempR);
        delete cur;
    }

    void clear() {
        nodes<keytype, valuetype>* cur = root;
        clearAll(cur);
        delete nil;
    }


public: 
    RBTree() {
        nil = new nodes<keytype, valuetype>();
        nil->color = "black";
        nil->leftChild = -1;
        nil->rightChild = -1;
        root = nil;
        count = 0;
    }

    RBTree(keytype *k, valuetype* V, int s) {
        nil = new nodes<keytype, valuetype>();
        nil->color = "black";
        nil->leftChild = -1;
        nil->rightChild = -1;
        root = nil;
        count = 0;
        int isOrdered;
        isOrdered = checkOrdered(k, s);
        // cout << "isOrdered:" << isOrdered << endl; //
        if(isOrdered == 0) {
            for(int i = 0; i < s; i++) {
                insert(k[i], V[i]);
            }
        }
        else {
            int height = checkPerfect(s);
            sortedInsertion(k, V, 0, s-1, height, 0);
        }
    }

    ~RBTree() {
        clear();
    }

    RBTree& operator=(const RBTree& src) {
        if(this != &src) {
            clear();
            nil = new nodes<keytype, valuetype>();
            nil->color = "black";
            nil->leftChild = -1;
            nil->rightChild = -1;
            root = nil;
            count = 0;
            nodes<keytype, valuetype>* snil = src.nil;
            nodes<keytype, valuetype>* cur = src.root;//new NIL
            spreOrderTraversalOrdered(cur, src.nil);
        }
        return* this;
    }

    RBTree(const RBTree& src) {
        nil = new nodes<keytype, valuetype>();
        nil->color = "black";
        nil->leftChild = -1;
        nil->rightChild = -1;
        root = nil;
        count = 0;
        nodes<keytype, valuetype>* snil = src.nil;
        nodes<keytype, valuetype>* cur = src.root;
        spreOrderTraversalOrdered(cur, snil);
    }


    void insert(keytype k, valuetype v) {
        nodes<keytype, valuetype>* z = new nodes<keytype,valuetype>(k, v, "NA", 0, 0);
        nodes<keytype, valuetype>* y = nil;
        nodes<keytype, valuetype>* x = root;

        while(x != nil) {
            y = x;
            if(z->key < x->key) {
                (x->leftChild)++;
                x = x->left;
            
            }
            else {
                (x->rightChild)++;
                x = x->right;
            }
        }
        z->parent = y;
        if(y == nil) {
            root = z;
        }
        else if(z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = "red";
        count++;
        insertFixup(z);
    }
    

    int remove(keytype k) {
        string originalColor;
        nodes<keytype,valuetype>* cur = root;
        nodes<keytype, valuetype>* x;
        nodes<keytype, valuetype>* y;
        nodes<keytype,valuetype>* z = pseudonegatives(cur, k);
        if(z == nil) {
            cur = root;
            pseudopositives(cur, k);
            return 0;
        }
        else {
            y = z;
            originalColor = y->color;
            if(z->left == nil) {
                x = z->right;
                Transplant(z, z->right);
            }
            else if(z->right == nil) {
                x = z->left;
                Transplant(z, z->left);
            }
            else {
                z->leftChild--;
                y = TreeMax(z->left);
                originalColor = y->color;
                x = y->left;
                if(y->parent == z) {
                    x->parent = y;
                }
                else {
                    Transplant(y, y->left);
                    y->left = z->left;
                    y->left->parent = y;
                }
                Transplant(z, y);
                y->right = z->right;
                y->right->parent = y;
                y->color = z->color;
                y->leftChild = z->leftChild;
                y->rightChild = z->rightChild;
            }

        }
        count--;
        delete z;
        if(originalColor == "black") {
            deleteFixup(x);
        }
        return 1;
    }

    valuetype* search(keytype k) {
        nodes<keytype, valuetype>* cur = root;
        nodes<keytype, valuetype>* temp = nodeSearch(cur, k);
        valuetype* r = NULL;
        if(temp == nil) {
            // cout << "didnt find the key" << endl; //remove
            return NULL;
        }
        else {
            // cout << "found" << endl; //remove
            r = &(temp->value);
            return r;
        }
    }

    int rank(keytype k) {
        nodes<keytype, valuetype>* cur = root;
        int rank = 1;

        while(1) {
            if(cur == nil) {
                return 0;
            }
            else if(cur->key == k) {
                rank = rank + cur->leftChild;
                break;
            }
            else if(cur->key < k) {
                rank = rank + cur->leftChild;
                cur = cur->right;
                rank++;
            }
            else {
                cur = cur->left;
            }
        }
        return rank;

    }

    
    keytype select(int pos) {
        nodes<keytype, valuetype>* cur = root;
        if(pos < 1 || pos > count || root == nil) {
            cout << "Invalid position" << endl;
            return nil->key;
        }
        else {
            while(1) {
                int x = 1;
                x = x + cur->leftChild; 
                // countLeft(cur->left, &x);
                if(pos == x) {
                    break;
                }
                else if(pos > x) {
                    pos = pos - x;
                    cur = cur->right;
                }
                else {
                    cur = cur->left;
                }
            }
        
        }
        return cur->key;
    }


    keytype* successor(keytype k) {
        int x = rank(k);
        if(x == 0) {
            // cout << "no key found, code will seg fault if you try to print the value" << endl;
            return NULL;
        }
        x++;
        nodes<keytype, valuetype>* temp = NULL;
        keytype* r = NULL;
        temp = selectChad(x);
        if(temp == nil) {
            // cout << "no successor, code will seg fault if you try to print the value" << endl;
            return NULL;
        }
        else { 
            r = &(temp->key);
            return r;
        }
    }

    keytype* predecessor(keytype k) {
        int x = rank(k);
        if(x == 0) {
            // cout << "no key found, code will seg fault if you try to print the value" << endl;
            return NULL;
        }
        x--;
        nodes<keytype, valuetype>* temp = NULL;
        keytype* r = NULL;
        temp = selectChad(x);
        if(temp == nil) {
            // cout << "no predecessor, code will seg fault if you try to print the value" << endl;
            return NULL;
        }
        else { 
            r = &(temp->key);
            return r;
        }
    }


    void inorder() {
        nodes<keytype, valuetype>* cur = root;
        inOrderTraversalOrdered(cur);
        cout << endl;
    }
    
    void preorder() {
        nodes<keytype, valuetype>* cur = root;
        preOrderTraversalOrdered(cur);
        cout << endl;
    }
    
    void postorder() {
        nodes<keytype, valuetype>* cur = root;
        postOrderTraversalOrdered(cur);
        cout << endl;
    }


    int size() {
        return count;
    }
};

