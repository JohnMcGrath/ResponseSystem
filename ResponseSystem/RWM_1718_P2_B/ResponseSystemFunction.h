#pragma once
#include "Box2D\Box2D.h"
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "EventListener.h"
#include "LTimer.h"

class ResponseSystemFunction
{
	struct Impulse 
	{
		b2Vec2 offSetPos;
		float forceScaler;
		float angle;
		float delay;
		bool onOff = false;
		std::string id;
	};

public:
	ResponseSystemFunction(b2Vec2 offSetPos, float forceScaler, float angle, float delay, std::string id);
	void Update();
	bool AddImpulse(Impulse newImpulse);
	std::vector<Impulse> GetImpulses() { return m_impulses; }
private:
	std::vector<Impulse> m_impulses;
};