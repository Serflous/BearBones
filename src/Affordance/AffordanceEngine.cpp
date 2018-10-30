#include "AffordanceEngine.h"



AffordanceEngine::AffordanceEngine()
{
}


AffordanceEngine::~AffordanceEngine()
{
}

void AffordanceEngine::SetWorld(std::shared_ptr<Objects::World> world)
{
	m_world = world;
}

Objects::AffordanceEntity AffordanceEngine::ChangeAffordance(Objects::AffordanceEntity entity1)
{
	entity1.SetAffordances("Rage", 0.5);
	return entity1;
}
