export module SimpleArrayModule;

#include<iostream>

using namespace std;

struct NodeArray {
    int n;
    NodeArray* next;
};

export typedef NodeArray* TSimpleArray;


export TSimpleArray initializeArray() {
    return NULL;
}

export bool isEmpty(TSimpleArray a) {
    return a == NULL;
}

export void insertNode(TSimpleArray& a, int n)
{
    TSimpleArray newNode = new NodeArray;
    newNode->n = n;
    newNode->next = nullptr;

    TSimpleArray currentNode, previousNode;

    if (isEmpty(a))
    {
        a = newNode;
    }
    else
    {
        currentNode = a;
        previousNode = nullptr;

        while ((currentNode != nullptr) && (currentNode->n <= n)) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        // Insert at the beginning
        if (previousNode == nullptr) {
            newNode->next = a;
            a = newNode;
        }
        // Insert at the end
        else if ( currentNode == nullptr )
        {
            previousNode->next = newNode;
        }
        else
        {
            previousNode->next = newNode;
            newNode->next = currentNode;
        }
    }
}

export void deleteNode(TSimpleArray& a, int n)
{
    if (isEmpty(a))
    {
        cout << "Cannot delete elements from an empty list" << endl;
        return;
    }

    TSimpleArray previousNode, currentNode, nodeToDelete = nullptr;
    previousNode = nullptr;
    currentNode = a;

    while ((currentNode != nullptr) && (currentNode->n != n))
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        cout << "No elements were found for input: " << n << endl;
        return;
    }
    else if (previousNode == nullptr)
    {
        a = currentNode->next;
        delete currentNode;

    }
    else if (currentNode->next == nullptr)
    {
        previousNode->next = nullptr;
        delete currentNode;
    }
    else
    {
        //nodeToDelete = currentNode;
        previousNode->next = currentNode->next;
        delete currentNode;
    }
}

export void insertEnd(TSimpleArray &a, int n)
{
    TSimpleArray node = new NodeArray;

    node->n = n;
    node->next = NULL;

    TSimpleArray pointer;
    if (isEmpty(a))
    {
        a = node;
    }
    else
    {
        pointer = a;
        while (pointer->next != NULL)
        {
            pointer = pointer->next;
        }
        pointer->next = node;
    }
}

export void printArray(const TSimpleArray a)
{
    if (isEmpty(a)) 
    {
        cout << "[]" << endl;
        return;
    }
    TSimpleArray pointer = a;
    while (pointer != NULL)
    {
        cout << "Pointer: " << pointer->n << endl;
        pointer = pointer->next;
    }
}
