export module Persistence;

#include <string>
#include <fstream>
#include <filesystem>
import ManagePerson;

using namespace std;

const string FILENAME = "data.db";

export struct TPersistence {
	const string fileName = FILENAME;
	bool isInitialized;
};

export void initializePersistence(TPersistence& p)
{
	if (!filesystem::exists(FILENAME))
	{
		ofstream file(FILENAME);
		file.close();
	}
	p.isInitialized = true;
}

export TList loadList(const TPersistence &p)
{
	if (p.isInitialized)
	{
		ifstream file(p.fileName);
		TPerson person;
		TList list = createList();

		while(file.read(reinterpret_cast<char*>(&person), sizeof(TPerson)))
		{
			addPerson(list, person);
		}
		file.close();
		return list;
	}
	else
	{
		throw runtime_error("Persistence is not initialized.");
	}
}

export int getLengthList(const TList &l)
{
	return l.count+1;
}

export TPerson getPersonByIndex(const TList &l, int index)
{
	return l.persons[index];
}

export bool indexIsValid(const TList &l, int index)
{
	return index >= 0 && index <= l.count;
}

export void saveList(const TList &l, const TPersistence &p)
{
	if (p.isInitialized)
	{
		ofstream file(p.fileName, ios::binary);
		TPerson person;
		for (int  i = 0; i < getLengthList(l); i++)
		{
			person = getPersonByIndex(l, i);
			file.write(reinterpret_cast<const char*>(&person), sizeof(TPerson));
		}
		file.close();
	}
}