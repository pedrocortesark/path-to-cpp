#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
import SimpleArrayModule;

using namespace std;

TSimpleArray simpleArray;

int main()
{
    int number;
    simpleArray = initializeArray();
    //srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        //insertNode(simpleArray, rand()%10);
        insertNode(simpleArray, i);
    }

    if (isEmpty(simpleArray))
    {
        cout << "The list is empty" << endl;
    }
    else
    {
        cout << "The list has nodes" << endl;
    }

    printArray(simpleArray);

    do {
        cout << "Enter the number to delete: " << endl;
        cin >> number;
        deleteNode(simpleArray, number);
        printArray(simpleArray);
        cout << endl;
    } while (number != -1);

}