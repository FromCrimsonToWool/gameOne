#ifndef LOGSDLERROR_H
#define LOGSDLERROR_H

//Standard Include
#include <iostream>
#include <fstream>

/**
* Log an SDL error with some error message to the given output steam.
* @param os The output stream to write the message to.
* @param msg The error message to write, format will be msg error: SDL_GetError()
**/
void logSDLError(std::ostream& os, const std::string& msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ofstream errorLog; errorLog.open("CotWErrorLog.txt");
	errorLog << msg << " error: " << SDL_GetError() << std::endl;
	errorLog.close();
}

#endif
