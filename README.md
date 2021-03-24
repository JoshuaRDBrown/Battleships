# Battleships

Repl link: https://replit.com/@Josh_Brown/AdaShip-Final#main.cpp

## 1) Challenge outline 

## Summary of problem
The challenge given to us in this assignment was to create a version of the classic game Battleships for the command line using C++ and following Object Oriented programming styles. This was to be completed while adherring to a number of rules and playing styles which included the following: 

* A configurable ini file which would dictate how big the board would be and the length and amount of ships that can be placed.
* A clear and easy to use user interface for the menu, setting up the game and for playing the game.
* Different game modes such as player vs computer, player vs player, a salvo mode and a mode which introduces mines. 
* Defensive programming styles which would stop the user inputting invalid data or placing a ship / missile in an invalid space.

## Proposed Solution
Because the objective is to use Object Oriented Programming to create this project, my proposed solution will be to create a number of classes in which each will handle specific segments off the game. I plan to build the following classes: 

`Main()`
Due to rules in C++, my main function is the first entry point of the application. This is where I will first fetch the `config.ini` file and check the data is valid (and throw an error if not) and then store that data in a data structure(probably in an array or a vector). After this, the main function will then display a menu listing the different options for different game modes. Once a user enters a valid menu item number, my program will create 4 new instances of the `Board` class (2 board, 2 hit boards) and an instance of the `GameHandler` class which will be dynamically set with different information based on the menu item selected. The last job of the main function is then to call a method on `GameHandler` called `GameHandler.setUp()` which triggers the games setup phase (more detail below). 

`Board` -
The `Board` class will probably be the biggest and most complex class in the game. The `Board` will be responsible for the following: 

* Getting and setting the height and width of the board and creating a 2D matrix to reflect those numbers. 
* Allowing public access to Board properties such as if the board belongs to a computer player or the players name.
* Rendering the matrix with column numbers and row letters.
* Setting and updating the matrix to have the most recent information to be avaliable for the user such as a newly placed boat or a success missile hit. 
* Handling validation to ensure boat placements are valid coordinates.

`GameHandler`- 
The `GameHandler`is essentially the controller class which ensures that the segements of the game go together nicely. It will be responsible for: 

* Calling the Boards set up methods so that the user(s) can place their boats.
* Creates a gameloop that only ends when one player has won (And constantly checks if the state of the game changes) 
* Prompting the users to fire a missile(or missiles) and will handle invalid input or if the user wishes to quit the game.
* Produce a game log of interesting events happening in the game (such as hitting a ship)
* Providing the health of a players ships by accessing `Ship` data. 
* Accessing Board API's in order to update players hit grids so they know where they have successfully/unsuccessfully hit. 
* Accessing `Ship` API's to check if a game has been won by determining if a user has any remaining ships alive.

`Ship` -
The `Ship` class will be responsible for holding all the information of a given ship. This includes the ships name, the ships length, the ships current health and if the ship is destroyed or not. The ship class with have no methods as such apart from one for taking damage to decrease the health. The `Ship` classes main purpose will be as a data store and getter for common ship information that other areas of my code will use during the game. I plan to store multiple `Ship` instances in a vector which can be looped through when needed. 

`Utils` -
The `Utils` class will be a class full of helpful reusable functions which will do common tasks. This is not required for the game but to achieve higher code maintainability and reduce code duplication I thought this would be a good idea. Types of functions that I would expect to be here would be those for validiating user input or creating random numbers.

## UML diagram
![alt text](https://github.com/JoshuaRDBrown/Battleships/blob/master/README_ASSETS/BattleShips_UML.png)

# Initial working plan

## Overal Approach
The approach and mindset I will take into tackling this coursework will be an iterative and future proofing one. Since each part is an improvement of the last. I will make sure my code is as dynamic as possible. This will make it easier for myself later when I come to start adding more complex features ontop of my already exisitng logic and functionality. As well as this in adherence to the brief, I was also adopt a 'fail fast' approach. This means I will plan to test every function I write to ensure they do exactly what I expect them to do. This will stop myself spending ages later on trying to debug an issue and having to look through hundreds of lines of code. I plan to do this by extracting my functions out into a seperate file and inputting all sorts of data into them in isolation to ensure the correct output is then returned to me so I can ensure the function has no bugs. Finally, I am following a waterfall methodology using the steps of planning -> development -> testing -> submitting. 

I plan to take an Object oriented approach to ensure my code is as readible but also efficent as it can be. I will make use of C++ wide offering of data structures and types such as structs, vectors, maps and arrays to deliver my solution as they make it easy to add, mutate, store and use complex data structures across applications. I will also use good variable and function names to ensure it is easy to read and understand what each part of my code is doing for other developers. My final plan is to always keep it simple, this is important for me as massive abstractions or complex logic is not fun to maintain or to read and overall it also makes stuff harder to test and catch. 

## Development stratergy
My development stratergy is nothing special, I have decided to build it in a "build it when I need it basis". I will follow the mark scheme and build out the features as and when they are required. This means that I will probably build the `Board` and `GameHandler` components first to ensure that the basic game logic can be written out first so I can build upon these later when the requirements increase in size and complexity. 

## Decomposition of problem into epics
To keep this project managable and easy to follow. I have split up the workload into some smaller chunks or epics:

* EPIC 1 - Display a working menu 
* EPIC 2 - Parse ini file and make that data accessible 
* EPIC 3 - Ship placing logic which updates the grid in real time 
* EPIC 4 - Validate the users input for placing ships and allow auto placement 
* EPIC 5 - Create a turn based system which allows users to fire and update this information in real time 
* EPIC 6 - Check if the game has been won 
* EPIC 7 - Allow the user to quit and reset the game
* EPIC 8 - Add Salvo 
* EPIC 9 - Add Mines

## Object-Oriented design ideas
As stated before, I have seperated each game functions such as rendering the board or holding the ship information to different classes. I believe classes should be dynamic and reusable. This helps as the users need 4 boards (2 hit boards and 2 normal boards) as well as 5 + ships for each player which needs to be stored. This is where we will really see the benefit of Object Oriented design as it helps keep track of all of these different data in a readible and concise way. 

My plan is that ship class instances will live in the board class matrix. This allows constant and easy access to set / get it's current values and removes the problem of data being outdated or out of sync. Using this will also make it easier to integrate the other game modes later on as it will all inherit this logic. 

# Development

# Good programming standards 

Good programming pratice is important for so many reasons. Firstly it allows you to build more robust and safe systems which are relatively bug free and work exactly how the developer intends them too. As well as this, well written code is easy to read which means that when another developer comes along to make changes to your code, they can easily understand what is going on. Without this, code can become unmaintainable and it can become really hard or really hacky to impliment new features. This has the benefit of reducing development and code renovation time in the future, future proofing the software. 

Some key programming standards I will follow in this project are : 

* DRY - Don't repeat yourself. There are some exceptions to this rule as sometimes it's important to choose readibility over repeated logic as abstracted logic can be hard to follow and it can get confusing if you have to read multiple layers of files to get to the source of some logic 10 files deep. 

* Clear and obvious variable and functions name - Another one for readibility, I will make sure my variable and function names fully reflect their purpose. 

* Code re-use - Where possible, I will try to re use as much logic as I can. This is my action plan with the `Utils` class as it will store lots of reuseable logic which otherwise would be repeated in the codebase many times. 

* Code refactoring - It's important to read the code you've written and look for changes / improvements. There's always a better way to approach a solution. It's a good thing to just get it working first but it is just as important you come back and polish it up into a nice looking logical solution. 

# Development part 1 - Menu and game config parseing 

## Implimentation

The first component I decided to build was the menu and config, this makes sense as it is the entry point of the game and everything will be actioned from this screen and the whole game will be affected by the config. 

I did this by parsing the data in the file by seperating by the equals sign in the file: 

```C++ 
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
 ```
 
 How this works is, if the config element is not the board it has to be a boat. The code tries to store the boat name and boat length in a key-value `pair` which we then will pass to the Board and Ship classes later on so they can use this data. If the data is the board, we split the height and the width by searching for the "by" symbol and splitting it that way. 

I created the menu by using a simple switch statement which numbers correspond to a number in the UI, which depending on which number the user picks, generates new boards for that given gamemode: 

```C++
switch(std::stoi(userInput)) {
	case 1: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, true, NORMAL);
	case 2: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, false, NORMAL);
	case 3: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, true, SALVO);
	case 4: initialisePlayerBoards(gameConfig.boardHeight, gameConfig.boardWidth, gameConfig.boatData, false, SALVO);					
	case 5: return 0; 
	default: throw std::invalid_argument("");
}
```

As you can see, depending on which option the user chooses, the game initialises player boards with the configs `boardHeight` and `boardWidth`, if a computer board will be needed and if the game mode is normal or salvo. 

`initalisePlayerBoards` is a function which takes this data and creates new instances of my Board class (which I implimented next) and passes all of the game config details to the `Board`. After the boards have been init'd. The references to these classes are then passed to my `GameHandler` class which will handle the game flow. Finally gameHandlers `setUp()` function is called so that the user can start to place ships. 

```C++ 
int initialisePlayerBoards(int boardHeight, int boardWidth, std::map<std::string, int> boatData, bool isAgainstComputer, GameMode gameMode) {
	
	Board player1Board(boardHeight, boardWidth, boatData, false, "Player 1");
	Board player2Board(boardHeight, boardWidth, boatData, isAgainstComputer, "Player 2");

	Board player1HitBoard(boardHeight, boardWidth, boatData, false, "Player 1's hit board");
	Board player2HitBoard(boardHeight, boardWidth, boatData, isAgainstComputer, "Player 2's hit board");

	GameHandler gameHandler(&player1Board, &player2Board, &player1HitBoard, &player2HitBoard, gameMode);
	int setUpStatus = gameHandler.setUp();
```

## Code review 

I think the above code makes sense to begin the project with. Not only does it future proof the game (by dynmically allowing the addition of more gamemodes and board dimensions) but it is also easy to read what is going on because of how I've created functions to handle logic in small reusable formats. 

I think this was a good decision because it allowed me to start off being dynamic which paved the way to continue the project in a similar manor.

## Changes 

A change I had to make was having to refactor the parsing logic for the board. I found an issue where smaller boards (such as 5x5) broke the game due to index being out of range. This was because I was explicitly looking for 2 numbers for each side and when that second index didn't exist, it would throw an `out_of_range` error: 
 
 ```C++ 
 std::string boardHeight = std::to_string(data[1].at(0) + data[1].at(1) 
 std::string boardWidth = std::to_string(data[1].at(2) + data[1].at(3) 
 ```
 
The fix for this you saw previously, I looped through the string and stored the data dynamically, anything before the "x" was the height and anything after would be width allowing it to be any length (Although I do check if it's over 80 or under 5 as stated in the brief). 

# Development part 2 - Board 

The next part of the game I built out was the `Board` class. The board class handles quite a lot of logic, the first thing I built out was the ability to display a grid on the screen. I used a `std::vector<std::vector<std::string>>` or a 2D vector to store the grid positions and boat positions in. The width and height was set dynamically on init: 

```C++ 
			if(boardWidth > 26) {

				int firstColumnLetterIndex = 0;

				for(int i = 0; i < boardWidth - 26; i++) {

					if(i % 26 == 0 && i != 0) {
						firstColumnLetterIndex ++;
					}
					
					std::string columnName = columnLetters[firstColumnLetterIndex] + columnLetters[i >= 26 ? i - 26 : i];
					columnLetters.push_back(columnName);
				}
			}

			matrix.resize(width, std::vector<std::string>(height, " "));
    }
```

The first bit of logic creates the column names, if the column index is further than the amount of alphabetical characters in the alphabet, we add the first letter of the alphabet to the end and loop again and again until ZZ (Which is way more columns than the game allows anyway).

The last bit of logic `matrix.resize(width, std::vector<std::string>(height, " "));` is the most important part here, it resizes the matrix to the config width and height and fills those indexes with a `" "` (which will be changed to boats or hits later on).

I then loop through this matrix using the following code: 

```C++
void Board::drawBoard() {
	std::cout << "\n" << name << "\n";

	std::cout << "     ";
	for (int i = 0; i < height; i ++) {
		if(i >= 25) {
			std::cout << columnLetters[i] << "  ";
		} else {
			std::cout << columnLetters[i] << "   ";
		}
		
	}

	std::cout << std::endl;

	for(int j = 0; j < width; j++) {
			
		if(j < 9) {
			std::cout << " " << j + 1 << " | ";
		} else {
			std::cout << j + 1 << " | ";
		}
			
		for(int k = 0; k < height; k++){
			std::cout << matrix[j][k] << " | ";
		}

		std::cout << std::endl;	
	}
}
```
Which renders a board with numbers row and alphabetical collumns by looping through each vector. Which produces this output: 

```Shell 
     A   B   C   D   E   F   G   H   I   J   
 1 |   |   |   |   |   |   |   |   |   |   | 
 2 |   |   |   |   |   |   |   |   |   |   | 
 3 |   |   |   |   |   |   |   |   |   |   | 
 4 |   |   |   |   |   |   |   |   |   |   | 
 5 |   |   |   |   |   |   |   |   |   |   | 
 6 |   |   |   |   |   |   |   |   |   |   | 
 7 |   |   |   |   |   |   |   |   |   |   | 
 8 |   |   |   |   |   |   |   |   |   |   | 
 9 |   |   |   |   |   |   |   |   |   |   | 
10 |   |   |   |   |   |   |   |   |   |   | 
```

## Code review

I think this part was pretty easy to do. There are not too many ways you can render a grid so I believe looping through a 2D vector was probably best practice in this approach. It also gave me the option to use nice C++ API's such a `Vector.resize` which made it even easier to dynamically set the size and the data inside of the grid instead of having to push the rows mannually which was really nice. 

## Changes

The only change I made here was that I was originally using a 2D array with a fix height and width of 10, which of course would not help me when trying to make it dynamic so I changed and opted for a 2D vector afterwards to fix this. 

# Development part 3 - Ship placement

The `Ship` class is probably the least complex class as it only has 1 function and the rest are get methods. I think I used the `Ship` class more of a structure / data store as I was reading data a lot but rarely writing to it. I need to know the following things about a Ship: 

* It's name (BattleShip, Carrier etc) 
* It's length
* It's health
* The position of the ship on the grid
* If the ship is destroyed

The first two points I get from the config file, which is pretty easy to store, the rest I have to take from the user and calculate myself. To get the ships position, I went to my `Board` class and wrote some input statements so that the user had the ability to enter data for their ship location like so: 

```C++ 
std::cout << "SETUP PHASE - Press R to reset or Q to quit at anytime.";
std::cout << "\nEnter the coordinates for the " << shipName << " - " << "which has a length of " << std::to_string(shipLength) << "(E.g 1B or press enter for random generation): ";
getline(std::cin, coordinates);
```

After verifying this logic (by checking it's the correct length, the correct format and is actually a place on the board) I then set the Ship placement on the `Board` by adding the ships initial to be placed at that index. This is a loop so this will do this while increasing the index by 1 for the length of the ship: 

```C++ 
if(matrix[coordIndex.row][coordIndex.col + i] == " ") {
	matrix[coordIndex.row][coordIndex.col + i] = shipInitial;
} else {
	return INVALID;
}
```
After this, all that data is then stored in a new `Ship` instance which is then pushed to a vector of `Ship` instances where all this data can be accessed in the `Board` class: 

```C++ 
placedShips.push_back(new Ship{shipInitial, shipName, shipLength, coordIndex, orientation});
```

After this I added some get methods to the `Ship` class to make it easy to get certain data about a specific instance and added a function which takes away some health (which should be called later if part of the ship has been hit): 

```C++ 
void Ship::takeDamage() {
	shipHealth = shipHealth -1;

	if(shipHealth == 0) {
		isDestroyed = true;
	}
}

char Ship::getShipInitial() {
	return shipInitial;
}

bool Ship::getIsShipDestroyed() {
	return isDestroyed;
}

std::string Ship::getShipName() {
	return shipName;
}
```

## Code review

I liked this approach as it was simple and easy to understand. It could be a bit complex for new programmers but this is one of the fundermental skills and benefits of Object-Oriented programming. This follows good practices of class prototyping to make it easy to transfer data between classes and functions. 

## Changes 

I began by trying to store the data of the `Ship` in the board, but then I realised this means that the ship data would be confined to the `Board` class and it wouldn't be able to be easily accessed elsewhere. That's when I decided to then put them into a vector which has a getter to be retrived throughout my application. 

# Development 4 - Game loop

The final part of development was defining the game loop. This was pretty simple as it just requires the same logic to be ran over and over until a winner breaks this loop. How this works is I create a while loop which ran the following logic: 

``` C++ 
		Board * currentPlayer = turnCount % 2 == 0 ? player2 : player1;
		Board * opponent = turnCount % 2 == 0 ? player1 : player2;
		Board * currentPlayerHitBoard = currentPlayer->getPlayerName() == "Player 1" ?  player1HB : player2HB;
    attemptFireMissile(currentPlayer, opponent, currentPlayerHitBoard);
```

Depending on if the turn is odd / even, the player `Board` class will switch to the currently playing user. This data is then passed to the `attemptFireMissile` function where the users input is then taken and then similar logic to above with placing ships.

I wrote some logic which checks if the users inputted coord grid position is occupied by an enemy ship. If so then I add a little X to the opponents board and the currentPlayers hit board, I am also checking if all the opponent ships are destroyed, in which case we can end the game: 

```C++ 
if(opponentMatrix[index.row][index.col] == shipInitalAsString) {
				opponentShips[i]->takeDamage();
				opponent->setMissleLocationOnHitGrid(index, "X");
				currentPlayerHitBoard->setMissleLocationOnHitGrid(index, "X");

				if(opponentShips[i]->getIsShipDestroyed()) {
					std::cout << "Your missile has destroyed an enemy ship!\n";
					opponent->setDestroyedShipAmount();
					checkIfGameEnd(opponent->getDestroyedShipAmount(), opponentShips.size(), currentPlayer);
				}
```

## Code review

The part of the code took a lot of thinking. I had to take into account the different game modes. This started as a singular operation but after I implimented Salvo I had to loop through this logic a few times each turn which was tricky to get right. But overall I'm happy with how it turned out as a lot of the work needed I had already implimented so it wasn't much work to get working quickly.

## Changes 

As stated above the main change was allowing multiple missile hits for Salvo mode. As well as this, I had to change the logic to be able to handle different amounts of inputs, which meant in some situations I should allow spacing in input for such things as "1A 2A 3A" etc. 
