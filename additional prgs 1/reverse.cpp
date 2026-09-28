#include <iostream>
using namespace std;

int main()
{
    string word[3];

    cout << "Enter 3 words: ";

    for(int i = 0; i < 3; i++)
    {
        cin >> word[i];
    }

    cout << "Reverse: ";

    for(int i = 2; i >= 0; i--)
    {
        cout << word[i] << " ";
    }

    return 0;
}