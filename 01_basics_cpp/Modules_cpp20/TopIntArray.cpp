#include "TopIntArray.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

namespace TopIntArray
{
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
			std::cout << "Array is full. Cannot insert " << n << std::endl;
			return;
		}
	}

	void insertOrderedItem(int n, TopArray& topArray)
	{
		int index;
		if (isEmpty(topArray)) {
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

	void deleteLastItem(TopArray& topArray)
	{
		if (isEmpty(topArray)) {
			std::cout << "Array is empty. Cannot delete last item." << std::endl;
			return;
		}

		topArray.length--;
	}

	void printArray(const TopArray& topArray)
	{
		if (isEmpty(topArray)) {
			std::cout << "Array is empty." << std::endl;
			return;
		}

		for (int i = 0; i <= topArray.length; i++)
			std::cout << topArray.arr[i] << " " << std::endl;
	}
}