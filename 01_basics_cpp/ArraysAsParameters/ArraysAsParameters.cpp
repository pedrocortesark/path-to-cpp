#include <iostream>
#include <array>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int MAX_NUM = 10;

unsigned int arrLength(int arr[])
{
	unsigned int sizeInt = sizeof(int);
	unsigned int sizeArr = sizeof(arr);

	unsigned int arrLength = sizeof(arr) / sizeInt;

	cout << "Size of int: " << sizeInt << endl;
	cout << "Size of array: " << sizeArr << endl;
	cout << "Length of array: " << arrLength << endl;

	return 0;
}

void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}

bool checkNumber(int arr[], int size, int number)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == number)
			return true;
	}
	return false;
}

unsigned int getNumberCount(int arr[], int size, int number)
{
	unsigned int counter = 0;
	for (int i = 0; i < size; i++)
		if (arr[i] == number) counter++;
	return counter;
}

int main()
{
    int numbers[MAX_NUM];
	int n;

	srand(time(NULL));

	for (int i = 0; i < MAX_NUM; i++)
	{
		numbers[i] = rand() % 10;
	}

	printArray(numbers, 10);
	cout << endl;

	//do {
	//	cout << "\nEnter a number between 0 and 99: ";
	//	cin >> n;
	//	cout << "The number " << n << " appears " << getNumberCount(numbers, n) << " times in the array.";
	//} while (!checkNumber(numbers, n));

	unsigned int sizeInt = sizeof(int);
	unsigned int sizeArr = sizeof(numbers);

	unsigned int arrLength = sizeof(numbers) / sizeInt;

	cout << "Size of int: " << sizeInt << endl;
	cout << "Size of array: " << sizeArr << endl;
	cout << "Length of array: " << arrLength << endl;

	//arrLength(numbers);

}
