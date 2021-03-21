#include <iostream>
#include <vector>
#include "./structs/RowAndCol.h"

class Utils {
	
	public:
		std::vector<std::string> parseGameConfigFile(const std::string& data, const std::string& seperator);
		std::string convertStringToUpperCase(std::string str);
		RowAndCol getIndexFromCoordinates(std::vector<std::string> columnLetters, std::string coordinates, int width);
		int randomNumber(int range);
		std::vector<std::string> splitInputCoords(std::string coords);
};