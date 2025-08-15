#include <iostream>

export module SimpleChainList;

using namespace std;

struct SimpleArray {
    int n;
    PtrSimpleArray next;
};

// 1 - Let's define an alias for the pointer to the SimpleArray type
export typedef SimpleArray* PtrSimpleArray;

export PtrSimpleArray initializeArray() {
    return NULL;
}

export bool isEmpty(PtrSimpleArray a) {
    return a == NULL;
}

export void insertNode(PtrSimpleArray& a, int n)
{
    PtrSimpleArray node = new SimpleArray;

    node->n = n;
    node->next = NULL;

    PtrSimpleArray pointer;
    if (isEmpty(a))
    {
        a = node;
    }
    else
    {
        pointer = a;
        while (pointer->next != NULL)
            pointer = pointer->next;
        
        pointer->next = node;
    }
}

export void printArray(PtrSimpleArray a)
{
    PtrSimpleArray pointer = a;
    while (pointer != NULL)
    {
        cout << "Pointer: " << pointer->n << endl;
        pointer = pointer->next;
    }
}