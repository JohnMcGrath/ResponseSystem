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

	b2World world = b2World(b2Vec2(0,0));

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
	void handleInput();

	void onEvent(EventListener::Event);

private:
	Player* m_player = new Player(gameRenderer);

	b2PolygonShape pShape;
	b2CircleShape pCircleShape;
	b2BodyDef pBodyDef;
	b2Body* pBody;

	SDL_Rect fRect;
	b2PolygonShape fShape;
	b2BodyDef fBodyDef;
	b2Body* fBody;
};

