
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int usn;
    string name;
    double *marks;
    int n;

    static int studentCount;

public:
    // Parameterized constructor
    Student(int u, string nm, int count) {
        usn = u;
        name = nm;
        n = count;

        marks = new double[n];

        for (int i = 0; i < n; i++) {
            cout << "Enter mark " << i + 1
                 << " for " << name << ": ";
            cin >> marks[i];
        }

        studentCount++;
    }

    // Copy constructor - deep copy
    Student(const Student &s) {
        usn = s.usn;
        name = s.name;
        n = s.n;

        marks = new double[n];

        for (int i = 0; i < n; i++) {
            marks[i] = s.marks[i];
        }

        studentCount++;
    }

    // Destructor
    ~Student() {
        delete[] marks;
        studentCount--;
    }

    // Inline function to calculate average
    inline double average() const {
        double total = 0;

        for (int i = 0; i < n; i++) {
            total += marks[i];
        }

        return total / n;
    }

    // Function overloading
    void display() const {
        cout << "\nUSN: " << usn;
        cout << "\nName: " << name;
        cout << "\nAverage Marks: " << average() << endl;
    }

    void display(bool showMarks) const {
        display();

        if (showMarks) {
            cout << "Individual Marks: ";

            for (int i = 0; i < n; i++) {
                cout << marks[i] << " ";
            }

            cout << endl;
        }
    }

    // Static member function
    static int getStudentCount() {
        return studentCount;
    }

    // Overloaded > operator
    bool operator>(const Student &s) const {
        return average() > s.average();
    }

    // Friend function
    friend void showTopper(const Student &s1,
                           const Student &s2);
};

// Definition of static member
int Student::studentCount = 0;

// Friend function
void showTopper(const Student &s1, const Student &s2) {
    cout << "\n--- Topper Details ---\n";

    if (s1 > s2) {
        cout << s1.name << " has higher marks.\n";
    }
    else if (s2 > s1) {
        cout << s2.name << " has higher marks.\n";
    }
    else {
        cout << "Both students have equal marks.\n";
    }
}

int main() {
    cout << "================================\n";
    cout << "   STUDENT MANAGEMENT SYSTEM\n";
    cout << "================================\n";

    int usn1, usn2;
    string name1, name2;

    cout << "\nEnter first student USN: ";
    cin >> usn1;

    cin.ignore();

    cout << "Enter first student name: ";
    getline(cin, name1);

    Student s1(usn1, name1, 3);

    cout << "\nEnter second student USN: ";
    cin >> usn2;

    cin.ignore();

    cout << "Enter second student name: ";
    getline(cin, name2);

    Student s2(usn2, name2, 3);

    cout << "\n--- Student Details ---\n";
    s1.display(true);
    s2.display(true);

    // Friend function and operator overloading
    showTopper(s1, s2);

    // Static member
    cout << "\nTotal Number of Students: ";
    cout << Student::getStudentCount() << endl;

    return 0;
}
