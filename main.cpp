#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
};

const string kDataFile = "students.txt";

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream inFile(kDataFile);

    if (!inFile.is_open()) {
        return students;
    }

    Student student{};
    while (inFile >> student.id >> quoted(student.name) >> student.age >> quoted(student.course)) {
        students.push_back(student);
    }

    return students;
}

bool saveStudents(const vector<Student>& students) {
    ofstream outFile(kDataFile, ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }

    for (const auto& student : students) {
        outFile << student.id << ' ' << quoted(student.name) << ' ' << student.age << ' ' << quoted(student.course) << '\n';
    }

    return true;
}

int findStudentIndexById(const vector<Student>& students, int id) {
    for (int i = 0; i < static_cast<int>(students.size()); ++i) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid number. Please try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

void addStudent(vector<Student>& students) {
    cout << "\n--- Add Student ---\n";
    int id = readInt("Enter ID: ");

    if (findStudentIndexById(students, id) != -1) {
        cout << "A student with this ID already exists.\n";
        return;
    }

    Student student{};
    student.id = id;
    student.name = readLine("Enter name: ");
    student.age = readInt("Enter age: ");
    student.course = readLine("Enter course: ");

    students.push_back(student);

    if (saveStudents(students)) {
        cout << "Student added successfully.\n";
    } else {
        cout << "Failed to save data.\n";
    }
}

void viewStudents(const vector<Student>& students) {
    cout << "\n--- Student Records ---\n";

    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    cout << left << setw(8) << "ID" << setw(25) << "Name" << setw(8) << "Age" << "Course\n";
    cout << string(60, '-') << '\n';

    for (const auto& student : students) {
        cout << left << setw(8) << student.id << setw(25) << student.name << setw(8) << student.age << student.course << '\n';
    }
}

void updateStudent(vector<Student>& students) {
    cout << "\n--- Update Student ---\n";
    int id = readInt("Enter ID to update: ");

    int index = findStudentIndexById(students, id);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Leave field empty to keep current value.\n";

    string newName = readLine("Enter new name (current: " + students[index].name + "): ");
    string ageInput = readLine("Enter new age (current: " + to_string(students[index].age) + "): ");
    string newCourse = readLine("Enter new course (current: " + students[index].course + "): ");

    if (!newName.empty()) {
        students[index].name = newName;
    }

    if (!ageInput.empty()) {
        try {
            students[index].age = stoi(ageInput);
        } catch (...) {
            cout << "Invalid age input. Keeping previous age.\n";
        }
    }

    if (!newCourse.empty()) {
        students[index].course = newCourse;
    }

    if (saveStudents(students)) {
        cout << "Student updated successfully.\n";
    } else {
        cout << "Failed to save data.\n";
    }
}

void deleteStudent(vector<Student>& students) {
    cout << "\n--- Delete Student ---\n";
    int id = readInt("Enter ID to delete: ");

    int index = findStudentIndexById(students, id);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students.erase(students.begin() + index);

    if (saveStudents(students)) {
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Failed to save data.\n";
    }
}

void showMenu() {
    cout << "\n===== Student Management System =====\n";
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Update Student\n";
    cout << "4. Delete Student\n";
    cout << "5. Exit\n";
}

int main() {
    vector<Student> students = loadStudents();

    while (true) {
        showMenu();
        int choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3:
                updateStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please select between 1 and 5.\n";
                break;
        }
    }
}
