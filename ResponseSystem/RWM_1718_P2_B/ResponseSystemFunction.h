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

struct Impulse
{
	b2Vec2 offSetPos;
	float forceScaler;
	float angle;
	float delay;
	bool onOff = false;
	std::string id;
};

struct BodyID
{
	b2Body* body;
	std::string id;
};

struct ResponsePair
{
	std::string bodyName;
	std::string impulseName;
};

class ResponseSystemFunction
{

public:
	ResponseSystemFunction(b2Vec2 offSetPos, float forceScaler, float angle, float delay, std::string id);
	void Update();
	void AddImpulse(Impulse* newImpulse);
	void AddBody(b2Body* newBody, std::string bodyName);
	std::vector<Impulse*> GetImpulses() { return m_impulses; }
	Impulse* GetSpecificImpulse(std::string idToFind);
	b2Body* GetSpecificBody(std::string idToFind);
private:
	std::vector<b2Body*> m_otherBodies;
	std::vector<BodyID*> m_bodies;
	std::vector<Impulse*> m_impulses;
	std::vector<std::string> m_bodyIDs;

	Impulse tempImpulse;
	BodyID protoBodyID;
};