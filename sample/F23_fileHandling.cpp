#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store student information
struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

// Function to add a student record to the file
void addStudentRecord() {
    ofstream file("students.txt", ios::app); // Open the file in append mode

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    file << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;

    file.close();
    cout << "Student record added successfully!" << endl;
}

// Function to delete a student record from the file
void deleteStudentRecord() {
    ifstream inFile("students.txt"); // Open the file for reading
    ofstream outFile("temp.txt"); // Open a temporary file for writing

    int rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        Student student;
        size_t pos = line.find(",");
        student.rollNumber = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(",");
        student.name = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        student.division = line.substr(0, pos);
        line.erase(0, pos + 1);
        student.address = line;

        if (student.rollNumber != rollNumber) {
            outFile << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.txt"); // Delete the original file
    rename("temp.txt", "students.txt"); // Rename the temporary file to the original file name

    if (found) {
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student record not found!" << endl;
    }
}

// Function to display information of a particular student
void displayStudentInfo() {
    ifstream file("students.txt");

    int rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;

    bool found = false;
    string line;
    while (getline(file, line)) {
        Student student;
        size_t pos = line.find(",");
        student.rollNumber = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(",");
        student.name = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        student.division = line.substr(0, pos);
        line.erase(0, pos + 1);
        student.address = line;

        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Student record not found!" << endl;
    }
}

// Function to display all student records in sequential order according to roll number
void displayRecordsSequentially() {
    ifstream file("students.txt");

    vector<Student> students;
    string line;
    while (getline(file, line)) {
        Student student;
        size_t pos = line.find(",");
        student.rollNumber = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(",");
        student.name = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        student.division = line.substr(0, pos);
        line.erase(0, pos + 1);
        student.address = line;

        students.push_back(student);
    }

    file.close();

    // Sort the student records by roll number
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.rollNumber < b.rollNumber;
    });

    // Display the sorted student records
    for (const Student& student : students) {
        cout << "Roll Number: " << student.rollNumber << endl;
        cout << "Name: " << student.name << endl;
        cout << "Division: " << student.division << endl;
        cout << "Address: " << student.address << endl;
        cout << endl;
    }
}

int main() {
    while (true) {
        cout << "Student Information System Menu:" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Delete Student Record" << endl;
        cout << "3. Search Student Information" << endl;
        cout << "4. Display Records Sequentially (by Roll Number)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addStudentRecord();
                break;
            case 2:
                deleteStudentRecord();
                break;
            case 3:
                displayStudentInfo();
                break;
            case 4:
                displayRecordsSequentially();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    }
}