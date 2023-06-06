#include <iostream>
#include <queue>

using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}

// Function to update the height of a node
void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Function to perform a right rotation
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left rotation
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left-right rotation
Node* rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// Function to perform a right-left rotation
Node* rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// Function to insert a new keyword-meaning pair
Node* insert(Node* root, const string& keyword, const string& meaning) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->keyword = keyword;
        newNode->meaning = meaning;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 0;
        return newNode;
    }

    if (keyword < root->keyword) {
        root->left = insert(root->left, keyword, meaning);
        if (getHeight(root->left) - getHeight(root->right) == 2) {
            if (keyword < root->left->keyword) {
                root = rotateRight(root);
            } else {
                root = rotateLeftRight(root);
            }
        }
    } else if (keyword > root->keyword) {
        root->right = insert(root->right, keyword, meaning);
        if (getHeight(root->right) - getHeight(root->left) == 2) {
            if (keyword > root->right->keyword) {
                root = rotateLeft(root);
            } else {
                root = rotateRightLeft(root);
            }
        }
    } else {
        // Keyword already exists, update the meaning
        root->meaning = meaning;
    }

    updateHeight(root);
    return root;
}

// Function to delete a keyword
Node* remove(Node* root, const string& keyword) {
    if (root == nullptr) {
        return nullptr;
    }

    if (keyword < root->keyword) {
        root->left = remove(root->left, keyword);
        if (getHeight(root->right) - getHeight(root->left) == 2) {
            if (getHeight(root->right->left) > getHeight(root->right->right)) {
                root = rotateRightLeft(root);
            } else {
                root = rotateLeft(root);
            }
        }
    } else if (keyword > root->keyword) {
        root->right = remove(root->right, keyword);
        if (getHeight(root->left) - getHeight(root->right) == 2) {
            if (getHeight(root->left->right) > getHeight(root->left->left)) {
                root = rotateLeftRight(root);
            } else {
                root = rotateRight(root);
            }
        }
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* successor = root->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            root->keyword = successor->keyword;
            root->meaning = successor->meaning;
            root->right = remove(root->right, successor->keyword);
            if (getHeight(root->left) - getHeight(root->right) == 2) {
                if (getHeight(root->left->right) > getHeight(root->left->left)) {
                    root = rotateLeftRight(root);
                } else {
                    root = rotateRight(root);
                }
            }
        }
    }

    updateHeight(root);
    return root;
}

// Function to search for a keyword
Node* search(Node* root, const string& keyword, int& comparisons) {
    if (root == nullptr || root->keyword == keyword) {
        comparisons++;
        return root;
    }

    if (keyword < root->keyword) {
        comparisons++;
        return search(root->left, keyword, comparisons);
    } else {
        comparisons++;
        return search(root->right, keyword, comparisons);
    }
}

// Function to traverse the tree in-order and display all keyword-meaning pairs
void displayInOrder(Node* root) {
    if (root == nullptr) {
        return;
    }

    displayInOrder(root->left);
    cout << root->keyword << ": " << root->meaning << endl;
    displayInOrder(root->right);
}

// Function to traverse the tree in-order and display all keyword-meaning pairs in descending order
void displayInOrderDescending(Node* root) {
    if (root == nullptr) {
        return;
    }

    displayInOrderDescending(root->right);
    cout << root->keyword << ": " << root->meaning << endl;
    displayInOrderDescending(root->left);
}

// Function to calculate the maximum number of comparisons required to find a keyword
int calculateMaxComparisons(Node* root, const string& keyword) {
    int comparisons = 0;
    search(root, keyword, comparisons);
    return comparisons;
}

int main() {
    Node* root = nullptr;

    while (true) {
        cout << "Dictionary Menu:" << endl;
        cout << "1. Add a new keyword" << endl;
        cout << "2. Delete a keyword" << endl;
        cout << "3. Update the meaning of a keyword" << endl;
        cout << "4. Display all keyword-meaning pairs (ascending order)" << endl;
        cout << "5. Display all keyword-meaning pairs (descending order)" << endl;
        cout << "6. Find a keyword" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter the keyword: ";
                string keyword;
                cin >> keyword;
                cout << "Enter the meaning: ";
                string meaning;
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                cout << "Keyword added successfully!" << endl;
                break;
            }
            case 2: {
                cout << "Enter the keyword to delete: ";
                string keyword;
                cin >> keyword;
                root = remove(root, keyword);
                cout << "Keyword deleted successfully!" << endl;
                break;
            }
            case 3: {
                cout << "Enter the keyword to update: ";
                string keyword;
                cin >> keyword;
                int comparisons = 0;
                Node* node = search(root, keyword, comparisons);
                if (node != nullptr) {
                    cout << "Enter the new meaning: ";
                    string newMeaning;
                    cin.ignore();
                    getline(cin, newMeaning);
                    node->meaning = newMeaning;
                    cout << "Meaning updated successfully!" << endl;
                } else {
                    cout << "Keyword not found!" << endl;
                }
                break;
            }
            case 4: {
                cout << "Keyword-meaning pairs (ascending order):" << endl;
                displayInOrder(root);
                break;
            }
            case 5: {
                cout << "Keyword-meaning pairs (descending order):" << endl;
                displayInOrderDescending(root);
                break;
            }
            case 6: {
                cout << "Enter the keyword to find: ";
                string keyword;
                cin >> keyword;
                int comparisons = 0;
                Node* node = search(root, keyword, comparisons);
                if (node != nullptr) {
                    cout << "Keyword found with meaning: " << node->meaning << endl;
                    cout << "Number of comparisons made: " << comparisons << endl;
                } else {
                    cout << "Keyword not found!" << endl;
                }
                break;
            }
            case 7: {
                cout << "Exiting..." << endl;
                // Clean up memory (delete the tree)
                queue<Node*> nodes;
                nodes.push(root);
                while (!nodes.empty()) {
                    Node* current = nodes.front();
                    nodes.pop();
                    if (current != nullptr) {
                        nodes.push(current->left);
                        nodes.push(current->right);
                        delete current;
                    }
                }
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

        cout << endl;
    }
}