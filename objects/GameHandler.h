#include <iostream>
#include <map>

enum playerUniquePlacementStatus {
	YES,
	NO
};

class GameHandler {

	private: 

		bool isGameInProgress = true;
		std::vector<std::string> playerMissleHits;

	public:

		Board *player1; 
		Board *player2;
		Board *player1HB;
		Board *player2HB;

		GameHandler(Board *player1Board, Board *player2Board, Board *player1HitBoard, Board *player2HitBoard) {
			player1 = player1Board;
			player2 = player2Board;
			player1HB = player1HitBoard;
			player2HB = player2HitBoard;
		}

		int setUp();
		void mainGameLoop();
		void fireMissile(RowAndCol index, Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard);
		void attemptFireMissile(Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard);
		void checkIfGameEnd(int opponentDestroyedShipAmount, int opponentPlacedShipAmount);
		void showShipStatus(Board * player);
		playerUniquePlacementStatus hasChoosenUniqueMissleFire(std::string coord);
};