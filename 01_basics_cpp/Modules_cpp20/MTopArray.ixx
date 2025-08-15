export module MTopArray;
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

export const int MAX_SIZE = 10;

export struct MTopArray {
	int arr[MAX_SIZE];
	int length = -1;
};

void randomArray(MTopArray& topArray) {
	srand((time(NULL)));
	for (int i = 0; i < MAX_SIZE; ++i) {
		topArray.arr[i] = rand() % 100;
	}
	topArray.length = MAX_SIZE - 1; // Set the length to the last index
}

export void initializeArray(MTopArray& topArray) {
	topArray.length = MAX_SIZE - 1; 
	randomArray(topArray);
}

export void printArray(const MTopArray& topArray)
{
	for (int i = 0; i <= topArray.length; i++)
		std::cout << topArray.arr[i] << " " << std::endl;
}