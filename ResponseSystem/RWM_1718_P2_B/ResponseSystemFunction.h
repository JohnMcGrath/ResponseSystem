#pragma once
#include "Box2D\Box2D.h"
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "EventListener.h"
#include "LTimer.h"
#include "SDL.h"

struct Impulse
{
	b2Vec2 offSetPos;
	float forceScaler;
	float angle;
	float ttl;
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
	bool onOff = false;
	bool continueMomentum = false;
	Uint32 timer = 0;
	Uint32 delayTimer = 0;
	bool timerStarted = false;
	bool delayTimerStarted = false;
	std::string id;
};

class ResponseSystemFunction
{

public:
	ResponseSystemFunction(b2Vec2 offSetPos, float forceScaler, float angle, float delay, std::string id);

	void Update();
	void CheckIfResponsePairActive();

	void AddImpulse(Impulse newImpulse);
	void AddBody(b2Body* newBody, std::string bodyName);
	void AddResponsePair(std::string bodyId, std::string impulseID, std::string id);

	void ActivateResponse(std::string id);
	void CreateImpulse(b2Vec2 offSetPos, float forceScaler, float angle, float delay,float ttl, std::string id);
	std::vector<Impulse> GetImpulses() { return m_impulses; }
	Impulse GetSpecificImpulse(std::string idToFind);
	b2Body* GetSpecificBody(std::string idToFind);
	ResponsePair ResponseSystemFunction::GetSpecificResponsePair(std::string idToFind);

private:
	std::vector<BodyID*> m_bodies;
	std::vector<Impulse> m_impulses;
	std::vector<ResponsePair> m_responsePairs;
	std::vector<std::string> m_bodyIDs;
	std::vector<float> m_timers;
	float timer = 0;

	float tempFloatX = 0;
	float tempFloatY = 0;

	Impulse tempImpulse;
	Impulse usingImpulse;
	BodyID protoBodyID;
	ResponsePair protoResponsePair;
};