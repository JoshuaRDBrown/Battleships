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
					throw std::invalid_argument("Config values must be int.");
				}
			}
		}
	}

	configFile.close();
	gameData.boatData = boatData;

	return gameData;
}

int main() {

	std::string userInput;
	bool inputIsInvalid = true;

	GameConfigDetails gameConfig = returnGameConfigDetails();

	Board player1Board(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, false, 1);
	Board player2Board(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, true, 2);

	while(inputIsInvalid) {

		std::cout << "Welcome to Ada Ship \n";
		std::cout << "Please choose an option \n";
		std::cout << "1) One player vs Computer \n";
		std::cout << "2) Quit \n";
		std::cout << "Your option: ";

		getline(std::cin, userInput);
		try {
			switch(std::stoi(userInput)) {
				case 1: {
					GameHandler gameHandler(&player1Board, &player2Board);
					gameHandler.setUp();
					inputIsInvalid = false;
				}
					
				case 2: return 0; 
				default: throw std::invalid_argument("");
			}
		} catch(...) {
			std::cout << "Please select a valid option \n";
		}
	}
	return 0;
}