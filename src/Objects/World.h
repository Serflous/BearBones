#pragma once

#include <vector>

#include "Texture.h"
#include "ObjModel.h"
#include "Entity.h"
#include "StaticEntity.h"

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
		void AddStaticEntity(StaticEntity entity);

		std::vector<Texture> GetTextures();
		std::vector<ObjModel> GetOBJModels();
		std::vector<StaticEntity> GetStaticEntities();

	private:
		std::vector<Texture> m_textures;
		std::vector<ObjModel> m_models;
		std::vector<StaticEntity> m_staticEntities;
	};

}