
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

// Week 11: Function Template
template <typename T>
T sumVector(const vector<T>& values) {
    return accumulate(values.begin(), values.end(), T{});
}

// Week 9: Custom Exception
class InvalidMarks : public runtime_error {
public:
    explicit InvalidMarks(const string& message)
        : runtime_error(message) {}
};

// Week 7 and 8: Base Class with Virtual Functions
class Student {
protected:
    int rollNo;
    string name;

public:
    Student(int roll, const string& studentName)
        : rollNo(roll), name(studentName) {}

    virtual int totalMarks() const = 0;
    virtual void display() const = 0;
    virtual void writeToFile(ofstream& out) const = 0;

    int getRollNo() const {
        return rollNo;
    }

    string getName() const {
        return name;
    }

    virtual ~Student() = default;
};

// Week 7: Derived Class
class Result : public Student {
private:
    vector<int> marks;

    void validateMarks() const {
        for (int mark : marks) {
            if (mark < 0 || mark > 100) {
                throw InvalidMarks(
                    "Marks must be between 0 and 100."
                );
            }
        }
    }

public:
    Result(int roll, const string& studentName,
           const vector<int>& subjectMarks)
        : Student(roll, studentName), marks(subjectMarks) {

        if (marks.size() != 3) {
            throw InvalidMarks(
                "Exactly 3 subject marks are required."
            );
        }

        validateMarks();
    }

    int totalMarks() const override {
        return sumVector(marks);
    }

    double averageMarks() const {
        return static_cast<double>(totalMarks())
               / marks.size();
    }

    string grade() const {
        double average = averageMarks();

        if (average >= 90) return "A+";
        if (average >= 80) return "A";
        if (average >= 70) return "B";
        if (average >= 60) return "C";
        if (average >= 50) return "D";

        return "Fail";
    }

    const vector<int>& getMarks() const {
        return marks;
    }

    // Week 8: Runtime Polymorphism
    void display() const override {
        cout << left
             << setw(10) << rollNo
             << setw(22) << name
             << setw(10) << marks[0]
             << setw(10) << marks[1]
             << setw(10) << marks[2]
             << setw(10) << totalMarks()
             << setw(12) << fixed << setprecision(2)
             << averageMarks()
             << grade() << '\n';
    }

    // Week 10: File Handling
    void writeToFile(ofstream& out) const override {
        out << rollNo << ','
            << name << ','
            << marks[0] << ','
            << marks[1] << ','
            << marks[2] << '\n';
    }
};

// Week 13: Factory Pattern and Smart Pointer
unique_ptr<Student> createResult(
    int roll,
    const string& name,
    const vector<int>& marks
) {
    return make_unique<Result>(roll, name, marks);
}

// Student Result Management System
class ResultManagementSystem {
private:
    // Week 11: STL Vector
    // Week 13: Smart Pointers
    vector<unique_ptr<Student>> students;

    const string filename = "student_results.txt";

    int readInteger(const string& prompt) const {
        int value;

        while (true) {
            cout << prompt;

            if (cin >> value) {
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                return value;
            }

            cout << "Invalid input. Enter an integer.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
        }
    }

    bool rollNumberExists(int roll) const {
        return any_of(
            students.begin(),
            students.end(),
            [roll](const unique_ptr<Student>& student) {
                return student->getRollNo() == roll;
            }
        );
    }

public:

    // Add Student
    void addStudent() {
        int roll = readInteger("Enter roll number: ");

        if (roll <= 0) {
            cout << "Roll number must be positive.\n";
            return;
        }

        if (rollNumberExists(roll)) {
            cout << "Roll number already exists.\n";
            return;
        }

        string name;

        cout << "Enter student name: ";
        getline(cin, name);

        if (name.empty() ||
            name.find(',') != string::npos) {
            cout << "Invalid student name.\n";
            return;
        }

        vector<int> marks(3);

        try {
            for (int i = 0; i < 3; i++) {
                marks[i] = readInteger(
                    "Enter marks for subject " +
                    to_string(i + 1) + " (0-100): "
                );
            }

            students.push_back(
                createResult(roll, name, marks)
            );

            cout << "Student record added successfully.\n";
        }
        catch (const InvalidMarks& e) {
            cout << "Invalid marks: "
                 << e.what() << '\n';
        }
    }

    // Display All Students
    void displayStudents() const {
        if (students.empty()) {
            cout << "No student records available.\n";
            return;
        }

        cout << "\n--------------- STUDENT RESULTS ---------------\n";

        cout << left
             << setw(10) << "Roll No"
             << setw(22) << "Name"
             << setw(10) << "Sub 1"
             << setw(10) << "Sub 2"
             << setw(10) << "Sub 3"
             << setw(10) << "Total"
             << setw(12) << "Average"
             << "Grade\n";

        cout << string(94, '-') << '\n';

        // Week 8: Virtual Function Calls
        for (const auto& student : students) {
            student->display();
        }

        cout << string(94, '-') << '\n';
    }

    // Search Student
    void searchStudent() const {
        int roll = readInteger(
            "Enter roll number to search: "
        );

        // Week 12: find_if and Lambda
        auto it = find_if(
            students.begin(),
            students.end(),
            [roll](const unique_ptr<Student>& student) {
                return student->getRollNo() == roll;
            }
        );

        if (it != students.end()) {
            cout << "\nStudent found:\n";
            (*it)->display();
        }
        else {
            cout << "Student record not found.\n";
        }
    }

    // Find Students Above Given Marks
    void displayAboveThreshold() const {
        int threshold = readInteger(
            "Enter total marks threshold (0-300): "
        );

        if (threshold < 0 || threshold > 300) {
            cout << "Threshold must be between 0 and 300.\n";
            return;
        }

        int count = 0;

        cout << "\nStudents scoring above "
             << threshold << ":\n";

        // Week 12: for_each and Lambda
        for_each(
            students.begin(),
            students.end(),
            [&threshold, &count](
                const unique_ptr<Student>& student
            ) {
                if (student->totalMarks() > threshold) {
                    student->display();
                    ++count;
                }
            }
        );

        cout << "Number of students above threshold: "
             << count << '\n';
    }

    // Sort Students
    void sortByTotalMarks() {
        // Week 12: sort and Lambda
        sort(
            students.begin(),
            students.end(),
            [](
                const unique_ptr<Student>& a,
                const unique_ptr<Student>& b
            ) {
                return a->totalMarks() > b->totalMarks();
            }
        );

        cout << "Records sorted by total marks.\n";
        displayStudents();
    }

    // Class Statistics
    void showStatistics() const {
        if (students.empty()) {
            cout << "No records available.\n";
            return;
        }

        // Week 12: accumulate and Lambda
        int total = accumulate(
            students.begin(),
            students.end(),
            0,
            [](
                int sum,
                const unique_ptr<Student>& student
            ) {
                return sum + student->totalMarks();
            }
        );

        // Week 12: count_if and Lambda
        int passed = count_if(
            students.begin(),
            students.end(),
            [](const unique_ptr<Student>& student) {
                return student->totalMarks() >= 150;
            }
        );

        cout << "\n------------- CLASS STATISTICS -------------\n";

        cout << "Number of students : "
             << students.size() << '\n';

        cout << "Combined marks     : "
             << total << '\n';

        cout << "Class average      : "
             << fixed << setprecision(2)
             << static_cast<double>(total)
                / students.size() << '\n';

        cout << "Students passed    : "
             << passed << '\n';

        cout << "Students failed    : "
             << students.size() - passed << '\n';
    }

    // Save Records to File
    void saveToFile() const {
        // Week 10: File Output
        ofstream out(filename);

        if (!out) {
            throw runtime_error(
                "Unable to open file for writing."
            );
        }

        for (const auto& student : students) {
            student->writeToFile(out);
        }

        if (!out) {
            throw runtime_error(
                "Error occurred while writing records."
            );
        }

        cout << "Records saved successfully to "
             << filename << ".\n";
    }

    // Load Records from File
    void loadFromFile() {
        // Week 10: File Input
        ifstream in(filename);

        if (!in) {
            cout << "No existing data file found. "
                 << "Starting with empty list.\n";
            return;
        }

        string line;
        int loaded = 0;

        while (getline(in, line)) {
            if (line.empty()) {
                continue;
            }

            try {
                stringstream ss(line);

                string rollText, name;
                string mark1Text, mark2Text, mark3Text;

                if (!getline(ss, rollText, ',') ||
                    !getline(ss, name, ',') ||
                    !getline(ss, mark1Text, ',') ||
                    !getline(ss, mark2Text, ',') ||
                    !getline(ss, mark3Text, ',')) {

                    cout << "Skipping invalid record.\n";
                    continue;
                }

                int roll = stoi(rollText);
                int mark1 = stoi(mark1Text);
                int mark2 = stoi(mark2Text);
                int mark3 = stoi(mark3Text);

                if (roll <= 0 || rollNumberExists(roll)) {
                    cout << "Skipping duplicate or invalid "
                         << "roll number.\n";
                    continue;
                }

                vector<int> marks = {
                    mark1, mark2, mark3
                };

                students.push_back(
                    createResult(roll, name, marks)
                );

                ++loaded;
            }
            catch (const exception& e) {
                cout << "Skipping invalid file record: "
                     << e.what() << '\n';
            }
        }

        cout << loaded << " record(s) loaded from "
             << filename << ".\n";
    }

    // Main Menu
    void run() {
        loadFromFile();

        int choice;

        do {
            cout << "\n";
            cout << "============================================\n";
            cout << "    STUDENT RESULT MANAGEMENT SYSTEM\n";
            cout << "============================================\n";

            cout << "1. Add Student Record\n";
            cout << "2. Display All Student Records\n";
            cout << "3. Search Student by Roll Number\n";
            cout << "4. Display Students Above Given Marks\n";
            cout << "5. Sort Students by Total Marks\n";
            cout << "6. Display Class Statistics\n";
            cout << "7. Save Records to File\n";
            cout << "8. Exit\n";

            cout << "============================================\n";

            choice = readInteger("Enter your choice: ");

            try {
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
                        displayAboveThreshold();
                        break;

                    case 5:
                        sortByTotalMarks();
                        break;

                    case 6:
                        showStatistics();
                        break;

                    case 7:
                        saveToFile();
                        break;

                    case 8:
                        saveToFile();
                        cout << "Thank you for using the system.\n";
                        break;

                    default:
                        cout << "Invalid choice. "
                             << "Please select 1 to 8.\n";
                }
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << '\n';
            }

        } while (choice != 8);
    }
};

// Main Function
int main() {
    ResultManagementSystem system;

    system.run();

    return 0;
}
