#include "Person.h"

struct _Person
{
	std::string name;
	std::string lastName;
	int age;
};

void CreatePerson(const std::string& name, const std::string& lastName, const int age, ADTPerson& person)
{
	ADTPerson output = new _Person;

	output->name = name;
	output->lastName = lastName;
	(age < 0 || age >100) ? output->age = 0 : output->age = age;
	person = output;
}

ADTPerson CreatePerson(const std::string& name, const std::string& lastName, const int age)
{
	ADTPerson output = new _Person;
	output->name = name;
	output->lastName = lastName;
	(age < 0 || age >100) ? output->age = 0 : output->age = age;
	return output;
}

// GETTERS
std::string GetName(const ADTPerson& person)
{
	return person->name;
}

std::string GetLastName(const ADTPerson& person)
{
	return person->lastName;
}

int GetAge(const ADTPerson& person)
{
	return person->age;
}

// SETTERS
void SetName(ADTPerson& person, const std::string& name)
{
	person->name = name;
}

void SetLastName(ADTPerson& person, const std::string& lastName)
{
	person->lastName = lastName;
}

void SetAge(ADTPerson& person, const int age)
{
	(age < 0 || age >100) ? person->age = 0 : person->age = age;
}

// PREDICATE
bool IsAdult(const ADTPerson& person)
{
	return person->age >= 18;
}

// DESTRUCTOR
void DestroyPerson(ADTPerson& person)
{
	if (person != nullptr)
	{
		delete person;
		person = nullptr;
	}
}