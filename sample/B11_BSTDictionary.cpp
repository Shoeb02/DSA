
/*
Problem statement(BST_dict) :=
A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to display
whole data sorted in ascending/ Descending order. Also find how many maximum
comparisons may require for finding any keyword. Use Binary Search Tree for
implementation.

*/

#include <bits/stdc++.h>
using namespace std;
class Node
{

public:
    string key;
    string mean;
    Node *left;
    Node *right;
    Node(string k, string m)
    {
        key = k;
        mean = m;
        left = NULL;
        right = NULL;
    }
};
class BST
{
public:
    Node *insertToBst(Node *root, string keyW, string meaning)
    {

        if (root == NULL)
        {
            root = new Node(keyW, meaning);
            return root;
        }

        if (keyW > root->key)
        {

            root->right = insertToBst(root->right, keyW, meaning);
            return root;
        }
        else
        {

            root->left = insertToBst(root->left, keyW, meaning);
            return root;
        }
    }

    void create(Node *&root)
    {
        string keyW;
        string meaning;
        cout << "Enter keyword to insert in BST (if not enter -1) : " << endl;
        cin >> keyW;
        cout << "Enter meaning of above keyword (if not enter -1) :" << endl;
        cin >> meaning;
        while (keyW != "-1" && meaning != "-1")
        {

            root = insertToBst(root, keyW, meaning);
            cout << "Enter keyword to insert in BST (if not enter -1) : " << endl;
            cin >> keyW;
            cout << "Enter meaning of above keyword (if not enter -1) :" << endl;
            cin >> meaning;
        }
    }
    void Display(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        Display(root->left);
        cout << root->key << ":" << root->mean << " ";
        Display(root->right);
    }
    Node *search(Node *root, string keyW)
    {

        if (root == NULL)
            return NULL;
        if (root->key == keyW)
            return root;

        if (root->key < keyW)
            return search(root->right, keyW);

        else
        {

            return search(root->left, keyW);
        }
    }
    void update(Node *root)
    {

        Node *p;
        string k;
        string newMeaning;
        cout << "Enter which key meaning to update :" << endl;
        cin >> k;
        p = search(root, k);
        if (p == NULL)
            cout << "\nElement not present in BST";
        else
        {

            cout << "Enter new meaning  : " << endl;
            cin >> newMeaning;
            p->mean = newMeaning;
        }
    }
    Node* minValue(Node *root)
    {
        Node *temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    Node *deleteKey(Node *root,string val)
    {
        
        if (root == NULL)
        {
            return root;
        }
        if (root->key == val)
        {
            // 0 child
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }

            // 1 child
            // left Child
            if (root->left != NULL && root->right == NULL)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            // right child
            if (root->left == NULL && root->right != NULL)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }

            // 2 child
            if (root->left != NULL && root->right != NULL)
            {
                string mini = minValue(root->right)->key;
                root->key = mini;
                root->right = deleteKey(root->right, mini);
                return root;
            }
        }
        else if (root->key > val)
        {
            // left part me jao
            root->left = deleteKey(root->left, val);
            return root;
        }
        else
        {
            // right part me jao
            root->right = deleteKey(root->right, val);
            return root;
        }
    }
};

int main()
{
    BST b;
    string key;
    Node *root = NULL;
    Node *p;
    string val;
    int ch;
    cout << "**********MENU**********" << endl;
    cout << "\n1.Create\n2.Display\n3.Search\n4.update\n5.Delete Key\n6.exit\n";
    while (1)
    {
        cout << "\nEnter a choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:

            b.create(root);
            break;
        case 2:
            b.Display(root);
            break;
        case 3:
            cout << "\nEnter key to be searched : ";
            cin >> key;
            p = b.search(root, key);
            if (p == NULL)
                cout << "\nElement not found";
            else
                cout << "\nElement found :" << p->key;
            break;

        case 4:
            b.update(root);
            break;
        case 5:
             
            cout << "Enter which key  to delete :" << endl;
            cin >> val;
            b.deleteKey(root,val);
            break;

        case 6:
            exit(1);
        }
    }
    return 0;
}
