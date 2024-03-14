#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};


Node* insert(Node* root, int value) {
    
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}


Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}


Node* remove(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = remove(root->left, value);
    } else if (value > root->data) {
        root->right = remove(root->right, value);
    } else {
        
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

       
        Node* temp = findMin(root->right);
        root->data = temp->data;    
        root->right = remove(root->right, temp->data);
    }
    return root;
}


bool search(Node* root, int value) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == value) {
        return true;
    } else if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}


void printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int nodesAtCurrentLevel = q.size();

        while (nodesAtCurrentLevel > 0) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }

            if (current->right != nullptr) {
                q.push(current->right);
            }

            nodesAtCurrentLevel--;
        }

        cout << endl;
    }
}

int main() {
    Node* root = nullptr;
    int value;

   
    cout << "Enter values to insert into the binary search tree (between 1 and 999, enter -1 to stop):" << endl;
    while (true) {
        cout << "Enter value: ";
        cin >> value;
        if (value == -1) {
            break;
        }
        root = insert(root, value);
    }

    
    cout << "Binary Search Tree:" << endl;
    printLevelOrder(root);
    cout << endl;

    
    int searchValue;
    cout << "Enter a value to search in the tree: ";
    cin >> searchValue;
    if (search(root, searchValue)) {
        cout << searchValue << " is in the tree." << endl;
    } else {
        cout << searchValue << " is not in the tree." << endl;
    }

  
    int removeValue;
    cout << "Enter a value to remove from the tree: ";
    cin >> removeValue;
    root = remove(root, removeValue);
    cout << "After removing " << removeValue << ":" << endl;
    printLevelOrder(root);
    cout << endl;

    return 0;
}
