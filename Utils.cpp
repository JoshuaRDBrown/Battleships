#include "Utils.h"

std::vector<std::string> Utils::parseGameConfigFile(const std::string& data, const std::string& seperator) {
	std::vector<std::string> objects;

	size_t prevPos = 0, pos = 0;

	while(pos < data.length() && prevPos < data.length()) {
		pos = data.find(seperator, prevPos);

		if(pos == std::string::npos) {
			pos = data.length();
		}

		std::string object = data.substr(prevPos, pos);

		if(!object.empty()) {
			objects.push_back(object);
		}

		prevPos = pos + seperator.length();
	}	

	return objects;
};

std::string Utils::convertStringToUpperCase(std::string str) {
	std::string uppercaseString;

	for (int i=0; i< str.length(); i++) {
		uppercaseString += putchar(toupper(str[i]));
	}

	return uppercaseString;      
};

RowAndCol Utils::getIndexFromCoordinates(char *lettersArray, std::string coordinates) {

	RowAndCol result;
	int indexOfLetter;
	std::string numberCoords;

	//Compares values in the letters array to the letter value inputted and records the index of a match

	for(int i = 0; i < 26; i ++) {
		if(lettersArray[i] == coordinates.at(2)) {
			indexOfLetter = i;
		}
	}

	//Filters the coords to get only the number coords
	for(int j = 0; j < coordinates.length(); j++) {
		if(isdigit(coordinates[j])) {
			numberCoords += coordinates[j];
		}
	}

	if(numberCoords.at(0) == '0') {
		numberCoords.erase(0, numberCoords.find_first_not_of('0'));
	}

	try {
		result.row = std::stoi(numberCoords) - 1;
	} catch(...) {
		result.row = 0;
	}
	
	result.col = indexOfLetter;

	return result;
};

int Utils::randomNumber(int range) {
	//generates a unique seed based on the current time to ensure a 'random' number is generated.
	srand(time(NULL));
	return rand() % range;
};