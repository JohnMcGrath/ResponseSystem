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

//Struct used to represent an impulse
struct Impulse
{
	b2Vec2 offSetPos; //offset in regards to the bodys of where the impulse will occur
	float forceScaler; //scaler to increase the force of impulse
	/*
	Angle of the impulse, in degrees. 90 being straight up vertical, 0 being
	to the right, 180 to the left and 270 down
	Easiest way for a user to visualise the movement in their head
	*/
	float angle; 
	float ttl; //Time to live, how long the impluse occurs for, in seconds
	float delay; //How long after being turned on before the impulse occurs
	bool onOff = false; //Whether the impulse is occuring or not
	/*
	id to identify each impulse
	A string is used as it's the easiet for a user to
	remember and make sense of
	*/
	std::string id;
};

//Struct used to tie a b2Body to an id
struct BodyID
{
	b2Body* body; //the b2Body
	std::string id; //the name you wish to call it
};

//Struct used to combine a body with a particular impulse
//The id is called with ActivateResponse(id)
//The impulse will then occur on the body
struct ResponsePair
{
	std::string bodyName; //the id of the body you're using
	std::string impulseName; //the id of the impulse youre using
	bool onOff = false; //represent whether it's occuring or not
	bool continueMomentum = false; //Continue it's momentum after finishing
	Uint32 timer = 0; //timer used by ttl
	Uint32 delayTimer = 0; //timer used by delay
	bool timerStarted = false; //whether the timer has started
	bool delayTimerStarted = false; //whether the delay tinmer has strated
	std::string id; //The id to call to activate the response
};

/// <summary>
/// ResponseSystem designed to be used in conjuction with box2d to easily create advanced
/// movements in a more user friendly and easier to understand manner 
/// </summary>
class ResponseSystemFunction
{

public:
	ResponseSystemFunction(); // Constructor for the Response System

	void Update(); // Update loop for the Response System
	void CheckIfResponsePairActive(); //Checks if each ResponsePair is On or Off

	void AddImpulse(Impulse newImpulse); // Quickly add a pre existing impulse to the vector
	void AddBody(b2Body* newBody, std::string bodyName); // Creates a bodyID struct using a b2Body and a string 
	void AddResponsePair(std::string bodyId, std::string impulseID, std::string id); // Creates a ResponsePair that attaches an object with an impulse

	void ActivateResponse(std::string id); // Turn on a ResponsePair
	void CreateImpulse(b2Vec2 offSetPos, float forceScaler, float angle, float delay,float ttl, std::string id); // Creates an impulse and add it to its vector of impulses
	std::vector<Impulse> GetImpulses() { return m_impulses; } //Get's the vector of impulses
	Impulse GetSpecificImpulse(std::string idToFind); // Gets any specific Impulse
	b2Body* GetSpecificBody(std::string idToFind); // Gets any specific Body
	ResponsePair ResponseSystemFunction::GetSpecificResponsePair(std::string idToFind); // Gets any specific ResponsePair
	void ChangeImpulseValue(float fieldToChange, float newVal, std::string id); //Function To change any impulse's values
	void SetResponsePairMomentumContinue(bool newVal, std::string id); //Function To change any ResponsePair's values

private:
	std::vector<BodyID*> m_bodies; //Vector of bodies
	std::vector<Impulse> m_impulses; //Vector of impulses
	std::vector<ResponsePair> m_responsePairs; //Vector of response pair
	std::vector<std::string> m_bodyIDs; //Vector of bodies with IDs

	//Temp values used in some calculations
	float tempFloatX = 0;
	float tempFloatY = 0;
	Impulse tempImpulse; 

	Impulse protoImpulse; //Impulse used to clone more into vector
	BodyID protoBodyID; //BodyID used to clone more into vector
	ResponsePair protoResponsePair; //ResponsePair used to clone more into vector
};