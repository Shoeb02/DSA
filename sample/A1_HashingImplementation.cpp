/*
Problem Statement(hashing) :=Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use of two collision
handling techniques and compare them using number of comparisons required to find a
set of telephone numbers.
*/

#include <bits/stdc++.h>

using namespace std;
class node
{
public:
    long long data;
    node *next;
};
class LinearProbing
{
public:
    int hashtable[10];

    LinearProbing()
    {
        for (int i = 0; i < 10; i++)
        {
            hashtable[i] = -1;
        }
    }
    void insert()
    {
        int key;
        cout << "Enter element to insert :" << endl;
        cin >> key;
        int loc = key % 10;
        for (int i = 0; i < 10; i++)
        {
            if (hashtable[loc] == -1)
            {
                hashtable[loc] = key;
                break;
            }
            else
            {

                loc = (loc + 1) % 10;
            }
        }
    }
    void display()
    {

        for (int i = 0; i < 10; i++)
        {
            if (hashtable[i] == -1)
            {
                cout << "--" << endl;
            }
            else
            {
                cout << hashtable[i] << endl;
            }
        }
    }
    void search()
    {
        int key;
        cout << "Enter element to search :" << endl;
        cin >> key;
        int loc = key % 10;
        bool flag = false;
        int count = 0;
        for (int i = 0; i < 10; i++)
        {
            if (hashtable[loc] == key)
            {
                count++;
                flag = true;
                break;
            }
            else
            {
                count++;
                loc = (loc + 1) % 10;
            }
        }

        if (flag)
        {
            cout << "element Found !" << endl;
            cout << "No of comparisions required :" << count << endl;
        }
        else
        {
            cout << "Element not found ! " << endl;
        }
    }
};
class OpenAdd
{

    node *hashtable[10];

public:
    OpenAdd()
    {

        for (int i = 0; i < 10; i++)
        {
            hashtable[i] = NULL;
        }
    }

    void insert()
    {
        long long key;
        cout << "Enter value to be inserted : " << endl;
        cin >> key;
        int loc = key % 10;
        node *p = new node();
        p->data = key;
        p->next = NULL;

        if (hashtable[loc] == NULL)
        {
            hashtable[loc] = p;
        }
        else
        {
            node *temp = hashtable[loc];

            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = p;
        }
    }
    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            node *temp = hashtable[i];
            if (temp == NULL)
            {
                cout << "0" << endl;
            }
            else
            {
                while (temp != NULL)
                {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
                cout << endl;
            }
        }
    }
    void search()
    {
        bool found = false;
        long long element;
        cout << "Enter element to be search :" << endl;
        cin >> element;

        int loc = element % 10;
        int count=0;
        node *temp = hashtable[loc];
        if (temp == NULL)
        {
            cout << "Element not found" << endl;
        }
        else
        {
            while (temp != NULL)
            {
                if (temp->data == element)
                {
                    count++;

                    found = true;
                    break;
                }

                temp = temp->next;
            }
            if (found)
            {
                cout << "Element found" << endl;
                cout << "No of comparisions required :" << count << endl;
            }
            else
            {
                cout << "Element not found" << endl;
            }
        }
    }
};

int main()
{
    LinearProbing h1;
    OpenAdd h2;

    int ch;

    cout << "Enter your choice between following : " << endl;
    cout << "\n1.Linear Probbing\n2.Quadratic Probing" << endl;
    cin >> ch;

    switch (ch)
    {
    case 1:

        cout << "1.Insert\n2.Display\n3.search\n4.Exit\n";
        while (1)
        {
            int ch1;

            cout << "Enter your choice :" << endl;
            cin >> ch1;
            switch (ch1)
            {
            case 1:
                h1.insert();
                break;
            case 2:
                h1.display();
                break;
            case 3:
                h1.search();
                break;
            case 4:
                exit(1);

                break;
            default:
                cout << "Enter valid choice" << endl;
            }
        }

    case 2:

        cout << "1.Insert\n2.Display\n3.search\n4.Exit";
        while (1)
        {
            int ch2;

            cout << "Enter your choice :" << endl;
            cin >> ch2;
            switch (ch2)
            {
            case 1:
                h2.insert();
                break;
            case 2:
                h2.display();
                break;
            case 3:
                h2.search();
                break;
            case 4:
                exit(1);

                break;
            default:
                cout << "Enter valid choice" << endl;
            }
        }
    }

        return 0;
    }
