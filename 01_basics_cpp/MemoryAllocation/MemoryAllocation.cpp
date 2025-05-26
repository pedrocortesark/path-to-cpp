#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    /*
    // A pointer variable does not store the value but the address
    int i = 40;
    //int* myPointer = 40;
    int* myPointer = 0;
    */
    // For the moment, it is not pointing to anything

    // Let's understand how we can get the address to a variable
    // This is a variable stored somewhere on our RAM memory
    double height = 180.5;

    // If we need to find the address, we use the & character
    // This is called the reference variable, which stores the reference to the variable
    double* myOtherPointer = &height;

    // How can I access the value of our variable thu the pointer?
    std::cout << "Pointer: " << myOtherPointer << std::endl;
    std::cout << "Value: " << *myOtherPointer;
}
