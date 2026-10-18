#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_STUDENTS = 100;
const int SUBJECTS = 5;

string names[MAX_STUDENTS];
string ids[MAX_STUDENTS];

double grades[MAX_STUDENTS][SUBJECTS];

string subjectNames[SUBJECTS] = {
    "Math",
    "English",
    "Computer Science",
    "Physics",
    "Statistics"
};

int studentCount = 0;

// Clear the visible output area
void clearScreen() {
    cout << string(35, '\n');
}

// Read an integer within a specific range
int readInt(string message, int minValue, int maxValue) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value &&
            value >= minValue &&
            value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a number from "
             << minValue << " to " << maxValue << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a grade from 0 to 100
double readGrade(string message) {
    double grade;

    while (true) {
        cout << message;

        if (cin >> grade &&
            grade >= 0 &&
            grade <= 100) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return grade;
        }

        cout << "Invalid grade. Enter a value from 0 to 100.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a non-empty line
string readNonEmptyLine(string message) {
    string value;

    while (true) {
        cout << message;
        getline(cin, value);

        if (!value.empty()) {
            return value;
        }

        cout << "This field cannot be empty. Please try again.\n";
    }
}

// Find a student by ID
int findStudent(string id) {
    for (int i = 0; i < studentCount; i++) {
        if (ids[i] == id) {
            return i;
        }
    }

    return -1;
}

// Calculate total out of 500
double calculateTotal(int index) {
    double total = 0;

    for (int i = 0; i < SUBJECTS; i++) {
        total += grades[index][i];
    }

    return total;
}

// Calculate average out of 100
double calculateAverage(int index) {
    return calculateTotal(index) / SUBJECTS;
}

// Calculate percentage
double calculatePercentage(int index) {
    return calculateTotal(index) / (SUBJECTS * 100.0) * 100.0;
}

// Determine final status
string getStatus(int index) {
    for (int i = 0; i < SUBJECTS; i++) {
        if (grades[index][i] < 50) {
            return "FAIL";
        }
    }

    return "PASS";
}

// Display detailed results for one student
void displayStudentResult(int index) {

    cout << "               * STUDENT RESULTS *\n";


    cout << "Student Name : " << names[index] << endl;
    cout << "Student ID   : " << ids[index] << endl;

    cout << "\nSubject Grades\n";
    cout << "--------------------------------------------\n";

    int failedSubjects = 0;

    cout << fixed << setprecision(2);

    for (int i = 0; i < SUBJECTS; i++) {
        cout << left << setw(23) << subjectNames[i]
             << right << setw(8) << grades[index][i]
             << " / 100";

        if (grades[index][i] >= 50) {
            cout << "   PASS\n";
        } else {
            cout << "   FAIL\n";
            failedSubjects++;
        }
    }

    cout << "--------------------------------------------\n";
    cout << "Total      : " << calculateTotal(index) << " / 500\n";
    cout << "Average    : " << calculateAverage(index) << " / 100\n";
    cout << "Percentage : " << calculatePercentage(index) << "%\n";
    cout << "Status     : " << getStatus(index) << endl;

    if (failedSubjects > 0) {
        cout << "\nFailed Subjects:\n";

        for (int i = 0; i < SUBJECTS; i++) {
            if (grades[index][i] < 50) {
                cout << "- " << subjectNames[i]
                     << " (" << grades[index][i] << ")\n";
            }
        }

        cout << "Number of Failed Subjects: "
             << failedSubjects << endl;
    } else {
        cout << "\nAll subjects passed successfully.\n";
    }

    cout << "                                           \n";
}

// Add a new student
void addStudent() {
    cout << "                     *  ADD NEW STUDENT  * \n";
    cout<< "                      \n";

    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum student capacity reached.\n";
        return;
    }

    string id = readNonEmptyLine("Enter Student ID: ");

    while (findStudent(id) != -1) {
        cout << "This ID already exists. Please enter another ID.\n";
        id = readNonEmptyLine("Enter Student ID: ");
    }

    string name = readNonEmptyLine("Enter Student Name: ");

    ids[studentCount] = id;
    names[studentCount] = name;

    cout << "\nEnter Student grades :\n";

    for (int i = 0; i < SUBJECTS; i++) {
        grades[studentCount][i] =
            readGrade(subjectNames[i] + " (100): ");
    }

    studentCount++;


    cout << "\nStudent added successfully!\n";
cout << "Name: " << name << " | ID: " << id << endl;
}

// Display all students in a table
void displayStudents() {
    cout << "                   *  STUDENT DIRECTORY  * \n";
    cout <<"                          \n";

    if (studentCount == 0) {
        cout << "No students have been added yet.\n";
        return;
    }

    cout << left
         << setw(15) << "Student ID"
         << setw(22) << "Name"
         << setw(10) << "Total"
         << setw(10) << "Average"
         << setw(13) << "Percentage"
         << "Status\n";

    cout << string(82, '-') << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < studentCount; i++) {
        cout << left
             << setw(15) << ids[i]
             << setw(22) << names[i]
             << setw(10) << calculateTotal(i)
             << setw(10) << calculateAverage(i)
             << setw(13) << calculatePercentage(i)
             << getStatus(i) << endl;
    }

    cout << string(82, '-') << endl;
    cout << "Total Students: " << studentCount << endl;
}

// Search for a student
void searchStudent() {
    cout << "             *  SEARCH STUDENT  *       \n";
    cout<<"                                           \n";

    if (studentCount == 0) {
        cout << "No students are available to search.\n";
        return;
    }

    string id = readNonEmptyLine("Enter Student ID: ");
    int index = findStudent(id);

    if (index == -1) {
        cout << "\nStudent not found. Please check the ID.\n";
    } else {
        displayStudentResult(index);
    }
}

// Calculate class statistics
void calculateClassStatistics() {
    cout << "             * CLASS STATISTICS *\n";
    cout <<"                                 \n";

    if (studentCount == 0) {
        cout << "No student data is available for statistics.\n";
        return;
    }

    double totalAverages = 0;
    double highestAverage = calculateAverage(0);
    double lowestAverage = calculateAverage(0);

    int highestIndex = 0;
    int lowestIndex = 0;
    int passCount = 0;
    int failCount = 0;

    for (int i = 0; i < studentCount; i++) {
        double average = calculateAverage(i);
        totalAverages += average;

        if (average > highestAverage) {
            highestAverage = average;
            highestIndex = i;
        }

        if (average < lowestAverage) {
            lowestAverage = average;
            lowestIndex = i;
        }

        if (getStatus(i) == "PASS") {
            passCount++;
        } else {
            failCount++;
        }
    }

    double classAverage = totalAverages / studentCount;
    double successRate = passCount * 100.0 / studentCount;

    cout << fixed << setprecision(2);

    cout << "Number of Students : " << studentCount << endl;
    cout << "Class Average     : " << classAverage << endl;
    cout << "Highest Average   : " << highestAverage
         << " (" << names[highestIndex] << ")\n";
    cout << "Lowest Average    : " << lowestAverage
         << " (" << names[lowestIndex] << ")\n";
    cout << "Passed Students   : " << passCount << endl;
    cout << "Failed Students   : " << failCount << endl;
    cout << "Success Rate      : " << successRate << "%\n";

    cout << "                                            \n";
}

// Display a complete class summary
void viewClassSummary() {
    cout << "           COMPLETE CLASS SUMMARY           \n";
    cout<<"                                              \n";

    if (studentCount == 0) {
        cout << "No students are available for the summary.\n";
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        displayStudentResult(i);
    }

    calculateClassStatistics();
}

// Delete a student with confirmation
void deleteStudent() {
    cout << "               DELETE STUDENT          \n";
    cout<<"                                         \n";

    if (studentCount == 0) {
        cout << "No students are available to delete.\n";
        return;
    }

    string id = readNonEmptyLine("Enter Student ID: ");
    int index = findStudent(id);

    if (index == -1) {
        cout << "Student not found. No record was deleted.\n";
        return;
    }

    cout << "\nStudent to delete:\n";
    cout << "Name: " << names[index] << endl;
    cout << "ID  : " << ids[index] << endl;

    int confirmation = readInt(
        "\nConfirm deletion? (1 = Yes, 2 = No): ", 1, 2
    );

    if (confirmation == 2) {
        cout << "\nDeletion cancelled. No data was changed.\n";
        return;
    }

    string deletedName = names[index];

    for (int i = index; i < studentCount - 1; i++) {
        names[i] = names[i + 1];
        ids[i] = ids[i + 1];

        for (int j = 0; j < SUBJECTS; j++) {
            grades[i][j] = grades[i + 1][j];
        }
    }

    studentCount--;

    cout << "\nStudent deleted successfully.\n";
    cout << "Deleted Student: " << deletedName << endl;
    cout << "Remaining Students: " << studentCount << endl;
}

// Display the menu once at startup
void displayMenu() {
    cout << "                                      \n";
    cout << "      * STUDENT GRADE MANAGEMENT SYSTEM  *\n";
    cout << "                                       \n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search for Student\n";
    cout << "4. Calculate Class Statistics\n";
    cout << "5. View Class Summary\n";
    cout << "6. Delete a Student\n";
    cout << "7. Exit\n";
    cout << "                                       \n";
}

// Main program
int main() {
    displayMenu();

    int choice;

    while (true) {
        choice = readInt("\nEnter your choice (1-7): ", 1, 7);

        if (choice == 7) {
            cout << "\nThank you for using the system. Goodbye!\n";
            break;
        }

        clearScreen();

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                calculateClassStatistics();
                break;

            case 5:
                viewClassSummary();
                break;

            case 6:
                deleteStudent();
                break;
        }


    }

    return 0;
}
