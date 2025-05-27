#include <iostream>

int main(){
    using namespace std;

    cout << "Playing with pointers and references." << endl; 

    int x = 10;
    int* ptr = &x;

    cout << "x = " << x << endl;
    cout << "*ptr = " << *ptr << endl;
    cout << "ptr = " << ptr << endl;
    cout << "&x = " << &x << endl;

    return 0;
}