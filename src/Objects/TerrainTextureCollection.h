#pragma once

#include <memory>
#include <vector>

#include "Texture.h"

namespace Objects
{
		/**
		 * Contains all the texture files to be used for the terrain.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class TerrainTextureCollection
	{
	public:
		TerrainTextureCollection();
		TerrainTextureCollection(const TerrainTextureCollection & other);
		~TerrainTextureCollection();

			/**
			 * Sets the base texture.
			 * @param[out] Pointer to the grayscale texture.
			 */
		void SetBaseTexture(std::shared_ptr<Texture> texture);
			/**
			 * Sets the coloured texture.
			 * @param[out] Pointer to the coloured texture.
			 */
		void SetTexture(int idx, std::shared_ptr<Texture> texture);

			/**
			 * Gets the base texture.
			 * @return The grayscale texture.
			 */
		std::shared_ptr<Texture> GetBaseTexture();
			/**
			 * Gets a texture at a specified index. Will be 0(red), 1(green), or 2(blue).
			 * @param[in] idx The index to get
			 * @return
			 */
		std::shared_ptr<Texture> GetTextureAt(int idx);

	private:
		std::shared_ptr<Texture> m_baseTexture;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};

}