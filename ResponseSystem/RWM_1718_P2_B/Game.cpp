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

	pShape.m_p.Set(100, 100);
	pBodyDef.type = b2_dynamicBody;
	pBodyDef.position.Set(100, 100);

	pBody = world.CreateBody(&pBodyDef);
	pBody->CreateFixture(&pShape, 1.0f);
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
	//Update the Box2D World
	world.Step(0.1f, 10, 100);

	pBody->ApplyForce(b2Vec2(5, 1), b2Vec2(m_player->GetRect()->w / 2, m_player->GetRect()->h / 2), false);

	m_player->GetRect()->x = pBody->GetPosition().x;
	m_player->GetRect()->y = pBody->GetPosition().y;

	std::cout << "Player Body: " << pBody->GetPosition().x << ", " << pBody->GetPosition().y << std::endl;

	render();
}

//** calls render on all game entities*/

void Game::render()
{
	//Set the background colour
	SDL_SetRenderDrawColor(gameRenderer, 255, 0, 0, 255);
	SDL_RenderClear(gameRenderer);
	
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 255, 255);
	SDL_RenderFillRect(gameRenderer, m_player->GetRect());

	SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gameRenderer, m_player->GetRect());

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