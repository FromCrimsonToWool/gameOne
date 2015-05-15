#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

//Return the resource path for resources located in res/subDir
std::string getResourcePath(const std::string &subDir = "") {
	//Determine path separator based on the OS.
	#ifdef _WIN32
		const char PATH_SEP = '\\';
	#else
		const char PATH_SEP = '/';
	#endif
	
	//Hold the base of the resource path, i.e. 'Projects/res'
	//Static so that in multiple callings of the function the baseRes
	//is only calculated once.
	static std::string baseRes;
	if(baseRes.empty()) {
		//SDL_GetBasePath will return NULL is it fails.
		char* basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		} else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		
		//Replace the ending 'bin/' in SDL's base path to get the resource path.
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}

	//If we specified a subdirectory to acquire return it appended to the end
	//of the resource path else simply return the base resource path.
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

#endif
