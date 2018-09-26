#pragma once

#include <vector>
#include <memory>

#include "Texture.h"
#include "ObjModel.h"
#include "Entity.h"
#include "StaticEntity.h"

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
			/**
			 * Adds a static entity to the world
			 * @param[in] A pointer to the static entity.
			 * @sa Objects::StaticEntity
			 */
		void AddStaticEntity(std::shared_ptr<StaticEntity> entity);

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
			 * Gets the static entities currently loaded.
			 * @return A vector of pointers to static entities currently in the world.
			 */
		std::shared_ptr<std::vector<std::shared_ptr<StaticEntity>>> GetStaticEntities();

	private:
		std::shared_ptr<std::vector<std::shared_ptr<Texture>>> m_textures;
		std::shared_ptr<std::vector<std::shared_ptr<ObjModel>>> m_models;
		std::shared_ptr<std::vector<std::shared_ptr<StaticEntity>>> m_staticEntities;
	};

}