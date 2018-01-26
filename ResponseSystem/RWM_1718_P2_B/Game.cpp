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
	pBodyDef.position.Set(100, 100);

	pBody = world.CreateBody(&pBodyDef);
	pBody->CreateFixture(&pShape, 1.0f);

	//Floor
	//
	//MAY CAUSE ISSUE; CENTRE PONIT
	//
	fShape.SetAsBox(SCREEN_WIDTH / 2, 10,b2Vec2(SCREEN_WIDTH / 2,0),0);
	fBodyDef.type = b2_kinematicBody;
	fBodyDef.position.Set(0, 350);

	fBody = world.CreateBody(&fBodyDef);
	fBody->CreateFixture(&fShape, 1.0f);
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

	pBody->ApplyForceToCenter(b2Vec2(0, 50000), false);

	m_player->GetRect()->x = pBody->GetPosition().x;
	m_player->GetRect()->y = pBody->GetPosition().y;
	std::cout << "Player Body: " << pBody->GetPosition().x << ", " << pBody->GetPosition().y << std::endl;

	float tempAngle = 0;

	fRect.w = SCREEN_WIDTH;
	fRect.h = 20;
	fRect.x = fBody->GetPosition().x;
	fRect.y = fBody->GetPosition().y;

	m_rsSysFun.AddBody(pBody, "player");
	
	tempAngle = m_rsSysFun.GetSpecificBody("player")->GetPosition().y;
	std::cout << "Player y: " << tempAngle << std::endl;
	
	m_rsSysFun.GetSpecificImpulse("1")->forceScaler = 1;
	tempAngle = m_rsSysFun.GetSpecificImpulse("1")->forceScaler;
	std::cout << "ForceScaler 1: " << tempAngle << std::endl;

	m_rsSysFun.GetSpecificImpulse("1")->forceScaler = 50;
	tempAngle = m_rsSysFun.GetSpecificImpulse("1")->forceScaler;
	//std::cout << "ForceScaler 2: " << tempAngle << std::endl;

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
			case SDLK_p:
				std::cout << "P Pressed";
				break;
			case SDLK_w:
				std::cout << "W Pressed";
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
	
	//Floor
	SDL_SetRenderDrawColor(gameRenderer, 100, 100, 255, 255);
	SDL_RenderFillRect(gameRenderer, &fRect);

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