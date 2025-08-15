export module ModSimpleArray;

#include <iostream>

using namespace std;

struct Node {
    int n;
    Node* next;
};

struct TList {
    Node* nodes;
    int count;
};

export typedef TList* PList;

export PList initializeList() {
    TList* l = new TList;
    l->nodes = NULL;
    l->count = 0;
    return l;
}

export bool isEmpty(PList l) {
    return l->count == 0;
}

export void insert(PList& l, int n)
{
    Node* node = new Node;

    node->n = n;
    node->next = NULL;

    Node* pointer;
    if (isEmpty(l))
    {
        l->nodes = node;
    }
    else
    {
        pointer = l->nodes;
        while (pointer->next != NULL)
            pointer = pointer->next;

        pointer->next = node;
    }
    l->count++;
}

export void insertSorted(int n, PList& l)
{
    Node* newNode = new Node;
    newNode->n = n;
    newNode->next = NULL;

    Node* currentNode;
    Node* previousNode;

    if (isEmpty(l))
    {
        l->nodes = newNode;
    }
    else
    {
        currentNode = l->nodes;
        previousNode = nullptr;

        while (currentNode != nullptr && currentNode->n < n)
        {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        // Insert at the beginning
        if (previousNode == nullptr)
        {
            newNode->next = l->nodes;
            l->nodes = newNode;
        }
        else if (currentNode == nullptr)
        {
            previousNode->next = newNode;
        }
        else
        {
            previousNode->next = newNode;
            newNode->next = currentNode;

        }
    }
    l->count++;
}

export void remove(int n, PList& l)
{
    Node* previousNode, *currentNode;
	Node* nodeToDelete;
    previousNode = NULL;
    currentNode = l->nodes;

    while (currentNode != NULL && currentNode->n != n)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL) return;
    
    if (previousNode == NULL)
    {
		nodeToDelete = currentNode;
        l->nodes = currentNode->next;
		currentNode->next = NULL;
		delete nodeToDelete;
    }
    else
    {
        nodeToDelete = currentNode;
        previousNode->next = currentNode->next;
        currentNode->next = NULL;
        delete nodeToDelete;
    }

    l->count--;
}

export unsigned int length(const PList l)
{
 //   PList pointer = a;
 //   unsigned int count = 0;
 //   while(pointer != NULL)
 //   {
 //       count++;
 //       pointer = pointer->next;
	//}
	//return count;
    return l->count;
}

export void destroyList(PList& l)
{
    if (l == NULL) return;

    Node* currentNode, * nextNode;

    currentNode = l->nodes;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }

    delete l;
    l = NULL;

}

export void printArray(PList l)
{
    if (isEmpty(l))
    {
        cout << "Array is empty." << endl;
		return;
    }

    Node* pointer = l->nodes;
    while (pointer != NULL)
    {
        cout << "Pointer: " << pointer->n << endl;
        pointer = pointer->next;
    }
}