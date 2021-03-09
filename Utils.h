#include <iostream>
#include <vector>
#include "./structs/RowAndCol.h"

class Utils {
	
	public:
		std::vector<std::string> parseGameConfigFile(const std::string& data, const std::string& seperator);
		std::string convertStringToUpperCase(std::string str);
		RowAndCol getIndexFromCoordinates(char *columnLetters, std::string coordinates);
		int randomNumber(int range);
};
