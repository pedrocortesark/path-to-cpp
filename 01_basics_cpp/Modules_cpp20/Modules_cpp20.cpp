#include <iostream>

import MTopArray;

/* OPTION CLASSIC .h FILES


#include "TopIntArray.h"

using namespace TopIntArray;

int main()
{
	srand(time(NULL));
	TopArray myTopArray;

	while (!isFull(myTopArray))
		insertOrderedItem(rand() % 100, myTopArray);

	printArray(myTopArray);
}

*/

int main()
{
	MTopArray myTopArray;

	initializeArray(myTopArray);
	printArray(myTopArray);
}