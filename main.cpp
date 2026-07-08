#include <iostream>
#include <fstream>
using namespace std;

struct Student {
    int id;
    char name[50];
    float marks;
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "Enter ID: ";
    cin >> s.id;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "Student Added!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        cout << "\nID: " << s.id;
        cout << "\nName: " << s.name;
        cout << "\nMarks: " << s.marks << endl;
    }

    file.close();
}

void searchStudent() {
    int id;
    Student s;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\nFound!";
            cout << "\nName: " << s.name;
            cout << "\nMarks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found) cout << "Student not found!";
    file.close();
}

void updateStudent() {
    int id;
    Student s;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new name: ";
            cin >> s.name;
            cout << "Enter new marks: ";
            cin >> s.marks;

            int pos = file.tellg() - sizeof(s);
            file.seekp(pos);

            file.write((char*)&s, sizeof(s));
            cout << "Updated!\n";
            break;
        }
    }

    file.close();
}

void deleteStudent() {
    int id;
    Student s;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Deleted if existed.\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
