#include <iostream>
using namespace std;

class Matrix {
    int rows, cols;
    int **data;

public:
    // Constructor
    Matrix(int m, int n) {
        rows = m;
        cols = n;

        data = new int*[rows];

        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
        }
    }

    // Deep Copy Constructor
    Matrix(const Matrix &obj) {
        rows = obj.rows;
        cols = obj.cols;

        data = new int*[rows];

        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];

            for (int j = 0; j < cols; j++) {
                data[i][j] = obj.data[i][j];
            }
        }
    }

    // Input
    void input() {
        cout << "Enter matrix elements:\n";

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    // Display
    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }

        delete[] data;

        cout << "Matrix memory released\n";
    }
};

int main() {
    Matrix m1(2, 3);

    m1.input();

    cout << "\nOriginal Matrix:\n";
    m1.display();

    // Deep copy
    Matrix m2 = m1;

    cout << "\nCopied Matrix:\n";
    m2.display();

    return 0;
}