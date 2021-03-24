#include "Board.h"
#include "GameHandler.h"
#include "../Utils.h"

int GameHandler::setUp() {
	player1->drawBoard();
	int p1CompletionStatus = player1->handleBoatPlacementInput();
	if(p1CompletionStatus == -1) {
		return -1;
	}
	int p2CompletionStatus = player2->handleBoatPlacementInput();

	if(p2CompletionStatus == -1) {
		return -1;
	}

	mainGameLoop();
	return 0;
}

int GameHandler::mainGameLoop() {

	Utils utils;

	int turnCount = 0;

	while(isGameInProgress) {
		turnCount++;
		//Using the result of turnCount modulo to determine which player class currently IS NOT the one playing
		Board * currentPlayer = turnCount % 2 == 0 ? player2 : player1;
		Board * opponent = turnCount % 2 == 0 ? player1 : player2;
		Board * currentPlayerHitBoard = currentPlayer->getPlayerName() == "Player 1" ?  player1HB : player2HB;

		attemptFireMissile(currentPlayer, opponent, currentPlayerHitBoard);
	}

	std::string playAgain;
	std::cout << "Would you like to play again? (Y/N): ";
	getline(std::cin, playAgain);

	playAgain = utils.convertStringToUpperCase(playAgain);

	if(playAgain == "Y") {
		setUp();
	} else if(playAgain == "N") {
		std::cout << "Goodbye...\n";
		exit(0);
	}

	return 1;
}

void GameHandler::attemptFireMissile(Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard) {

	Utils utils;

	std::string coordinatesToFireUpon;
	bool inputIsInvalid = true;
	std::vector<std::string> errorMessageBody = {};
	
	int aliveShipAmount = currentPlayer->getPlacedShipData().size() - currentPlayer->getDestroyedShipAmount();

	std::cout << "Game Phase - Press Q to quit the game at any time";

	currentPlayer->drawBoard();
	currentPlayerHitBoard->drawBoard();
	showShipStatus(currentPlayer);

	while(inputIsInvalid) {
		if(!currentPlayer->getIsComputerBoard()) {
			
			std::string salvoPrompt = ", Please enter " + std::to_string(aliveShipAmount) + " unique locations to fire upon(E.g 1A 5B 9D... or press enter to auto fire): ";
			std::string normalPrompt = ", Please enter a location to fire (1A or press space for auto fire): ";

			std::cout << "\n" << currentPlayer->getPlayerName();
			std::cout << (selectedGameMode == SALVO ? salvoPrompt : normalPrompt);

			getline(std::cin, coordinatesToFireUpon);
			coordinatesToFireUpon = utils.convertStringToUpperCase(coordinatesToFireUpon);
		}
		
		if(currentPlayer->getIsComputerBoard() || coordinatesToFireUpon.empty()) {
			if(selectedGameMode == SALVO) { 
				for(int i = 0; i < aliveShipAmount; i++) {
					std::string randomlyGeneratedCoord = currentPlayer->generateRandomPlacement(Board::COORD);
					if(i != 0) {
						coordinatesToFireUpon += " " + randomlyGeneratedCoord;
					} else {
						coordinatesToFireUpon += randomlyGeneratedCoord;
					}
				}
			} else {
				coordinatesToFireUpon = currentPlayer->generateRandomPlacement(Board::COORD);
			}
		}

		std::vector<std::string> missileLocations = utils.splitInputCoords(coordinatesToFireUpon);
		
		std::vector<RowAndCol> indexesToFireUpon = {};

		for(int j = 0; j < missileLocations.size(); j++) {
			if(!isdigit(missileLocations[j].at(1))) {
				missileLocations[j] = "0" + missileLocations[j];
			}
			
			if(missileLocations[j].length() != 4) {
				missileLocations[j] = missileLocations[j] + " ";
			}

			if((selectedGameMode == SALVO && indexesToFireUpon.size() > aliveShipAmount) || (selectedGameMode == NORMAL && missileLocations.size() != 1)) {
				errorMessageBody.push_back("- You have enter too many locations.");
			}

			bool coordIsValid = currentPlayer->coordinateIsValid(missileLocations[j]);

			if(!coordIsValid) {
				errorMessageBody.push_back("- Location is not a valid place on the board");
			} else {
				std::vector<std::string> columnLetters = currentPlayer->getColumnLetters();
				RowAndCol index = utils.getIndexFromCoordinates(columnLetters, missileLocations[j], currentPlayer->getBoardDimensions().width);

				std::string gridPosValue = currentPlayerHitBoard->getBoard()[index.row][index.col];

				if(gridPosValue == "X" || gridPosValue == "O") {
					errorMessageBody.push_back("- You have already fired a missle here");
				} else {
					indexesToFireUpon.push_back(index);
				}

				if(errorMessageBody.size() != 0) {
					break;
				}
			}
		}

		if(errorMessageBody.size() == 0) {
			inputIsInvalid = false;
			std::cout << "\nTURN LOG: \n";
			for(int i = 0; i < indexesToFireUpon.size(); i++) {
				fireMissile(indexesToFireUpon[i], currentPlayer, opponent, currentPlayerHitBoard, missileLocations[i]);
			}

		} else {
			if(!currentPlayer->getIsComputerBoard()) {
				std::cout << "Invalid input - your input violated the following rules, please try again: \n";
				for(int i = 0; i < errorMessageBody.size(); i++) {
					std::cout << errorMessageBody[i] << "\n";
				}
			}
			errorMessageBody.clear();
		}
	}
	std::cout << "Press any key to continue";
	std::cin.ignore();
}

void GameHandler::fireMissile(RowAndCol index, Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard, std::string missileLocation) {

	std::vector< std::vector<std::string> > opponentMatrix = opponent->getBoard();
	std::vector< std::vector<std::string> > currentPlayerHitBoardMatrix = currentPlayerHitBoard->getBoard();

	if(opponentMatrix[index.row][index.col] != " ") {

		std::string playerLog =  "Your missile has hit an enemy ship at " + missileLocation + "\n";
		std::string computerLog = "Computers missile hit one of your ships!\n";

		std::cout << (currentPlayer->getIsComputerBoard() ? computerLog : playerLog);

		std::vector<Ship*> opponentShips = opponent->getPlacedShipData();

		for(int i = 0; i < opponentShips.size(); i++) {
			std::string shipInitalAsString;

			char shipInital = opponentShips[i]->getShipInitial();

			shipInitalAsString += shipInital;
			 
			if(opponentMatrix[index.row][index.col] == shipInitalAsString) {
				opponentShips[i]->takeDamage();
				opponent->setMissleLocationOnHitGrid(index, "X");
				currentPlayerHitBoard->setMissleLocationOnHitGrid(index, "X");

				if(opponentShips[i]->getIsShipDestroyed()) {
					std::cout << "Your missile has destroyed an enemy ship!\n";
					opponent->setDestroyedShipAmount();
					checkIfGameEnd(opponent->getDestroyedShipAmount(), opponentShips.size(), currentPlayer);
				}
			}
		}
	} else {

		std::cout << (currentPlayer->getIsComputerBoard() ? "Computers missile failed to hit one of your ships.\n" : "Your missile failed to hit an enemy ship.\n");

		currentPlayerHitBoard->setMissleLocationOnHitGrid(index, "O");
	}
}

void GameHandler::checkIfGameEnd(int opponentDestroyedShipAmount, int opponentPlacedShipAmount, Board * currentPlayerBoard) {

	if(opponentPlacedShipAmount == opponentDestroyedShipAmount) {
		isGameInProgress = false;
		std::string winningText = currentPlayerBoard->getIsComputerBoard() ? "The computer has won!\n" : currentPlayerBoard->getPlayerName() + " has won!\n"; 
		std::cout << winningText;
	}
}

void GameHandler::showShipStatus(Board * player) {

	std::vector<Ship*> placedShipData = player->getPlacedShipData();

	std::cout << "Placed ship data: \n";

	for(int i = 0; i < placedShipData.size(); i++) {
		std::cout << placedShipData[i]->getShipName() << " | " << placedShipData[i]->getShipHealth() << "/" << placedShipData[i]->getShipLength() << " |" << "\n";
	}
}