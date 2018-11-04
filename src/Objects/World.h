#pragma once

#include <vector>
#include <memory>

#include "Texture.h"
#include "ObjModel.h"
#include "PrimitiveModel.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "AffordanceEntity.h"
#include "RigidBody.h"
#include "NPC.h"
#include "Terrain.h"
#include "../AI/AIEntity.h"
#include "GUI.h"

namespace Objects
{

		/**
		 * The world object contains all the resources used in the game.
		 * @author Mathew Causby.
		 * @version 0.1
		 */
	class World
	{
	public:
		World();
		World(const World & other);
		~World();

			/**
			 * Adds a texture to the world.
			 * @param[in] texture A pointer to the texture.
			 * @sa Objects::Texture
			 */
		void AddTexture(std::shared_ptr<Texture> texture);
			/**
			 * Adds an ObjModel to the world.
			 * @param[in] model A pointer to the ObjModel.
			 * @sa Objects::ObjModel
			 */
		void AddObjModel(std::shared_ptr<ObjModel> model);
			/**
			 * Adds a geometric shape to the world.
			 * @param[in] model A pointer to the PrimitiveModel.
			 * @sa Objects::PrimitiveModel
			 */
		void AddPrimitiveModel(std::shared_ptr<PrimitiveModel> model);
			/**
			 * Adds a static entity to the world.
			 * @param[in] entity A pointer to the static entity.
			 * @sa Objects::StaticEntity
			 */
		void AddStaticEntity(std::shared_ptr<StaticEntity> entity);

			/**
			 * Adds an entity with affordance to the world.
			 * @param[in] entity A pointer to the static entity.
			 * @sa Objects::AffordanceEntity
			 */
		void AddAffordanceEntity(std::shared_ptr<Objects::AffordanceEntity> entity);

			/**
			 * Adds a rigid body to the world.
			 * @param[in] entity A pointer to the rigid body.
			 * @sa Objects::RigidBody
			 */
		void AddRigidBody(std::shared_ptr<Objects::RigidBody> entity);
			/**
			 * Adds terrain to the world.
			 * @param[in] terrain A pointer to the terrain.
			 * @sa Objects::Terrain
			 */
		void AddTerrain(std::shared_ptr<Objects::Terrain> terrain);
			/**
			 * Set the GUI to the window.
			 * @param[in] gui A pointer to the GUI.
			 * @sa Objects::GUI
			 */
		void SetGUI(std::shared_ptr<Objects::GUI> gui);
			/**
			 * Adds a debug object to the world.
			 * @param[in] model A pointer to an entity.
			 * @sa Objects::Entity
			 */
		void Objects::World::AddDebugObject(std::shared_ptr<Objects::Entity> model);
			/**
			 * Adds an NPC to the window.
			 * @param[in] npc A pointer to the NPC.
			 * @sa NPC
			 */
		void AddNPC(std::shared_ptr<NPC> npc);
			/**
			 * Gets the textures currently loaded.
			 * @return A vector of pointers to textures currently in the world
			 */
		std::shared_ptr<std::vector<std::shared_ptr<Texture>>> GetTextures();
			/**
			 * Gets the obj models currently loaded.
			 * @return A vector of pointers to models currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<ObjModel>>> GetOBJModels();	
			/**
			 * Gets the primitive models currently loaded.
			 * @return A vector of pointers to primitive models currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<PrimitiveModel>>> GetPrimitiveModels();
			/**
			 * Gets the static entities currently loaded.
			 * @return A vector of pointers to static entities currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<StaticEntity>>> GetStaticEntities();
			/**
			 * Gets the rigid bodies currently loaded.
			 * @return A vector of pointers to rigid bodies currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>> GetRigidBodies();
			/**
			 * Gets the terrains currently loaded.
			 * @return A vector of pointers to terrains currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Terrain>>> GetTerrains();
			/**
			 * Gets the affordance entities currently loaded.
			 * @return A vector of pointers to affordance entities currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<Objects::AffordanceEntity>>> GetAffordanceEntities();
			/**
			 * Gets the debug objects currently loaded.
			 * @return A vector of pointers to debug objects currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Entity>>> Objects::World::GetDebugObjects();
			/**
			 * Gets the GUI currently loaded.
			 * @return A vector of pointers to the GUI that is currently in the world.
			 */
		std::shared_ptr<Objects::GUI> GetGUI();

			/**
			 * Updates the world's current state.
			 */
		void Objects::World::Update();

	private:
		std::shared_ptr<std::vector<std::shared_ptr<Texture>>> m_textures;
		std::shared_ptr<std::vector<std::shared_ptr<ObjModel>>> m_objModels;
		std::shared_ptr<std::vector<std::shared_ptr<PrimitiveModel>>> m_primitiveModels;
		std::shared_ptr<std::vector<std::shared_ptr<StaticEntity>>> m_staticEntities;
		std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>> m_rigidBodies;
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Terrain>>> m_terrains;
		std::shared_ptr<std::vector<std::shared_ptr<Entity>>> m_debugObjects;
		std::shared_ptr<std::vector<std::shared_ptr<AffordanceEntity>>> m_affordanceEntities;
		std::shared_ptr<std::vector<std::shared_ptr<NPC>>> m_npcs;
		std::shared_ptr<Objects::GUI> m_gui;
	};

}