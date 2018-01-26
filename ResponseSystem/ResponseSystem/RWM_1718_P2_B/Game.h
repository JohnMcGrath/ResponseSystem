#pragma once
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Renderer.h"
#include "Player.h"
#include "ResponseSystemFunction.h"

/// <summary>
/// The game objct which handles the update loop of the game
/// </summary>
class Game:public EventListener
{
	unsigned int lastTime;//time of last update;

	bool pause = true; //bool to pause
	bool quit; //bool to quit

	SDL_Window* gameWindow; //Game window
	SDL_Renderer* gameRenderer; //Game Render

	b2World world = b2World(b2Vec2(0,0)); //The b2 World, gravity set to (0,0)

	bool gameRunning = true; //Is the game still running

public:
	Game(); //Constructor
	~Game(); //Deconstructor

	bool init(); //Initialisation


	void update(); //Update cycle of the game
	void render(); //Renderer
	void loop(); //Calculates the update cycles
	void handleInput(); //Handles player input
	void Game::onEvent(EventListener::Event evt); //Event handlier
private:
	Player* m_player = new Player(gameRenderer); //The player object

	b2PolygonShape pShape;
	b2CircleShape pCircleShape;
	b2BodyDef pBodyDef;
	b2Body* pBody;


	
	ResponseSystemFunction m_rsSysFun = ResponseSystemFunction();
};

