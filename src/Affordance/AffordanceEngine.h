#pragma once

#include "Objects/Entity.h"
#include "Objects/World.h"

/**
 * The engine that handles any affordances that occur.
 * @author
 * @version 0.1
 */
class AffordanceEngine
{
public:
	AffordanceEngine();
	~AffordanceEngine();
	/**
	 * Sets the affordances to the world.
	 * @param[in] world The world to apply affordances to.
	 */
	void SetWorld(std::shared_ptr<Objects::World> world);
	/**
	 * Changes the affordance of an entity.
	 * @param[in] entity1 The entity to have its affordances changed.
	 */
	void AffordanceEngine::ChangeAffordance(std::shared_ptr<Objects::Entity> entity1);
private:
	std::shared_ptr<Objects::World> m_world;

};

