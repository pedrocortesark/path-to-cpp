#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	float sum = 0;

	std::cout << argc << " arguments received." << std::endl;
	for (int i = 1; i < argc; ++i) {
		sum += stoi(argv[i]);
	}

	cout << "Sum of arguments: " << sum << std::endl;
}