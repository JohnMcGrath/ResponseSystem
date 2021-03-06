#include "ResponseSystemFunction.h"

/// <summary>
/// Constructor for the Response System
/// </summary>
/// <param name="offSetPos">Where on the body that the force will be applied</param>
ResponseSystemFunction::ResponseSystemFunction()
{
	//Tutorial message for users
	std::cout << "Press Q to see: Up and zag down" << std::endl;
	std::cout << "Press W to see: Around in a square" << std::endl;
	std::cout << "Press E to see: Zig Zag" << std::endl;
	std::cout << "Press R to: Reset Position" << std::endl << std::endl;
	std::cout << "Press an arrow key to move in any direction for half a second" << std::endl;
	std::cout << "Combine the simple and premade advanced moves and mess around" << std::endl;
}

/// <summary>
/// Creates an impulse and add it to its vector of impulses
/// </summary>
/// <param name="offSetPos">Where on the body that the force will be applied</param>
/// <param name="forceScaler">Scaler to be applied to the force of impulse</param>
/// <param name="angle">Angle in degrees with 90 degree being straight up</param>
/// <param name="delay">The amount of time you want to pass before an impulse occurs after being turned on</param>
/// <param name="ttl">How long you want the impulse to occur for</param>
/// <param name="id">id you wish to name this particular impulse</param>
void ResponseSystemFunction::CreateImpulse(b2Vec2 offSetPos, float forceScaler, float angle, float delay, float ttl, std::string id)
{
	/*
	All values are passed to an Impulse object
	A copy of this object is passed along and pushed back
	into the vector of impulses
	*/
	protoImpulse.offSetPos = offSetPos;
	protoImpulse.forceScaler = forceScaler;
	protoImpulse.angle = angle;
	protoImpulse.ttl = ttl;
	protoImpulse.delay = delay;
	protoImpulse.id = id;

	m_impulses.push_back(protoImpulse);
}

/// <summary>
/// Quickly add a pre existing impulse to the vector
/// Can be used to make a second copy of an impulse if needed
/// </summary>
/// <param name="newImpulse">The impulse that you wish to push back</param>
void ResponseSystemFunction::AddImpulse(Impulse newImpulse)
{
	m_impulses.push_back(newImpulse);
}

/// <summary>
/// Creates a ResponsePair that attaches an object with an impulse
/// </summary>
/// <param name="bodyId">The id of the body you wish to attach</param>
/// <param name="impulseId">The id of the impulse you wish to attach</param>
/// <param name="id">The id you wish to give this particualr instance of body and impulse</param>
void ResponseSystemFunction::AddResponsePair(std::string bodyId, std::string impulseId, std::string id)
{
	/*
	All values are passed to an ResponsePair object
	A copy of this object is passed along and pushed back
	into the vector of ResponsePairs
	*/
	protoResponsePair.bodyName = bodyId;
	protoResponsePair.impulseName = impulseId;
	protoResponsePair.id = id;

	m_responsePairs.push_back(protoResponsePair);
}

/// <summary>
/// Allows you to change the value of a pre existing impulse
/// </summary>
/// <param name="fieldToChange">The value you'd like to change;
/// 1 means ForceScaler
/// 2 means Angle
/// 3 means Delay
/// 4 means TTL</param>
/// <param name="newVal">The newValue you'll be using</param>
/// <param name="id">The id of impulse you wish to change</param>
void ResponseSystemFunction::ChangeImpulseValue(float fieldToChange, float newVal,std::string id)
{
	for (size_t i = 0; i < m_impulses.size(); i++) //Go through the vector
	{
		if (m_impulses[i].id == id) //if you find it
		{
			if (fieldToChange == 1) //forcesScaler
			{
				m_impulses[i].forceScaler = newVal;
			}
			else if (fieldToChange == 2) //Angle
			{
				m_impulses[i].angle = newVal;
			}
			else if (fieldToChange == 3)  //Delay
			{
				m_impulses[i].delay = newVal;
			}
			else if (fieldToChange == 4) //Time To Live
			{
				m_impulses[i].ttl = newVal;
			}
		}
	}
}

/// <summary>
/// Allows you to change wether an interaction continues it's momentum after finishing
/// </summary>
/// <param name="fieldToChange">The new value for momentum</param>
/// <param name="id">id of the pair being changed</param>
void ResponseSystemFunction::SetResponsePairMomentumContinue(bool newVal, std::string id)
{
	for (size_t i = 0; i < m_responsePairs.size(); i++) //Go through the vector
	{
		if (m_responsePairs[i].id == id)
		{
			m_responsePairs[i].continueMomentum = newVal;
		}
	}
}
/// <summary>
/// Gets any specific ResponsePair
/// </summary>
/// <param name="idToFind">The id of the ResponsePair you want to get</param>
ResponsePair ResponseSystemFunction::GetSpecificResponsePair(std::string idToFind)
{
	for (size_t i = 0; i < m_impulses.size(); i++)
	{
		if (m_responsePairs[i].id == idToFind) //If the id match the pair's id
		{
			return m_responsePairs[i];
		}
	}
	std::cout << "No response pair with id: " << idToFind << "; found" << std::endl;
	return m_responsePairs[0];
}

/// <summary>
/// Gets any specific Impulse
/// </summary>
/// <param name="idToFind">The id of the Impulse you want to get</param>
Impulse ResponseSystemFunction::GetSpecificImpulse(std::string idToFind)
{
	for (size_t i = 0; i < m_impulses.size(); i++)
	{
		if (m_impulses[i].id == idToFind) //If the id match the impulses's id
		{
			return m_impulses[i];
		}
	}
	std::cout << "No impulse with id: " << idToFind << "; found" << std::endl;
	return m_impulses[0];
}

/// <summary>
/// Creates a bodyID struct using a b2Body and a string 
/// </summary>
/// <param name="newBody">The b2Body you wish to use</param>
/// <param name="bodyName">The id you wish to call the b2Body</param>
void ResponseSystemFunction::AddBody(b2Body* newBody,std::string bodyName)
{
	protoBodyID.body = newBody;
	protoBodyID.id = bodyName;

	m_bodies.push_back(&protoBodyID);
}

/// <summary>
/// Gets any specific Body
/// </summary>
/// <param name="idToFind">The id of the Body you want to get</param>
b2Body* ResponseSystemFunction::GetSpecificBody(std::string idToFind)
{
	for (size_t i = 0; i < m_bodies.size(); i++)
	{
		if (m_bodies[i]->id == idToFind) //If the id match the impulses's id
		{
			return m_bodies[i]->body;
		}
	}
	std::cout << "No body with id: " << idToFind << "; found" << std::endl;
	return m_bodies[0]->body;
}

/// <summary>
/// Turn on a ResponsePair
/// </summary>
/// <param name="id">The id of the ResponsePair you want to turn on</param>
void ResponseSystemFunction::ActivateResponse(std::string id)
{
	for (size_t i = 0; i < m_responsePairs.size(); i++)
	{
		if (m_responsePairs[i].id == id) //if the id matches
		{
			m_responsePairs[i].onOff = true; //value that dictates whether a ResponsePair is occuring
		}
	}
}

/// <summary>
/// Function that checks if each ResponsePair is On or Off
/// If it finds one that is on, it will also perform the movement
/// and time keeping involved
/// </summary>
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
			
			tempImpulse = GetSpecificImpulse(m_responsePairs[i].impulseName);

			/*
			Checks if the time passed since the impulse was turned on is
			greater than the delay of the ResponsePair multiplied by 1000
			(It's easier for the user to visual time in seconds rather than
			milliseconds so this will easily convert it for them)
			The amount of time the delay has occured is calculated by subtracting how much time had
			passed since starting the app right now and when the count started
			*/
			if (SDL_GetTicks() - m_responsePairs[i].delayTimer > (tempImpulse.delay * 1000))
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
				if (SDL_GetTicks() - m_responsePairs[i].timer < (tempImpulse.ttl * 1000))
				{
					tempFloatX = (tempImpulse.angle)*(3.142 / 180); //Converts the angle to radians
					tempFloatY = tempImpulse.forceScaler; //Acts as the impulse's scale factor
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

/// <summary>
/// Update loop of the ResponseSystem
/// </summary>
void ResponseSystemFunction::Update()
{
	CheckIfResponsePairActive();
}