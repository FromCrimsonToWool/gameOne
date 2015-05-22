#include "textFileParser.h"

TextFileParser::TextFileParser() {

}

void TextFileParser::closeRead() {
	fileRead.close();
}

void TextFileParser::closeWrite() {
	fileWrite.close();
}

void TextFileParser::readFile(std::string f) {

}

//Reads from a file and returns the string associated with a particular text code.
std::string TextFileParser::readByCode(std::string filename, std::string textCode, bool keepOpen) {
	std::string readIn;

	if (!fileRead.is_open()) {
		fileRead.open(filename);
	}

	if (fileRead.is_open()) {
		while (getline(fileRead, readIn)) {
			std::size_t found = readIn.find(textCode);
			if (found != std::string::npos) {
				std::string lineIn; std::size_t foundDel1, foundDel2;

				foundDel1 = readIn.find(";");
				foundDel2 = readIn.find(";;;;x");
				if (foundDel1 != std::string::npos && foundDel2 != std::string::npos) {
					lineIn = readIn.substr(foundDel1 + 1, foundDel2 - foundDel1 - 1);
					
					//Parse paragraphs by looking for the '<p>' delimeter and adding '\n \n' to the string.
					std::string returnLine = "";
					foundDel1 = 0;
					foundDel2 = lineIn.find("<p>");
					while (foundDel2 != std::string::npos) {
						returnLine = returnLine + lineIn.substr(foundDel1, foundDel2 - foundDel1 - 1) + "\n \n";
						foundDel1 = foundDel2 + 3; foundDel2 = lineIn.find("<p>", foundDel1);
					}
					foundDel2 = lineIn.find(";;;;x");
					returnLine = returnLine + lineIn.substr(foundDel1, foundDel2 - foundDel1 - 1);
					
					if (!keepOpen) { fileRead.close(); }
					return returnLine;
				}
			}
		}
	} else {
		std::cerr << "Error loading file input (" + filename + ")!" << std::endl;
	}
}