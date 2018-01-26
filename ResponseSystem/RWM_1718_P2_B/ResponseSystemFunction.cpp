#include "ResponseSystemFunction.h"

ResponseSystemFunction::ResponseSystemFunction(b2Vec2 offSetPos, float forceScaler, float angle, float delay, std::string id)
{
	tempImpulse.offSetPos = offSetPos;
	tempImpulse.forceScaler = forceScaler;
	tempImpulse.angle = angle;
	tempImpulse.delay = delay;
	tempImpulse.id = id;

	//Might need to be made as a pointer
	m_impulses.push_back(&tempImpulse);
}
void ResponseSystemFunction::CreateImpulse(b2Vec2 offSetPos, float forceScaler, float angle, float delay, float ttl, std::string id)
{
	tempImpulse.offSetPos = offSetPos;
	tempImpulse.forceScaler = forceScaler;
	tempImpulse.angle = angle;
	tempImpulse.ttl = ttl;
	tempImpulse.delay = delay;
	tempImpulse.id = id;

	m_impulses.push_back(&tempImpulse);
}
void ResponseSystemFunction::AddImpulse(Impulse* newImpulse)
{
	m_impulses.push_back(newImpulse);
}

void ResponseSystemFunction::AddResponsePair(std::string bodyId, std::string impulseId, std::string id)
{
	protoResponsePair.bodyName = bodyId;
	protoResponsePair.impulseName = impulseId;
	protoResponsePair.id = id;

	m_responsePairs.push_back(&protoResponsePair);
}
ResponsePair* ResponseSystemFunction::GetSpecificResponsePair(std::string idToFind)
{
	for (size_t i = 0; i < m_impulses.size(); i++)
	{
		if (m_responsePairs[i]->id == idToFind)
		{
			return m_responsePairs[i];
		}
	}
	return m_responsePairs[0];
}
Impulse* ResponseSystemFunction::GetSpecificImpulse(std::string idToFind)
{
	for (size_t i = 0; i < m_impulses.size(); i++)
	{
		if (m_impulses[i]->id == idToFind)
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
		if (m_responsePairs[i]->id == id)
		{
			m_responsePairs[i]->onOff = true;
		}
	}
}

void ResponseSystemFunction::CheckIfResponsePairActive()
{
	std::cout << "SIZE OF VECTOR: " << m_responsePairs.size() << std::endl;
	for (size_t i = 0; i < m_responsePairs.size(); i++)
	{
		std::cout << m_responsePairs[i]->id << std::endl;
		if (m_responsePairs[i]->onOff == true)
		{
			//std::cout << m_responsePairs[i]->id << " IMPULSE ACTIVATED" << std::endl;

			//if the impulses time is over, set off
		}
		else
		{
		//	std::cout << m_responsePairs[i]->id << " IMPULSE NOT ACTIVATED" << std::endl;
		}
	}
}

void ResponseSystemFunction::Update()
{
	CheckIfResponsePairActive();
}