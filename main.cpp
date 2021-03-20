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
				boatData.insert(std::pair<std::string,int>(data[0], std::stoi(data[1]))); 
			} else {
				data[1].erase(std::remove(data[1].begin(), data[1].end(), 'x'), data[1].end());

				auto formattedBoardHeight = std::string(1,data[1].at(0))+data[1].at(1);
				auto formattedBoardWidth = std::string(1,data[1].at(2))+data[1].at(3);

				try {
					int boardHeight = std::stoi(formattedBoardHeight);
					int boardWidth = std::stoi(formattedBoardWidth);

					gameData.boardHeight = boardHeight;
					gameData.boardWidth = boardWidth;
				} catch(...) {
					throw std::invalid_argument("Config file is incorrect.");
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