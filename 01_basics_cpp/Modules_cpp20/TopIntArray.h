#pragma once
#ifndef TopIntArray.h

namespace TopIntArray
{
	const int MAX_SIZE = 10;

	struct TopArray {
		int arr[MAX_SIZE];
		int length = -1;
	};

	unsigned int numberOfElements(const TopArray& topArray);

	bool isFull(const TopArray& topArray);

	bool isEmpty(const TopArray& topArray);

	void insertItem(int n, TopArray& topArray);

	void insertOrderedItem(int n, TopArray& topArray);

	void deleteLastItem(TopArray& topArray);

	void printArray(const TopArray& topArray);
}

#endif // !TopIntArray.h
