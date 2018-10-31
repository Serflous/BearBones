#pragma once

#include "Objects/Entity.h"
#include "Objects/World.h"

class AffordanceEngine
{
public:
	AffordanceEngine();
	~AffordanceEngine();
	void SetWorld(std::shared_ptr<Objects::World> world);
	void AffordanceEngine::ChangeAffordance(std::shared_ptr<Objects::Entity> entity1);
private:
	std::shared_ptr<Objects::World> m_world;

};

