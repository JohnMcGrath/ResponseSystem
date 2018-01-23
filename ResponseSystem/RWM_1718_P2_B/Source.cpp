// MyPuzzler.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"



#include <iostream>
using namespace std;
#include "Game.h"


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Game game;

	if (!game.init()) {
		cout << "Failed to init game" << '\n';
	}

	//run the game loop
	game.loop();

	game.destroy();

	return 0;
}