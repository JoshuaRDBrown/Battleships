#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../structs/BoardDimensions.h"
#include "Ship.h"

enum shipPlacementStatus { 
	VALID,
	INVALID
};

class Board {

	private: 

		std::vector< std::vector<std::string> > matrix;

		char columnLetters[26] = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'N', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
		};

		int height;
		int width;
		std::map<std::string, int> shipData;
		std::vector<Ship*> placedShips = { }; 

	public: 

		Board(int boardHeight, int  boardWidth, std::map<std::string, int> ships) {
			height = boardHeight;
			width = boardWidth;
			shipData = ships;
    }

		void drawBoard(bool isInitalDraw);
		BoardDimensions getBoardDimensions();
		std::map<std::string, int> getShipData();
		bool coordinateIsValid(std::string coordinates);
		void handleBoatPlacementInput();
		shipPlacementStatus attemptShipPlacement(std::string shipName, int shipLength, std::string coordinates, std::string orientation);
};