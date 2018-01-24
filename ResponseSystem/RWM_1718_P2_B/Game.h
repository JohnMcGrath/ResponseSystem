#pragma once

#include <vector>
#include "EventListener.h"
#include "LTimer.h"
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Box2D\Box2D.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Renderer.h"
#include "Player.h"
/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	unsigned int lastTime;//time of last update;

	bool pause = true;
	bool quit;
	bool nextLevel;
	bool drownState = false;

	enum GameState {
		STARTSCREEN,
		GAMEPLAY,
		PAUSE,
		OPTIONS,
		ENDSCREEN,
	};

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;

	bool gameRunning = true;
	bool musicPlaying = false;


	bool wallBroke = false;
	SDL_Rect box;
	SDL_Point center;
	SDL_Texture* bWallTexture;


	SDL_Texture* startScreenTexture = NULL;
	SDL_Texture* startScreenIcon = NULL;


public:
	Game();
	~Game();

	bool init();

	void destroy();

	void update();
	void render();
	void loop();

	void onEvent(EventListener::Event);

private:
	Player* m_player = new Player(gameRenderer);

};

