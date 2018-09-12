#pragma once

#include <vector>

#include "Texture.h"
#include "ObjModel.h"
#include "Entity.h"

namespace Objects
{

	class World
	{
	public:
		World();
		World(const World & other);
		~World();

		void AddTexture(Texture texture);
		void AddObjModel(ObjModel model);
		void AddEntity(Entity entity);

		std::vector<Texture> GetTextures();
		std::vector<ObjModel> GetOBJModels();
		std::vector<Entity> GetEntities();

	private:
		std::vector<Texture> m_textures;
		std::vector<ObjModel> m_models;
		std::vector<Entity> m_entities;
	};

}