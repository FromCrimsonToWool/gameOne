#ifndef TEXTFILEPARSER_H
#define TEXTFILEPARSER_H

//Standard Include
#include <iostream>
#include <fstream>
#include <string>

class TextFileParser {
	private:
		std::ifstream fileRead;
		std::ofstream fileWrite;

	public:
		//Constructors
		TextFileParser();

		//File Input
		void closeRead();
		void closeWrite();
		void readFile(std::string filename);
		std::string readByCode(std::string filename, std::string textCode, bool keepOpen = true);
};

#endif //TEXTFILEPARSER_H INCLUDED