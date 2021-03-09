class GameHandler {

	public: 

		Board *player; 
		Board *computer;

		GameHandler(Board *playerBoard, Board *computerBoard) {
			player = playerBoard;
			computer = computerBoard;
		}

		void setUp();
};