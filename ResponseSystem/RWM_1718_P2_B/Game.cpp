#include "Game.h"

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

	//Create the Window and Renderer
	gameWindow = SDL_CreateWindow("Response System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	//Player
	pShape.SetAsBox(25, 25, b2Vec2(12.5,12.5),0);
	pBodyDef.type = b2_dynamicBody;
	pBodyDef.position.Set(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	pBody = world.CreateBody(&pBodyDef);
	pBody->CreateFixture(&pShape, 1.0f);

	m_rsSysFun.AddBody(pBody, "player");

	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 1, 0, 2, "lowerJump");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 5000, 270, 0, 2, "standardJump");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 900000, 180, 0, 2, "higherJump");

	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 90, 0, 1, "Up");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 180, 1, 1, "Left");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 270, 2, 1, "Down");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 0, 3, 1, "Right");

	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, 45, 0, 0.9, "UpZig");
	m_rsSysFun.CreateImpulse(b2Vec2(0, 0), 1000, -45, 1, 0.9, "DownZag");

	m_rsSysFun.AddResponsePair("player", "UpZig", "pUpZig");
	m_rsSysFun.AddResponsePair("player", "DownZag", "pDownZag");

	m_rsSysFun.AddResponsePair("player", "Up", "pUp");
	m_rsSysFun.AddResponsePair("player", "Left", "pLeft");
	m_rsSysFun.AddResponsePair("player", "Down", "pDown");
	m_rsSysFun.AddResponsePair("player", "Right", "pRight");

	m_rsSysFun.AddResponsePair("player", "lowerJump", "lJump");
	m_rsSysFun.AddResponsePair("player", "standardJump", "sJump");
	m_rsSysFun.AddResponsePair("player", "higherJump", "hJump");
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

	//pBody->ApplyForceToCenter(b2Vec2(0, 50000), false);

	m_player->GetRect()->x = pBody->GetPosition().x;
	m_player->GetRect()->y = pBody->GetPosition().y;
	//std::cout << "Player Body: " << pBody->GetPosition().x << ", " << pBody->GetPosition().y << std::endl;

	float tempAngle = 0;

	
	m_rsSysFun.Update();

	handleInput();
	render();
}

void Game::handleInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_q:
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
			case SDLK_r:
				pBody->SetTransform(b2Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), pBody->GetAngle());
				break;
			}
			}
		}
}
//** calls render on all game entities*/
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