#include <iostream>



int main()
{
    using namespace std;

    const int MIN_AGE = 18;
    int age;

    cout << "Please enter your age:" << endl;
    cin >> age;

    if (age < MIN_AGE) 
    {
        cout << "You are not allowed to get into the place." << endl;
    }
    else
    {
        cout << "Perfect, please follow the white rabit.";
    }

    cout << "End of the program.";
}
