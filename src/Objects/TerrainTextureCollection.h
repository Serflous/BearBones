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

		/**
		 * Sets the grayscale texture.
		 * @param[out] Pointer to the grayscale texture.
		 */
		void SetBaseTexture(std::shared_ptr<Texture> texture);
		/**
		 * Sets the coloured texture.
		 * @param[out] Pointer to the coloured texture.
		 */
		void SetTexture(int idx, std::shared_ptr<Texture> texture);

		/**
		 * Gets the grayscale texture.
		 * @return The grayscale texture.
		 */
		std::shared_ptr<Texture> GetBaseTexture();
		/**
		 * 
		 * @return
		 */
		std::shared_ptr<Texture> GetTextureAt(int idx);

	private:
		std::shared_ptr<Texture> m_baseTexture;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};

}