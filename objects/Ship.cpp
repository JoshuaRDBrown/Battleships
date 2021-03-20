#include <iostream>
#include "Ship.h"

void Ship::takeDamage() {
	shipHealth = shipHealth -1;

	if(shipHealth == 0) {
		isDestroyed = true;
	}
}

char Ship::getShipInitial() {
	return shipInitial;
}

bool Ship::getIsShipDestroyed() {
	return isDestroyed;
}

std::string Ship::getShipName() {
	return shipName;
}

int Ship::getShipHealth() {
	return shipHealth;
}

int Ship::getShipLength() {
	return shipLength;
}