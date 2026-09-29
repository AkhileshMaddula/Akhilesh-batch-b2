#include <iostream>
using namespace std;

class Volume
{
public:
    // Volume of cube
    int volume(int side)
    {
        return side * side * side;
    }

    // Volume of cuboid
    int volume(int length, int breadth, int height)
    {
        return length * breadth * height;
    }

    // Volume of cylinder
    double volume(double radius, double height)
    {
        return 3.14 * radius * radius * height;
    }
};

int main()
{
    Volume v;

    cout << "Volume of cube = " << v.volume(5) << endl;

    cout << "Volume of cuboid = "
         << v.volume(5, 4, 3) << endl;

    cout << "Volume of cylinder = "
         << v.volume(8.0, 5.0) << endl;

    return 0;
}