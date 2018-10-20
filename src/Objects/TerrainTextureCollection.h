#pragma once

#include <memory>
#include <vector>

#include "Texture.h"

namespace Objects
{

	class TerrainTextureCollection
	{
	public:
		TerrainTextureCollection();
		TerrainTextureCollection(const TerrainTextureCollection & other);
		~TerrainTextureCollection();

		void SetBaseTexture(std::shared_ptr<Texture> texture);
		void SetTexture(int idx, std::shared_ptr<Texture> texture);

		std::shared_ptr<Texture> GetBaseTexture();
		std::shared_ptr<Texture> GetTextureAt(int idx);

	private:
		std::shared_ptr<Texture> m_baseTexture;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};

}