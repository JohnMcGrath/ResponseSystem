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

void ResponseSystemFunction::AddImpulse(Impulse* newImpulse)
{
	m_impulses.push_back(newImpulse);
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