#pragma once

#include <vector>
#include <memory>

#include "Texture.h"
#include "ObjModel.h"
#include "PrimitiveModel.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "RigidBody.h"
#include "Terrain.h"

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

		void AddRigidBody(std::shared_ptr<Objects::RigidBody> entity);
		void AddTerrain(std::shared_ptr<Objects::Terrain> terrain);

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

	private:
		std::shared_ptr<std::vector<std::shared_ptr<Texture>>> m_textures;
		std::shared_ptr<std::vector<std::shared_ptr<ObjModel>>> m_objModels;
		std::shared_ptr<std::vector<std::shared_ptr<PrimitiveModel>>> m_primitiveModels;
		std::shared_ptr<std::vector<std::shared_ptr<StaticEntity>>> m_staticEntities;
		std::shared_ptr<std::vector<std::shared_ptr<RigidBody>>> m_rigidBodies;
		std::shared_ptr<std::vector<std::shared_ptr<Objects::Terrain>>> m_terrains;
	};

}