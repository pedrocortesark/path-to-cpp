#include <iostream>

using namespace std;

void testingArrays(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	
	for (int i = 0; i < size; i++)
		arr[i] = 0;
}

int main()
{
	int myarray[5] = { 1, 2, 3, 4, 5 };
	testingArrays(myarray, 5);
	cout << endl;
	for (int i = 0; i < 5; i++)
		cout << myarray[i] << " ";
}
