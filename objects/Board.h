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
		bool isComputerBoard;
		std::string name;
		int destroyedShipAmount = 0;

	public: 

		enum randomGenerationType {
			COORD,
			ORIENTATION
		};

		Board(int boardHeight, int  boardWidth, std::map<std::string, int> ships, bool isComputer, std::string playerName) {
			height = boardHeight;
			width = boardWidth;
			shipData = ships;
			isComputerBoard = isComputer;
			name = playerName;

			matrix.resize(width, std::vector<std::string>(height, " "));
    }

		void drawBoard();
		BoardDimensions getBoardDimensions();
		std::map<std::string, int> getShipData();
		bool coordinateIsValid(std::string coordinates);
		int handleBoatPlacementInput();
		shipPlacementStatus attemptShipPlacement(std::string shipName, int shipLength, std::string coordinates, std::string orientation);
		std::string generateRandomPlacement(randomGenerationType genType);
		std::vector<Ship*> getPlacedShipData();
		char * getColumnLetters();
		std::vector< std::vector<std::string> > getBoard();
		bool getIsComputerBoard();
		std::string getPlayerName();
		int getDestroyedShipAmount();
		void setDestroyedShipAmount();
		void setMissleLocationOnHitGrid(RowAndCol index, std::string value);
};