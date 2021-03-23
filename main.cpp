#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include "./objects/Board.h"
#include "./structs/GameConfigDetails.h"
#include "Utils.h"
#include "./objects/GameHandler.h"

GameConfigDetails returnGameConfigDetails() {
	Utils utils;
	GameConfigDetails gameData;

	std::string line; 
	std::ifstream configFile("./adaship_config.ini");

	//generates a unique seed based on the current time to ensure a 'random' number is generated.
	srand(time(NULL));

	std::map<std::string, int> boatData = { };

	if(configFile.fail()) {
		throw std::invalid_argument("An error occurred reading the game config file.");
	}

	if(configFile.is_open()) {
		while(getline(configFile, line)) {
			std::vector<std::string> data = utils.parseGameConfigFile(line, "=");
			if(data[0] != "Board") {
				try {
					boatData.insert(std::pair<std::string,int>(data[0], std::stoi(data[1]))); 
				} catch(...) {
					throw std::invalid_argument("ERROR: Boat values must be numbers.");
				}
			} else {

				bool hasGotHeight = false;
				std::string height;
				std::string width;

				for(int i=0; i < data[1].length(); i++) {
					if(data[1].at(i) == 'x' || hasGotHeight) {
						hasGotHeight = true;
						width += data[1].at(i);
					} else {
						height += data[1].at(i);
					}
				}

				width.erase(std::remove(width.begin(), width.end(), 'x'), width.end());

				try {
					int boardHeight = std::stoi(height);
					int boardWidth = std::stoi(width);

					if((boardHeight > 80 || boardWidth > 80) || boardHeight < 5 || boardWidth < 5) {
						throw;
					}

					gameData.boardHeight = boardHeight;
					gameData.boardWidth = boardWidth;
				} catch(...) {
					throw std::invalid_argument("ERROR: Config file data is incorrect.");
				}
			}
		}
	}

	configFile.close();
	gameData.boatData = boatData;

	return gameData;
}

int initialisePlayerBoards(int boardHeight, int boardWidth, std::map<std::string, int> boatData, bool isAgainstComputer, GameMode gameMode) {
	
	Board player1Board(boardHeight, boardWidth, boatData, false, "Player 1");
	Board player2Board(boardHeight, boardWidth, boatData, isAgainstComputer, "Player 2");

	Board player1HitBoard(boardHeight, boardWidth, boatData, false, "Player 1's hit board");
	Board player2HitBoard(boardHeight, boardWidth, boatData, isAgainstComputer, "Player 2's hit board");

	GameHandler gameHandler(&player1Board, &player2Board, &player1HitBoard, &player2HitBoard, gameMode);
	int setUpStatus = gameHandler.setUp();

	if(setUpStatus == -1) {
		return -1;
	}

	return 0;
}

int main() {

	std::string userInput;
	bool inputIsInvalid = true;

	GameConfigDetails gameConfig = returnGameConfigDetails();

	while(inputIsInvalid) {

		std::cout << "Welcome to Ada Ship \n";
		std::cout << "Please choose an option \n";
		std::cout << "1) One player vs Computer \n";
		std::cout << "2) Two player game \n";
		std::cout << "3) One player vs Computer (Salvo mode) \n";
		std::cout << "4) Two player game (Salvo mode) \n";
		std::cout << "5) Quit \n";
		std::cout << "Your option: ";

		getline(std::cin, userInput);

		try {
			switch(std::stoi(userInput)) {
				case 1: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, true, NORMAL);
				case 2: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, false, NORMAL);
				case 3: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, true, SALVO);
				case 4: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, false, SALVO);					
				case 5: return 0; 
				default: throw std::invalid_argument("");
			}

			inputIsInvalid = false;
		} catch(...) {
			std::cout << "Please select a valid option \n";
		}
	}
	return 0;
}