#include "GuerreroRPG.h"
#include <string>

struct Opaco_Guerrero
{
	int attack;
	int defense;
	int health;
};

GuerreroRPG CreateGuerrero(int attack, int defense, int health)
{
	GuerreroRPG guerrero = new Opaco_Guerrero;
	guerrero->attack = attack;
	guerrero->defense = defense;
	guerrero->health = health;
	return guerrero;
}

int getAttack(GuerreroRPG guerrero)
{
	if (guerrero == nullptr) return 0;
	return guerrero->attack;
}

int getDefense(GuerreroRPG guerrero)
{
	if (guerrero == nullptr) return 0;
	return guerrero->defense;
}

int getHealth(GuerreroRPG guerrero)
{
	if (guerrero == nullptr) return 0;
	return guerrero->health;
}

void setAttack(GuerreroRPG guerrero, int attack)
{
	if (guerrero != nullptr) {
		guerrero->attack = attack;
	}
}
void setDefense(GuerreroRPG guerrero, int defense)
{
	if (guerrero != nullptr) {
		guerrero->defense = defense;
	}
}
void setHealth(GuerreroRPG guerrero, int health)
{
	if (guerrero != nullptr) {
		guerrero->health = health;
	}
}

bool isDead(const GuerreroRPG guerrero)
{
	return guerrero->health <= 0;
}

void destroyGuerrero(GuerreroRPG guerrero) 
{
	delete guerrero;
	guerrero = nullptr;
}
