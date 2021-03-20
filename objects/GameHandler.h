#include <iostream>
#include <map>

enum GameMode {
	NORMAL,
	SALVO,
	MINES
};

class GameHandler {

	private: 

		bool isGameInProgress = true;
		GameMode selectedGameMode;

		Board *player1; 
		Board *player2;
		Board *player1HB;
		Board *player2HB;

	public:

		GameHandler(Board *player1Board, Board *player2Board, Board *player1HitBoard, Board *player2HitBoard, GameMode gameMode) {
			player1 = player1Board;
			player2 = player2Board;
			player1HB = player1HitBoard;
			player2HB = player2HitBoard;
			selectedGameMode = gameMode;
		}

		int setUp();
		void mainGameLoop();
		void fireMissile(RowAndCol index, Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard);
		void attemptFireMissile(Board * currentPlayer, Board * opponent, Board * currentPlayerHitBoard);
		void checkIfGameEnd(int opponentDestroyedShipAmount, int opponentPlacedShipAmount);
		void showShipStatus(Board * player);
};