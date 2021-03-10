#include <iostream>
#include <map>

class GameHandler {

	public: 

		Board *player1; 
		Board *player2;

		enum gameStatus {
			IN_PROGRESS
			OVER
		}

		GameHandler(Board *player1Board, Board *player2Board) {
			player1 = player1Board;
			player2 = player2Board;
		}

		void setUp();
		void promptMissileFire();
		void fireMissile(RowAndCol index, Board * currentPlayer, Board * opponent);
		bool checkIfGameEnd(int opponentDestroyedShipAmount, int opponentPlacedShipAmount);
};