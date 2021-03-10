#include "Board.h"
#include "GameHandler.h"
#include "../Utils.h"

void GameHandler::setUp() {
	player1->drawBoard(true);
	player2->drawBoard(true);
	promptMissileFire();
}

void GameHandler::promptMissileFire() {

	Utils utils;

	bool isGameInProgress = true;

	int turnCount = 1;

	std::string coordinateToFireUpon;

	while(isGameInProgress) {
		//Using the result of turnCount modulo to determine which player class currently IS NOT the one playing
		Board * currentPlayer = turnCount % 2 == 0 ? player2 : player1;
		Board * opponent = turnCount % 2 == 0 ? player1 : player2;

		if(!currentPlayer->getIsComputerBoard()) {
			std::cout << "Please enter a location to fire (1A): ";
			getline(std::cin, coordinateToFireUpon);

			std::cout << coordinateToFireUpon;
		} else {
			coordinateToFireUpon = player1->generateRandomPlacement(Board::COORD);
		}
	
		if(coordinateToFireUpon.length() == 2) {
			coordinateToFireUpon = "0" + coordinateToFireUpon;
		}

		bool coordIsValid = player1->coordinateIsValid(coordinateToFireUpon);

		if(coordIsValid) {
			char * columnLetters = player1->getColumnLetters();
			RowAndCol index = utils.getIndexFromCoordinates(columnLetters, coordinateToFireUpon);

			fireMissile(index, currentPlayer, opponent);

		}
		turnCount++;
	}
}

void GameHandler::fireMissile(RowAndCol index, Board * currentPlayer, Board * opponent) {

	std::vector< std::vector<std::string> > opponentMatrix = opponent->getBoard();

	if(opponentMatrix[index.row][index.col] != " ") {

		if(!currentPlayer->getIsComputerBoard()) {
			std::cout << "Your missile has hit an enemy ship! \n";
		}
		
		std::vector<Ship*> opponentShips = opponent->getPlacedShipData();
		int destroyedShipAmount = 0;

		for(int i = 0; i < opponentShips.size(); i++) {
			std::string shipInitalAsString;

			if(opponentShips[i]->getIsShipDestroyed()) {
				destroyedShipAmount++;
			}

			char shipInital = opponentShips[i]->getShipInitial();

			shipInitalAsString += shipInital;
			 
			if(opponentMatrix[index.row][index.col] == shipInitalAsString) {
				opponentShips[i]->takeDamage();

				if(opponentShips[i]->getIsShipDestroyed()) {
					bool gameHasBeenWon = checkIfGameEnd(destroyedShipAmount, opponentShips.size());
				}
			}
		}
	} else {

		if(!currentPlayer->getIsComputerBoard()) {
			std::cout << "Your missile failed to hit an enemy ship. \n";
		}
	}
}

bool GameHandler::checkIfGameEnd(int opponentDestroyedShipAmount, int opponentPlacedShipAmount) {

	if(opponentPlacedShipAmount == opponentDestroyedShipAmount) {
		return true;
	}

	return false;

}