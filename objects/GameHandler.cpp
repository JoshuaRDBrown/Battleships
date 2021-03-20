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

void GameHandler::mainGameLoop() {

	int turnCount = 0;

	while(isGameInProgress) {
		turnCount++;
		//Using the result of turnCount modulo to determine which player class currently IS NOT the one playing
		Board * currentPlayer = turnCount % 2 == 0 ? player2 : player1;
		Board * opponent = turnCount % 2 == 0 ? player1 : player2;
		Board * currentPlayerHitBoard = currentPlayer->getPlayerName() == "Player 1" ?  player1HB : player2HB;

		attemptFireMissile(currentPlayer, opponent, currentPlayerHitBoard);
	}
}

void GameHandler::attemptFireMissile(Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard) {

	Utils utils;

	std::string coordinateToFireUpon;

	//TODO add validation 

	if(!currentPlayer->getIsComputerBoard()) {
		currentPlayer->drawBoard();
		currentPlayerHitBoard->drawBoard();
		showShipStatus(currentPlayer);
		std::cout << "\n" << currentPlayer->getPlayerName() << ", Please enter a location to fire (1A or press space for auto fire): ";
		getline(std::cin, coordinateToFireUpon);
	} 
		
	if(currentPlayer-> getIsComputerBoard() || coordinateToFireUpon.empty()) {
		coordinateToFireUpon = currentPlayer->generateRandomPlacement(Board::COORD);
	}
	
	if(coordinateToFireUpon.length() == 2) {
		coordinateToFireUpon = "0" + coordinateToFireUpon;
	}

	playerMissleHits.push_back(coordinateToFireUpon);
	char * columnLetters = currentPlayer->getColumnLetters();
	RowAndCol index = utils.getIndexFromCoordinates(columnLetters, coordinateToFireUpon);
	fireMissile(index, currentPlayer, opponent, currentPlayerHitBoard);
}

void GameHandler::fireMissile(RowAndCol index, Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard) {

	std::vector< std::vector<std::string> > opponentMatrix = opponent->getBoard();
	std::vector< std::vector<std::string> > currentPlayerHitBoardMatrix = currentPlayerHitBoard->getBoard();

	if(opponentMatrix[index.row][index.col] != " ") {

		if(!currentPlayer->getIsComputerBoard()) {
			std::cout << "Your missile has hit an enemy ship! \n";
		}
		
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
					opponent->setDestroyedShipAmount();
					checkIfGameEnd(opponent->getDestroyedShipAmount(), opponentShips.size());
				}
			}
		}
	} else {

		if(!currentPlayer->getIsComputerBoard()) {
			std::cout << "Your missile failed to hit an enemy ship. \n";
		}
		currentPlayerHitBoard->setMissleLocationOnHitGrid(index, "O");
	}
}

void GameHandler::checkIfGameEnd(int opponentDestroyedShipAmount, int opponentPlacedShipAmount) {

	if(opponentPlacedShipAmount == opponentDestroyedShipAmount) {
		isGameInProgress = false;
		std::cout << "GAME WON!";
	}
}

void GameHandler::showShipStatus(Board * player) {

	std::vector<Ship*> placedShipData = player->getPlacedShipData();

	std::cout << "Placed ship data: \n";

	for(int i = 0; i < placedShipData.size(); i++) {
		std::string destroyedStatus = placedShipData[i]->getIsShipDestroyed() ? "YES" : "NO";

		std::cout << placedShipData[i]->getShipName() << " | " << placedShipData[i]->getShipHealth() << "/" << placedShipData[i]->getShipLength() << " | " << destroyedStatus << "\n";
	}
}

playerUniquePlacementStatus GameHandler::hasChoosenUniqueMissleFire(std::string coord) {

	//infinite loop fix this

	// if(playerMissleHits.empty()) {
	// 	return YES;
	// }

	// for(int i = 0; i < playerMissleHits.size(); i++) {

	// 	std::cout << "COORD: " << playerMissleHits[i];
	// 	std::cout << "PLAYER COORD: " << coord;

	// 	if(playerMissleHits[i] == coord) {
	// 		return NO;
	// 	}
	// }

	return YES;
}