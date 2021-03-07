#include "../structs/RowAndCol.h"

class Ship {

	public:

		char shipInitial;
		std::string shipName;
		int shipLength;
		RowAndCol shipPos;
		std::string shipOrientation;

		Ship(char initial, std::string name, int length, RowAndCol pos, std::string orientation) {
			shipInitial = initial;
			shipName = name;
			shipLength = length;
			shipPos = pos;
			shipOrientation = orientation;
		}
};