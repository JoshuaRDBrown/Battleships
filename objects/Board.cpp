#include "Board.h"
#include "../Utils.h"

void Board::drawBoard(bool isInitialDraw) {
	std::cout << "Your board: \n";

	matrix.resize(width, std::vector<std::string>(height, " "));
	
	std::cout << "     ";
	for (int i = 0; i < height; i ++) {
		std::cout << columnLetters[i] << "   ";
	}

	std::cout << std::endl;

	for(int j = 0; j < width; j++) {
			
		if(j < 9) {
			std::cout << " " << j + 1 << " | ";
		} else {
			std::cout << j + 1 << " | ";
		}
			
		for(int k = 0; k < height; k++){
			std::cout << matrix[j][k] << " | ";
		}
		std::cout << std::endl;
	}

	if(isInitialDraw) {
		handleBoatPlacementInput();
	}
}

BoardDimensions Board::getBoardDimensions() {
	BoardDimensions boardDimensions;

	boardDimensions.height = height;
	boardDimensions.width = width;

	return boardDimensions;
};

std::map<std::string, int> Board::getShipData() {
 		return shipData;
};

bool Board::coordinateIsValid(std::string coordinates) {
	//TODO refactor so it deals with letters for bigger boards such as AA, AB
	try {

		int numberCoord;

		if(coordinates.at(0) == '0') {
			std::string coordAsString;
			coordAsString += coordinates.at(1);
			numberCoord = std::stoi(coordAsString);
		} else {
			std::string concatCoord;
			concatCoord += coordinates.at(0);
			concatCoord += coordinates.at(1);
			numberCoord = std::stoi(concatCoord);
		}

		if(numberCoord <= height && !isdigit(coordinates.at(2))) {
			return true;
		}

		return false;
	} catch(...) {
		return false;
	}
};

void Board::handleBoatPlacementInput() {

	Utils utils;

	for (auto const& pair : shipData) {
    auto shipName = pair.first;
		auto shipLength = pair.second;
	
		bool inputIsInvalid = true;

		while(inputIsInvalid) {
			std::string errorMessageHeader = "Invalid input - your input violated the following rules: \n";
			std::vector<std::string> errorMessageBody = {};

			std::string coordinates;
			std::cout << "Enter the coordinates for the " << shipName << " - " << "which has a length of " << std::to_string(shipLength) << "(E.g 1B): ";
			getline(std::cin, coordinates);

			coordinates = utils.convertStringToUpperCase(coordinates);

			if(coordinates.empty()) {
				//autoplace
			} else if(coordinates.length() == 2) {
				coordinates = "0" + coordinates;
			}

			bool coordIsValid = coordinateIsValid(coordinates);

			if(!coordIsValid) {
				errorMessageBody.push_back("- The coordinates should use a format of number and letter (20AB)");
			}

			std::string orientation;
			std::cout << "Enter the orientation for this ship (H/V): "; 
			getline(std::cin, orientation);

			orientation = utils.convertStringToUpperCase(orientation);

			if(orientation.empty()) {
				//autoplace
			} else if(orientation != "H" && orientation != "V") {
				errorMessageBody.push_back("- The orientation should be either 'H' or 'V'");
			}

			if(errorMessageBody.size() == 0) {

				shipPlacementStatus placementStatus = attemptShipPlacement(shipName, shipLength, coordinates, orientation);

				if(placementStatus == INVALID) {
					std::cout << "That position is either an invalid position or you have a boat already occupying this space, please try again \n";
				} else {
					inputIsInvalid = false;
				}
			} else {
				std::cout << errorMessageHeader;
				for(int i = 0; i < errorMessageBody.size(); i ++) {
					std::cout << errorMessageBody[i] << "\n";
				}
				errorMessageBody.clear();
			}
		}
	}
}

shipPlacementStatus Board::attemptShipPlacement(std::string shipName, int shipLength, std::string coordinates, std::string orientation) {
	
	Utils utils;

	char shipInitial = shipName[0];

	RowAndCol coordIndex = utils.getIndexFromCoordinates(columnLetters, coordinates);

	for(int i = 0; i < shipLength; i++) {

		if(orientation == "H") {
			for(int j = 0; j < shipLength; j++) {
				if(coordIndex.col + j > height -1) {
				return INVALID;
				}
			}

			if(matrix[coordIndex.row][coordIndex.col + i] == " ") {
				matrix[coordIndex.row][coordIndex.col + i] = shipInitial;
			} else {
				return INVALID;
			}
		} else {
			for(int k = 0; k < shipLength; k++) {
				if(coordIndex.col + k > height -1) {
				return INVALID;
				}
			}

			if(matrix[coordIndex.row + i][coordIndex.col] == " ") {
				matrix[coordIndex.row + i][coordIndex.col] = shipInitial;
			} else {
				return INVALID;
			}
		}
	}

	placedShips.push_back(new Ship{shipInitial, shipName, shipLength, coordIndex, orientation});

	drawBoard(false);

	return VALID;
};