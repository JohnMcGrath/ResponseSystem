#pragma once
#include"Particle.h"

class Emitter
{
public:
	Emitter(int x, int y, SDL_Renderer *r);
	~Emitter();

	void handleEvent(SDL_Event &e);

	void changePos();

	void Render(SDL_Renderer *r);
	void setXPos(int x) { mXPos = x; }
	void setYPos(int y) { mYPos = y; }

private:
	Particle* particles[20];
	void renderParticles();
	int mXPos;
	int mYPos;

};