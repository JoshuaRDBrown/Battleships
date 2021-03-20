#include "../structs/RowAndCol.h"

class Ship {
	
	private: 
		char shipInitial;
		std::string shipName;
		int shipLength;
		int shipHealth;
		RowAndCol shipPos;
		std::string shipOrientation;

		bool isDestroyed = false;

	public:

		Ship(char initial, std::string name, int length, RowAndCol pos, std::string orientation) {
			shipInitial = initial;
			shipName = name;
			shipLength = length;
			shipHealth = length;
			shipPos = pos;
			shipOrientation = orientation;
		}

		void takeDamage();
		char getShipInitial();
		bool getIsShipDestroyed();
		std::string getShipName();
		int getShipHealth();
		int getShipLength();
};