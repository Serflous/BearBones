#pragma once
#include "Objects/AffordanceEntity.h"
#include "Objects/World.h"

class AffordanceEngine
{
public:
	AffordanceEngine();
	~AffordanceEngine();
	void SetWorld(std::shared_ptr<Objects::World> world);
	Objects::AffordanceEntity ChangeAffordance(Objects::AffordanceEntity entity1);
private:
	std::shared_ptr<Objects::World> m_world;

};

