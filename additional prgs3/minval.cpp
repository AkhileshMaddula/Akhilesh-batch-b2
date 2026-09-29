#include <iostream>
using namespace std;

// Smaller of two integers
inline int minVal(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}

// Smaller of three integers
inline int minVal(int a, int b, int c)
{
    int min = a;

    if(b < min)
        min = b;

    if(c < min)
        min = c;

    return min;
}

int main()
{
    cout << "Smaller of 2 numbers = "
         << minVal(10, 5) << endl;

    cout << "Smaller of 3 numbers = "
         << minVal(10, 6, 8) << endl;

    return 0;
}