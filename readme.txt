Project Gamma
Readme.txt
Julien Fernandes

This document is created to provide information to myself and others on working with my implementation of Project Gamma. As it stands now I am working to make this implementation able to be seamlessly worked on and added to from both my Linux and Windws environment.

Unfortunately due to my overall inexperience with developing in Linux and switching between the two one can forget important things such as, 

"When I compile in Linux which directory should I be running that in? Oh and by the way where is the executable at?"

To answer that question compilation can be run with the simple 'make' command from within the /CastleOfTheWinds/bin directory. The resulting executable is located in /CastleOfTheWinds/Debug. 

Useful Information
1. Command for finding where SDL is installed on Linux and my own SDL installation location

	sdl2-config --cflags --libs

	-I/usr/include/SDL2 -D_REENTRANT
	-L/usr/lib/i386-linux-gnu -lSDL2

