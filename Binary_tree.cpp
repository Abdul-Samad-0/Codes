#include <iostream>
using namespace std;
#include <queue>
#include <stack>
class BT;
class Node {

    int data;
    Node* right;
    Node* left;

public:
    Node(int data) {
        this->data = data;
        this->right = this->left = NULL;
    }
    friend class BT;
};
class BT {
    Node* root;

public:
    // Constructor of the BST
    BT() {
        root = NULL;
        cout << "BST default constructor called" << endl;
    }

    // Insert the data in the BST
    Node* insert(Node* temp, int data) {
        if (temp == nullptr) {
            temp = new Node(data);
            return temp;
        }
        else if (temp->data > data) {
            temp->left = insert(temp->left, data);
        }
        else {
            temp->right = insert(temp->right, data);
        }
        return temp;
    }

    // void Insert pass by reference of root
    void insert2(Node*& root, int data) {
        if (root == nullptr) {
            cout << data << "  data is inserted in the BST" << endl;

            Node* temp1 = new Node(data);
            root = temp1;
        }
        else {
            if (root->data > data) {
                insert2(root->left, data);
            }
            else {
                insert2(root->right, data);
            }
        }
    }

    // wapper function to insert the data in the BST
    void _insert(int data) {
        // root=insert(root, data);
        insert2(root, data);
    }

    // Search the data in the BST
    bool search(int value) {
        Node* temp = root;
        while (temp != nullptr) {
            if (temp->data == value) {
                return true;
            }
            else if (temp->data > value) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return false;
    }
    // Insert node in Binary Tree (Level Order)
    Node* insertNode(Node* root, int value) {
        if (!root) {
            Node* temp = new Node(value);
            return root = temp;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            if (!temp->left) {
                temp->left = new Node(value);
                break;
            }
            else {
                q.push(temp->left);
            }
            if (!temp->right) {
                temp->right = new Node(value);
                break;
            }
            else {
                q.push(temp->right);
            }
        }

        return root;
    }
    void insert_Node(int val) {
        root = insertNode(root, val);
    }

    // level order traversal of the BT
    void level_order(Node*& root) {

        if (root == nullptr) {
            return;
        }
        else {
            int level = 1;
            queue<Node*> q;
            q.push(root);
            while (!q.empty()) {
                for (int i = q.size(); i > 0; i--) {
                    Node* temp = q.front();
                    q.pop();
                    cout << temp->data << "  ";
                    if (temp->left) {
                        q.push(temp->left);
                    }
                    if (temp->right) {
                        q.push(temp->right);
                    }
                }
                cout << "level " << level << endl;
                level++;
            }
        }
    }
    // zigzag print of the BT
    void f(Node*& root) {
        if (root == nullptr) {
            return;
        }
        else {
            queue<Node*> q;
            stack<Node*> s;
            q.push(root);
            int level = 1;
            while (!q.empty() || !s.empty()) {
                if (level % 2 != 0) {
                    for (int i = q.size(); i > 0; i--) {
                        Node* temp = q.front();
                        q.pop();
                        cout << temp->data << "  ";
                        if (temp->left) {
                            s.push(temp->left);
                        }
                        if (temp->right) {
                            s.push(temp->right);
                        }
                    }
                    cout << "level " << level << endl;
                    level++;
                }

                else {

                    for (int i = s.size(); i > 0; i--) {
                        Node* temp = s.top();
                        s.pop();
                        cout << temp->data << "  ";
                        if (temp->right) {
                            q.push(temp->right);
                        }
                        if (temp->left) {
                            q.push(temp->left);
                        }
                    }
                    while (!q.empty()) {
                        s.push(q.front());
                        q.pop();
                    }
                    while (!s.empty()) {
                        q.push(s.top());
                        s.pop();
                    }
                    cout << "level " << level << endl;
                    level++;
                }
            }
        }
    }

    // wapper  function to level order traversal of the BT
    void _level_order() { level_order(root); }
    // Inorder traversal of the BST
    void _inorder(Node* temp) {
        if (temp == nullptr) {
            return;
        }
        _inorder(temp->left);
        cout << temp->data << "  ";
        _inorder(temp->right);
    }
    void get_root() { f(root); }
    bool W(Node*& temp) {
        if (temp) {
            W(temp->left);
            if (temp->left) {
                if (temp->data < temp->left->data) {
                    return false;
                }
            }
            if (temp->right) {
                if (temp->data > temp->right->data) {
                    return false;
                }
            }
            W(temp->right);
        }
        else {
            return true;
        }
        return true;
    }
    bool is_valid_bst() { return W(root); }
    Node* helper2(Node*& t) {

        if (t != nullptr) {
            if (t->left == nullptr) {
                return t;
            }
        }
        return helper2(t->left);
    }
    void helper() {
        Node* leaf = helper2(root);
        cout << leaf->data << endl;
        leaf->left = new Node(56);
    }
    // Make a balance_bst from the sorted array
    void balance_bst(int arr[], int i, int size) {
        if (i < size) {
            int mid = ((i + size) - 1) / 2;
            this->_insert(arr[mid]);
            balance_bst(arr, i, mid);
            balance_bst(arr, mid + 1, size);
        }
    }

    void fun1(Node*& root, queue<Node*>& b1) {
        if (root == nullptr) {
            return;
        }
        fun1(root->left, b1);
        b1.push(root);
        fun1(root->right, b1);
    }
    void check() {
        queue<Node*> b1;
        queue<Node*> sw;
        fun1(root, b1);
        while (((b1.size()) - 1)) {
            Node* a = b1.front();
            b1.pop();
            Node* b = b1.front();
            if (a->data > b->data) {
                if (sw.empty()) {
                    sw.push(a);
                }
                else {
                    sw.push(b);
                }
            }
        }
        // Node pointer values swap
        if (!sw.empty()) {
            Node* c = sw.front();
            sw.pop();
            Node* d = sw.front();
            int temp = c->data;
            c->data = d->data;
            d->data = temp;
        }
    }
    // wapper function to Inoder traversal of the BST
    void inorder() { _inorder(root); }
    // left most and right most data are swapped by mistake in the BST
    void left_most() {
        Node* temp1 = root;
        Node* temp = root;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        while (temp1->right != nullptr) {
            temp1 = temp1->right;
        }
        int t = temp->data;
        temp->data = temp1->data;
        temp1->data = t;
    }
    // check T2 is subtree of T1 or not
    bool subtree(Node*& root, Node*& root1) {
        if (root == nullptr && root1 == nullptr) {
            return true;
        }
        if (root == nullptr || root1 == nullptr) {
            return false;
        }
        if (root->data == root1->data) {
            return subtree(root->left, root1->left) &&
                subtree(root->right, root1->right);
        }
        return subtree(root->left, root1) || subtree(root->right, root1);
    }

    void ff(Node* root) {
        cout << subtree(this->root, root);
    }


    Node* _root() {
        return root;
    }


    // profitable path in a tree
    int find_max_sum(Node* root, int sum, int& max_sum) {
        if (root == nullptr) {
            return 0;
        }
        int left = find_max_sum(root->left, sum, max_sum);
        int right = find_max_sum(root->right, sum, max_sum);
        int temp = left + right + root->data;
        int temp2 = 0;
        if (left > right) {
            temp2 = left + root->data;
        }
        else { temp2 = right + root->data; }
        int temp3 = root->data;
        if (temp > temp2) {
            if (temp > temp3) {
                max_sum = temp;
            }
            else {
                max_sum = temp3;
            }
        }
        else {
            if (temp2 > temp3) {
                max_sum = temp2;
            }
            else { max_sum = temp3; }
        }
        return max_sum;
    }
};

int main() {
    BT b1;
    cout << "First binary_Search Tree\n\n";
    b1._insert(50);
    b1._insert(30);
    b1._insert(70);
    b1._insert(20);
    //  b1._insert(10);
    b1._insert(25);
    b1._insert(15);
    b1._insert(5);
    // b1._insert(35);
    b1._insert(80);
    b1._insert(75);
    b1._insert(60);
    b1._insert(65);
    // b1.inorder();
    //  b1.__delete(15);
    cout << "\n\n";
    if (b1.search(75)) {
        cout << "data  is present in bst \n";
    }
    else {
        cout << "data is not present in bst\n";
    }
    cout << "\n\n";
    cout << "inorder print of the BST \n";
    b1.inorder();
    cout << "\n\n";
    cout << "level order print of  BST\n";
    b1._level_order();
    cout << "\n\n" << endl;
    cout << "Zigzag print of level's\n";
    b1.get_root();
    cout << "\nSec Binary_Search Tree\n\n";
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    BT b2;
    cout << endl;
    cout << "balance bst from the sorted array\n";
    b2.balance_bst(arr, 0, 7);
    b2._level_order();
    cout << "\n any two nodes are swapped by mistake in the BST \n";
    b2.left_most();
    b2.inorder();
    cout << "\ninorder print of bst\n";
    b2.check();
    b2.inorder();
    cout << "Binary Tree \n\n\n";

    BT b3;
    cout << "Enter the data for the BT\n";
    b3.insert_Node(7);
    b3.insert_Node(8);
    b3.insert_Node(1);
    b3.insert_Node(1);
    b3.insert_Node(-48);
    b3.insert_Node(18);
    b3._level_order();
    int max_sum = 0;
    b3.find_max_sum(b3._root(), 0, max_sum);
    cout << "\n max_sum of path\n" << max_sum << endl;
}