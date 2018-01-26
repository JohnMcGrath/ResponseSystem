#include "ResponseSystemFunction.h"

ResponseSystemFunction::ResponseSystemFunction(b2Vec2 offSetPos, float forceScaler, float angle, float delay, std::string id)
{
	tempImpulse.offSetPos = offSetPos;
	tempImpulse.forceScaler = forceScaler;
	tempImpulse.angle = angle;
	tempImpulse.delay = delay;
	tempImpulse.id = id;

	//Might need to be made as a pointer
	m_impulses.push_back(tempImpulse);
}
void ResponseSystemFunction::CreateImpulse(b2Vec2 offSetPos, float forceScaler, float angle, float delay, float ttl, std::string id)
{
	tempImpulse.offSetPos = offSetPos;
	tempImpulse.forceScaler = forceScaler;
	tempImpulse.angle = angle;
	tempImpulse.ttl = ttl;
	tempImpulse.delay = delay;
	tempImpulse.id = id;

	m_impulses.push_back(tempImpulse);
}
void ResponseSystemFunction::AddImpulse(Impulse newImpulse)
{
	m_impulses.push_back(newImpulse);
}

void ResponseSystemFunction::AddResponsePair(std::string bodyId, std::string impulseId, std::string id)
{
	protoResponsePair.bodyName = bodyId;
	protoResponsePair.impulseName = impulseId;
	protoResponsePair.id = id;

	m_responsePairs.push_back(protoResponsePair);
}
ResponsePair ResponseSystemFunction::GetSpecificResponsePair(std::string idToFind)
{
	for (size_t i = 0; i < m_impulses.size(); i++)
	{
		if (m_responsePairs[i].id == idToFind)
		{
			return m_responsePairs[i];
		}
	}
	return m_responsePairs[0];
}
Impulse ResponseSystemFunction::GetSpecificImpulse(std::string idToFind)
{
	for (size_t i = 0; i < m_impulses.size(); i++)
	{
		if (m_impulses[i].id == idToFind)
		{
			return m_impulses[i];
		}
	}
	//Better value to be implimented
	return m_impulses[0];
}

void ResponseSystemFunction::AddBody(b2Body* newBody,std::string bodyName)
{
	protoBodyID.body = newBody;
	protoBodyID.id = bodyName;

	m_bodies.push_back(&protoBodyID);
}

b2Body* ResponseSystemFunction::GetSpecificBody(std::string idToFind)
{
	for (size_t i = 0; i < m_bodies.size(); i++)
	{
		if (m_bodies[i]->id == idToFind)
		{
			return m_bodies[i]->body;
		}
	}
	return m_bodies[0]->body;
}

void ResponseSystemFunction::ActivateResponse(std::string id)
{
	for (size_t i = 0; i < m_responsePairs.size(); i++)
	{
		if (m_responsePairs[i].id == id)
		{
			std::cout << "IT SHOULD BE ON" << std::endl;
			m_responsePairs[i].onOff = true;
		}
	}
}

void ResponseSystemFunction::CheckIfResponsePairActive()
{
	for (size_t i = 0; i < m_responsePairs.size(); i++) //For loop that goes through all ResponsePairs
	{	
		if (m_responsePairs[i].onOff == true) //if any ResponsePair has been turned on
		{
			if (m_responsePairs[i].delayTimerStarted == false) //if the delay hasn't started being counted yet
			{
				m_responsePairs[i].delayTimerStarted = true; //will now start counting time
				m_responsePairs[i].delayTimer = SDL_GetTicks(); //Gets the current time since the app started
			}
			
			usingImpulse = GetSpecificImpulse(m_responsePairs[i].impulseName);

			/*
			Checks if the time passed since the impulse was turned on is
			greater than the delay of the ResponsePair multiplied by 1000
			(It's easier for the user to visual time in seconds rather than
			milliseconds so this will easily convert it for them)
			The amount of time the delay has occured is calculated by subtracting how much time had
			passed since starting the app right now and when the count started
			*/
			if (SDL_GetTicks() - m_responsePairs[i].delayTimer > (usingImpulse.delay * 1000))
			{
				if (m_responsePairs[i].timerStarted == false) //Starts count of how long it's been occuring now
				{
					m_responsePairs[i].timerStarted = true; //will now start counting time
					m_responsePairs[i].timer = SDL_GetTicks(); //Gets the current time since the app started
				}
				/*
				Checks if the time the response has been on is less than it's time to loive
				Time is has been on is calculated the same as the delay timer
				*/
				if (SDL_GetTicks() - m_responsePairs[i].timer < (usingImpulse.ttl * 1000))
				{
					tempFloatX = (usingImpulse.angle)*(3.142 / 180); //Converts the angle to radians
					tempFloatY = usingImpulse.forceScaler; //Acts as the impulse's scale factor
					/*
					Each pixel is treated as a km in regards to the physics so scaler's a multiplied by 10,000
					so user's don't need to use ridiculously large numbers as scalers.
					*/
					GetSpecificBody(m_responsePairs[i].bodyName)->ApplyForceToCenter(b2Vec2(cos(tempFloatX)*tempFloatY*10000, -sin(tempFloatX) * tempFloatY*10000), true);
				}
				else //The impulse has finished
				{
					/*
					Will stop in place or carry momentmum after finishing depending on whether or
					not the ResponsePair's moment bool is true or false
					*/
					GetSpecificBody(m_responsePairs[i].bodyName)->SetAwake(m_responsePairs[i].continueMomentum);
					m_responsePairs[i].onOff = false; //turn the pair off
					m_responsePairs[i].delayTimerStarted = false; //reset the delay timer
					m_responsePairs[i].timerStarted = false; //rest the timer
				}
			}
		}
	}
}

void ResponseSystemFunction::Update()
{
	CheckIfResponsePairActive();
}