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
			 * @param[in] A pointer to the texture.
			 * @sa Objects::Texture
			 */
		void AddTexture(std::shared_ptr<Texture> texture);
			/**
			 * Adds an ObjModel to the world
			 * @param[in] A pointer to the ObjModel
			 * @sa Objects::ObjModel
			 */
		void AddObjModel(std::shared_ptr<ObjModel> model);
		void AddPrimitiveModel(std::shared_ptr<PrimitiveModel> model);
			/**
			 * Adds a static entity to the world
			 * @param[in] A pointer to the static entity.
			 * @sa Objects::StaticEntity
			 */
		void AddStaticEntity(std::shared_ptr<StaticEntity> entity);

		void AddAffordanceEntity(std::shared_ptr<Objects::AffordanceEntity> entity);

		void AddRigidBody(std::shared_ptr<Objects::RigidBody> entity);
		void AddTerrain(std::shared_ptr<Objects::Terrain> terrain);
		void SetGUI(std::shared_ptr<Objects::GUI> gui);
		void Objects::World::AddDebugObject(std::shared_ptr<Objects::Entity> model);
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
		std::shared_ptr<std::vector<std::shared_ptr<PrimitiveModel>>> GetPrimitiveModels();
			/**
			 * Gets the static entities currently loaded.
			 * @return A vector of pointers to static entities currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<StaticEntity>>> GetStaticEntities();
		std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>> GetRigidBodies();
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Terrain>>> GetTerrains();
		std::shared_ptr<std::vector<std::shared_ptr<Objects::AffordanceEntity>>> GetAffordanceEntities();
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Entity>>> Objects::World::GetDebugObjects();
		std::shared_ptr<Objects::GUI> GetGUI();

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