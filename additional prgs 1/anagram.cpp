#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string s1, s2;

    cout << "Enter first word: ";
    cin >> s1;

    cout << "Enter second word: ";
    cin >> s2;

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    if(s1 == s2)
        cout << "Anagram";
    else
        cout << "Not an Anagram";

    return 0;
}