#ifndef GAME_CONFIG_STRUCT
#define GAME_CONFIG_STRUCT

struct GameConfigDetails {
	int boardHeight; 
	int boardWidth;
	std::map<std::string, int> boatData;
};

#endif