#include "Game.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/// <summary>
/// Constructor for the Game
/// </summary>
Game::Game()
{
	//Initialises SDL Image to use PNGs
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "Error : PNG Did not load";
	}

	//Create the Window and Renderer
	gameWindow = SDL_CreateWindow("Response System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	//Player
	pShape.SetAsBox(25, 25, b2Vec2(12.5,12.5),0);
	pBodyDef.type = b2_dynamicBody;
	pBodyDef.position.Set(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//Create the player's body
	pBody = world.CreateBody(&pBodyDef);
	pBody->CreateFixture(&pShape, 1.0f);

	//add the player's body and id it "player"
	m_rsSysFun.AddBody(pBody, "player");

	//Creating the impulses
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 20, 0, 2, "lowerJump");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 50000, 45, 0, 2, "standardJump");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 900000, 65, 0, 2, "higherJump");

	//Simple direction movements
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 90, 0, 1, "Up");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 180, 1, 1, "Left");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 270, 2, 1, "Down");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 0, 3, 1, "Right");

	//Angled movements
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 45, 0, 1, "UpZig");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, -45, 1, 1, "DownZag");

	//Create a pair between the player and zig, zag impulses
	m_rsSysFun.AddResponsePair("player", "UpZig", "pUpZig");
	m_rsSysFun.AddResponsePair("player", "DownZag", "pDownZag");

	//Create pairs between the layer and movement directions
	m_rsSysFun.AddResponsePair("player", "Up", "pUp");
	m_rsSysFun.AddResponsePair("player", "Left", "pLeft");
	m_rsSysFun.AddResponsePair("player", "Down", "pDown");
	m_rsSysFun.AddResponsePair("player", "Right", "pRight");
	
	//Create pairs with the different jumps
	m_rsSysFun.AddResponsePair("player", "lowerJump", "lJump");
	m_rsSysFun.AddResponsePair("player", "standardJump", "sJump");
	m_rsSysFun.AddResponsePair("player", "higherJump", "hJump");
}

/// <summary>
/// Deconstructor for the Game
/// </summary>
Game::~Game()
{
}

/// <summary>
/// Initialisation for the Game
/// </summary>
bool Game::init() 
{
	quit = false;
	return true;
}


/// <summary>
/// Update loop for the game object
/// </summary>
void Game::update()
{
	//Update the Box2D World
	world.Step(0.1f, 10, 100);

	//Move player pos to their b2 body's pos
	m_player->GetRect()->x = pBody->GetPosition().x;
	m_player->GetRect()->y = pBody->GetPosition().y;
	
	m_rsSysFun.Update(); //Update the response system

	handleInput(); // handle input

	render(); //render the game
}

/// <summary>
/// Handles the keyboard input
/// </summary>
void Game::handleInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type) {
		case SDL_KEYDOWN: //If a key is pressed
			switch (e.key.keysym.sym) {
			case SDLK_q: //Activates both the pUp and pDownZag together
				m_rsSysFun.ActivateResponse("pUp");
				m_rsSysFun.ActivateResponse("pDownZag");
				break;
			case SDLK_w:
				m_rsSysFun.ActivateResponse("pUp");
				m_rsSysFun.ActivateResponse("pLeft");
				m_rsSysFun.ActivateResponse("pDown");
				m_rsSysFun.ActivateResponse("pRight");
				break;
			case SDLK_e:
				m_rsSysFun.ActivateResponse("pUpZig");
				m_rsSysFun.ActivateResponse("pDownZag");
				break;
			case SDLK_r: //Returns the square to the centre of the screen
				pBody->SetTransform(b2Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), pBody->GetAngle());
				break;
			}
			}
		}
}
/// <summary>
/// Renders the game objects
/// </summary>
void Game::render()
{
	//Set the background colour
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);

	//Set the colour for the fill rect
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 255, 255);
	SDL_RenderFillRect(gameRenderer, m_player->GetRect());

	//Set the colour for the outline of the rect
	SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gameRenderer, m_player->GetRect());

	SDL_RenderPresent(gameRenderer);
}

/// <summary>
/// Calculates the froms and when to update
/// </summary>
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