#include "AffordanceEntity.h"

Objects::AffordanceEntity::AffordanceEntity()
{

}

Objects::AffordanceEntity::~AffordanceEntity()
{

}

void Objects::AffordanceEntity::SetAffordances(std::string key, double value)
{
	m_affordances[key] = value;
}

void Objects::AffordanceEntity::SetAffordanceMap(std::map<std::string, double> map)
{
	m_affordances = map;
}

std::map<std::string, double> Objects::AffordanceEntity::GetAffordances()
{
	return m_affordances;
}