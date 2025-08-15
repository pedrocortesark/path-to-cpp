#pragma once

#include <string>

const int MIN_AGE = 18;

struct _Person;

typedef _Person* ADTPerson;

// OPERATORS CONSTRUCTORS
void CreatePerson(const std::string& name, const std::string& lastName, const int age, ADTPerson& person);

ADTPerson CreatePerson(const std::string& name, const std::string& lastName, const int age);


// GETTERS
std::string GetName(const ADTPerson& person);

std::string GetLastName(const ADTPerson& person);

int GetAge(const ADTPerson& person);

// SETTERS
void SetName(ADTPerson& person, const std::string& name);

void SetLastName(ADTPerson& person, const std::string& lastName);

void SetAge(ADTPerson& person, const int age);

// PREDICATES
bool IsAdult(const ADTPerson& person);

// DESTRUCTORS
void DestroyPerson(ADTPerson& person);