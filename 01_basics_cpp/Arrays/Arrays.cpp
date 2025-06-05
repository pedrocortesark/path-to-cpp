#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));
	const int NUMS = 10;

	int num;
	int randNumbers[NUMS];

	bool exists;

	for (int i = 0; i < NUMS; i++)
	{
		num = rand() % NUMS;

		for (int j = 0; j < i; j++)
		{
			if (randNumbers[j] == num)
			{
				num = rand() % NUMS;
				j = -1;
			}
		}

		int j = 0;
		while (j < i) {

		}

		randNumbers[i] = num;
	}
	

	for (int i = 0; i < NUMS; i++)
	{
		cout << randNumbers[i] << " ";
	}
}

