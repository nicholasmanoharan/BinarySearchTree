#include <iostream>
#include <fstream>
#include <sstream>
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


void deleteTree(Node* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int value;
    char choice;

    cout << "Enter numbers to insert into the binary search tree (between 1 and 999, separated by a space):" << endl;
    string input;
    getline(cin, input);
    istringstream iss(input);
    while (iss >> value) {
        root = insert(root, value);
    }

    cout << "Binary Search Tree:" << endl;
    printLevelOrder(root);

    while (true) {
        cout << "\nDo you want to perform any operation? (Y/N): ";
        cin >> choice;

        if (choice == 'N' || choice == 'n') {
            break;
        }

        cout << "Choose operation: \n";
        cout << "1. Insert a number\n";
        cout << "2. Remove a number\n";
        cout << "3. Search for a number\n";
        cout << "4. Print the tree\n";
        cout << "5. Exit\n";

        int operation;
        cout << "Enter operation number: ";
        cin >> operation;

        switch (operation) {
            case 1:
                cout << "Enter the number to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter the number to remove: ";
                cin >> value;
                root = remove(root, value);
                break;
            case 3:
                cout << "Enter the number to search for: ";
                cin >> value;
                if (search(root, value)) {
                    cout << value << " is in the tree." << endl;
                } else {
                    cout << value << " is not in the tree." << endl;
                }
                break;
            case 4:
                cout << "Binary Search Tree:" << endl;
                printLevelOrder(root);
                break;
            case 5:
                cout << "Exiting...\n";
                deleteTree(root);
                return 0;
            default:
                cout << "Invalid operation!\n";
        }
    }

    deleteTree(root);
    return 0;
}
