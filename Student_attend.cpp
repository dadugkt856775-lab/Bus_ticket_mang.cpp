
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    int totalClasses;
    int presentClasses;

    Student(int roll, string studentName) {
        rollNumber = roll;
        name = studentName;
        totalClasses = 0;
        presentClasses = 0;
    }

    double getAttendancePercentage() const {
        if (totalClasses == 0)
            return 0.0;

        return (presentClasses * 100.0) / totalClasses;
    }

    void display() const {
        cout << left << setw(12) << rollNumber
             << setw(22) << name
             << setw(15) << presentClasses
             << setw(15) << totalClasses
             << fixed << setprecision(2)
             << getAttendancePercentage() << "%\n";
    }
};

class AttendanceSystem {
private:
    vector<Student> students;

    int findStudentIndex(int roll) const {
        for (int i = 0; i < (int)students.size(); i++) {
            if (students[i].rollNumber == roll)
                return i;
        }
        return -1;
    }

public:
    void addStudent() {
        int roll;
        string name;

        cout << "\nEnter roll number: ";
        cin >> roll;

        if (findStudentIndex(roll) != -1) {
            cout << "Roll number already exists!\n";
            return;
        }

        cout << "Enter student name: ";
        getline(cin >> ws, name);

        students.emplace_back(roll, name);
        cout << "Student added successfully!\n";
    }

    void markAttendance() {
        if (students.empty()) {
            cout << "\nNo students registered.\n";
            return;
        }

        int roll;
        char status;

        cout << "\nEnter roll number: ";
        cin >> roll;

        int index = findStudentIndex(roll);

        if (index == -1) {
            cout << "Student not found!\n";
            return;
        }

        cout << "Enter P for Present or A for Absent: ";
        cin >> status;

        if (status == 'P' || status == 'p') {
            students[index].presentClasses++;
            students[index].totalClasses++;
        } else if (status == 'A' || status == 'a') {
            students[index].totalClasses++;
        } else {
            cout << "Invalid attendance status!\n";
            return;
        }

        cout << "Attendance marked successfully!\n";
    }

    void searchStudent() const {
        int roll;

        cout << "\nEnter roll number to search: ";
        cin >> roll;

        int index = findStudentIndex(roll);

        if (index == -1) {
            cout << "Student not found!\n";
            return;
        }

        cout << "\nStudent Attendance Details\n";
        cout << "Roll Number: " << students[index].rollNumber << endl;
        cout << "Name: " << students[index].name << endl;
        cout << "Classes Attended: "
             << students[index].presentClasses << endl;
        cout << "Total Classes: "
             << students[index].totalClasses << endl;
        cout << fixed << setprecision(2);
        cout << "Attendance: "
             << students[index].getAttendancePercentage()
             << "%\n";
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "\nNo students registered.\n";
            return;
        }

        cout << "\n========== ATTENDANCE REPORT ==========\n";
        cout << left << setw(12) << "Roll No."
             << setw(22) << "Name"
             << setw(15) << "Present"
             << setw(15) << "Total"
             << "Percentage\n";

        for (const Student& student : students)
            student.display();
    }

    void showDefaulters() const {
        const double minimumAttendance = 75.0;
        bool found = false;

        cout << "\nStudents Below 75% Attendance\n";

        for (const Student& student : students) {
            if (student.totalClasses > 0 &&
                student.getAttendancePercentage() < minimumAttendance) {
                student.display();
                found = true;
            }
        }

        if (!found)
            cout << "No attendance defaulters found.\n";
    }

    void displaySummary() const {
        int totalStudents = students.size();
        int totalPresent = 0;
        int totalClasses = 0;

        for (const Student& student : students) {
            totalPresent += student.presentClasses;
            totalClasses += student.totalClasses;
        }

        cout << "\n========== SUMMARY ==========\n";
        cout << "Registered students: " << totalStudents << endl;
        cout << "Recorded student-class sessions: "
             << totalClasses << endl;
        cout << "Present student-class sessions: "
             << totalPresent << endl;
    }

    void run() {
        int choice;

        do {
            cout << "\n===== STUDENT ATTENDANCE SYSTEM =====\n";
            cout << "1. Add Student\n";
            cout << "2. Mark Attendance\n";
            cout << "3. Search Student\n";
            cout << "4. Display All Attendance\n";
            cout << "5. Show Students Below 75%\n";
            cout << "6. Attendance Summary\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input!\n";
                break;
            }

            switch (choice) {
                case 1: addStudent(); break;
                case 2: markAttendance(); break;
                case 3: searchStudent(); break;
                case 4: displayAllStudents(); break;
                case 5: showDefaulters(); break;
                case 6: displaySummary(); break;
                case 0:
                    cout << "Exiting Attendance System...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    AttendanceSystem system;
    system.run();
    return 0;
}
