#include <iostream>
using namespace std;

#include "LTimer.h"
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Box2D\Box2D.h"


const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game()
{
	//Initialises SDL Image to use PNGs
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "Error : PNG Did not load";
	}

	gameWindow = SDL_CreateWindow("Response System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
}


Game::~Game()
{
}


bool Game::init() 
{
	quit = false;
	return true;
}

void Game::destroy()
{
}

//** calls update on all game entities*/
void Game::update()
{
}

//** calls render on all game entities*/

void Game::render()
{
	SDL_RenderClear(gameRenderer);
	SDL_RenderPresent(gameRenderer);
}

/** update and render game entities*/
void Game::loop()
{
	LTimer capTimer;//to cap framerate

	int frameNum = 0;
	while (!quit)
	{
		capTimer.start();
		render();
		update();
	}

	int frameTicks = capTimer.getTicks();//time since start of frame
	if (frameTicks < SCREEN_TICKS_PER_FRAME)
	{
		//Wait remaining time before going to next frame
		SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
	}
}

void Game::onEvent(EventListener::Event evt) 
{
}