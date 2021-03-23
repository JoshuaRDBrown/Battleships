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



