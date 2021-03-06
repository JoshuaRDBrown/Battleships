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

RowAndCol Utils::getIndexFromCoordinates(std::vector<std::string> lettersArray, std::string coordinates, int width) {

	RowAndCol result;
	int indexOfLetter;
	std::string numberCoords;

	//Compares values in the letters array to the letter value inputted and records the index of a match

	std::string letterCoords;

	if(coordinates.at(3) != ' ') {
		letterCoords += coordinates.at(2);
		letterCoords += coordinates.at(3);
	} else {
		letterCoords += coordinates.at(2);
	} 
	
	for(int i = 0; i < width; i ++) {
		if(lettersArray[i] == letterCoords) {
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

	return rand() % range;
};

std::vector<std::string> Utils::splitInputCoords(std::string coords) {

	std::vector<std::string> listOfCoords = {};

	std::string currentCoord;

	for(char& c : coords) {
		if(c == ' ') {
			listOfCoords.push_back(currentCoord);
			currentCoord = "";
		} else {
			currentCoord += c;
		}
	}

	listOfCoords.push_back(currentCoord);

	return listOfCoords;
}