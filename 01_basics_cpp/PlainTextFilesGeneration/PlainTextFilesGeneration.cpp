#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

int main()
{
	string path = "My file.txt";

	//ofstream myFile;
	//myFile.open(path, ios::app);

	//// Check if the file was created
	//if (filesystem::exists(path))
	//{
	//	cout << "Exists." << endl;
	//	myFile << "Hi line.\n";
	//	myFile.close();
	//}
	//else
	//	cout << "Failed to create file." << endl;
	
	string content;
	ifstream file(path);

	while (getline(file, content))
	{
		cout << content << endl;
	}

	file.close();


}