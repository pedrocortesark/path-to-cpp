#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;
const int MAX_SIZE = 10;

struct TopArray {
    int arr[MAX_SIZE];
    int length = -1;
};

unsigned int numberOfElements(const TopArray& topArray)
{
    return (topArray.length + 1);
}

bool isFull(const TopArray& topArray)
{
	return (topArray.length == MAX_SIZE - 1);
}

bool isEmpty(const TopArray& topArray)
{
	return (topArray.length == -1);
}


void insertItem(int n, TopArray& topArray)
{
	if (!isFull(topArray))
	{
		topArray.length++;
		topArray.arr[topArray.length] = n;
	}
	else
	{
		cout << "Array is full. Cannot insert " << n << endl;
		return;
	}
}

void insertOrderedItem(int n, TopArray &topArray)
{
	int index;
	if(isEmpty(topArray)) {
		topArray.length++;
		topArray.arr[topArray.length] = n;
	}
	else
	{
		index = -1;
		for (int i = 0; i <= topArray.length; i++)
		{
			if (topArray.arr[i] > n)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			topArray.length++;
			topArray.arr[topArray.length] = n;
		}
		else
		{
			topArray.length++;
			for (int i = topArray.length; i > index; i--)
				topArray.arr[i] = topArray.arr[i - 1];
			
			topArray.arr[index] = n;
		}
	}
}

void deleteLastItem(TopArray &topArray)
{
	if(isEmpty(topArray)) {
		cout << "Array is empty. Cannot delete last item." << endl;
		return;
	}

	topArray.length--;
}

void printArray( const TopArray& topArray)
{
	if(isEmpty(topArray)) {
		cout << "Array is empty." << endl;
		return;
	}

	for (int i = 0; i <= topArray.length; i++)
		cout << topArray.arr[i] << " " << endl;
}


int main()
{
	srand(time(NULL));
	TopArray myTopArray;

	/* Class A
		//for (int i = 0; i < 5; i++)
		//	insertItem(rand() % 100, myTopArray);

		//insertItem(20, myTopArray);

		while(!isFull(myTopArray)) {
			int randomValue = rand() % 10;
			insertItem(randomValue, myTopArray);
		}

		int numElements = numberOfElements(myTopArray);
		cout << "Number of elements in the TopArray: " << numElements << endl;
		printArray(myTopArray);

		while(!isEmpty(myTopArray)) {
			deleteLastItem(myTopArray);
			cout << "Deleted last item: " <<  "Remaining items: " << numberOfElements(myTopArray) << endl;
		}

		printArray(myTopArray);
	*/

	while (!isFull(myTopArray))
		insertOrderedItem(rand() % 100, myTopArray);
	
	printArray(myTopArray);


}