#pragma once

struct Opaco_Guerrero;

typedef Opaco_Guerrero* GuerreroRPG;

GuerreroRPG CreateGuerrero(int attack, int defense, int health);

int getAttack(GuerreroRPG guerrero);

int getDefense(GuerreroRPG guerrero);

int getHealth(GuerreroRPG guerrero);

void setAttack(GuerreroRPG guerrero, int attack);
void setDefense(GuerreroRPG guerrero, int defense);
void setHealth(GuerreroRPG guerrero, int health);

bool isDead(const GuerreroRPG guerrero);

void destroyGuerrero(GuerreroRPG guerrero);

