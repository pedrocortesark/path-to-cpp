#include <iostream>

using namespace std;

struct SimpleArray {
    int n;
    SimpleArray* next;
};

// Let's define some functions to encapsulate the logic

// 1 - Initialize the array with a NULL object
SimpleArray* initializeArray() {
    return NULL;
}

// 2 - Check is any array is empty
bool isEmpty(SimpleArray* a) {
    return a == NULL;
}

// 3 - Create a function to insert a new node at the end
//     IMP - we need to pass the array as reference!
void insertNode(SimpleArray* &a, int n)
{
    // Let's create the node requesting the memory
    SimpleArray* node = new SimpleArray;

    // Now, we assign the argument and define the next node as NULL
    node->n = n;
    node->next = NULL;

    SimpleArray* pointer;
    // Finally, we check the provided array
    if (isEmpty(a))
    {
        // If it is empty, the list is just the node I've created
        a = node;
    }
    else
    {
        // If the list is not empty, I need to iterate over the whole list seeking the last element
        // The last element is that one with a NULL pointer in the next property
        // First, we initialize the pointer with the first element 
        pointer = a;
        while (pointer->next != NULL)
        {
            // Let's move along the whole array until we find the NULL next property
            pointer = pointer->next;
        }
        // Once we find the last element, we can assign the node as the following item
        pointer->next = node;
    }
}

// 4 - Let's create a funcion to print the array elements
void printArray(SimpleArray* a)
{ 
    SimpleArray* pointer = a;
    while (pointer != NULL)
    {
        cout << "Pointer: " << pointer->n << endl;
        pointer = pointer->next;
    }
}

SimpleArray* simpleArray;

int main()
{
    // simpleArray is nothing currently
    // Let's ask for memory (Leap)
    // simpleArray = new SimpleArray;
    // simpleArray->next = new SimpleArray;
    // simpleArray->next->next = new SimpleArray;

    // Initializing the array element
    simpleArray = initializeArray();

    // Checking if the array is empty (clue, it is empty)
    if (isEmpty(simpleArray))
    {
        cout << "The list is empty" << endl;
    }
    else
    {
        cout << "The list has nodes" << endl;
    }

    // Adding several items to my array
    for (int i = 0; i < 10; i++)
    {
        insertNode(simpleArray, i);
    }

    // Checking if the array is empty (clue, it is not empty)
    if (isEmpty(simpleArray))
    {
        cout << "The list is empty" << endl;
    }
    else
    {
        cout << "The list has nodes" << endl;
    }

    // Printing the resulting array
    printArray(simpleArray);
}