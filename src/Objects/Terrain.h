#pragma once

#include <GLM/vec3.hpp>

#include "TerrainTextureCollection.h"

namespace Objects
{

		/**
		 * The terrain upon which serves as the ground for the world.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class Terrain
	{
	public:
		Terrain();
		Terrain(const Terrain & other);
		~Terrain();

			/**
			 * Sets the ID number of the VAO.
			 * @param[in] vaoID The ID number to set for the VAO.
			 */
		void SetVaoID(int vaoId);
			/**
			 * Sets the number of verticies found on the terrain.
			 * @param[in] vertexCount The number of verticies on the terrain.
			 */
		void SetVertexCount(int vertexCount);
			/**
			 * Sets the heightmap data of the terrain.
			 * @param[out] Pointer to the heightmap data.
			 */
		void SetTerrainHeightData(unsigned char * data);
			/**
			 * Sets the size of the terrain.
			 * @param[in] size The size of the terrain.
			 */
		void SetSize(int size);
			/**
			 * Sets the position of the terrain.
			 * @param[in] position The position to set the terrain to.
			 */
		void SetPosition(glm::vec3 position);
			/**
			 * Sets the scale of the terrain.
			 * @param[in] scale The scale to set the terrain to.
			 */
		void SetScale(glm::vec3 scale);
			/**
			 * Sets the base, red, green, and blue values of the terrain.
			 * @param[in] collection A collection of textures containing a base texture, and the red, green, and blue values of said texture.
			 */
		void SetTerrainTextureCollection(std::shared_ptr<TerrainTextureCollection> collection);

			/**
			 * Gets the ID number of the VAO.
			 * @return The ID number of the VAO.
			 */
		int GetVaoID();
			/**
			 * Gets the number of verticies found on the terrain.
			 * @return The number of verticies on the terrain.
			 */
		int GetVertexCount();
			/**
			 * Gets the heightmap data of the terrain.
			 * @return The heightmap data.
			 */
		unsigned char * GetTerrainHeightData();
			/**
			 * Gets the size of the terrain.
			 * @return The size of the terrain.
			 */
		int GetSize();
			/**
			 * Gets the position of the terrain.
			 * @return The position of the terrain.
			 */
		glm::vec3 GetPosition();
			/**
			 * Gets the scale of the terrain.
			 * @return The scale of the terrain.
			 */
		glm::vec3 GetScale();
			/**
			 * Gets the grayscale, red, green, and blue values of the terrain.
			 * @return A collection of textures containing a grayscale texture, and the red, green, and blue values of said texture.
			 */
		std::shared_ptr<TerrainTextureCollection> GetTerrainTextureCollection();

			/**
			 * Gets the height at a specific point on the terrain.
			 * @param[in] x X coordinate of the point.
			 * @param[in] z Z coordinate of the point.
			 * @return Y coordinate of the point.
			 */
		float GetHeight(int x, int z);
			/**
			 * Gets the relative height at a specific point on the terrain.
			 * @param[in] x X coordinate of the point.
			 * @param[in] z Z coordinate of the point.
			 * @return Y coordinate of the point.
			 */
		float GetRelativeHeight(float x, float z);

	private:
			/**
			 * Checks if a point is within the given boundaries of the terrain.
			 * @param[in] x X coordinate of the point.
			 * @param[in] z Z coordinate of the point.
			 * @return True if within the boundaries. Otherwise return false.
			 */
		bool InBounds(int x, int z);

	private:
		int m_vaoId;
		int m_vertexCount;
		unsigned char * m_terrainHeightData;
		int m_size;
		glm::vec3 m_position;
		glm::vec3 m_scale;
		std::shared_ptr<TerrainTextureCollection> m_terrainCollection;
	};

}