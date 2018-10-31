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

void AffordanceEngine::ChangeAffordance(std::shared_ptr<Objects::Entity> entity1)
{
	entity1->SetAffordances("Rage", 0.5);
}

