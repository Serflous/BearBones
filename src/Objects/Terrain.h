#pragma once

#include <GLM/vec3.hpp>

#include "TerrainTextureCollection.h"

namespace Objects
{

	class Terrain
	{
	public:
		Terrain();
		Terrain(const Terrain & other);
		~Terrain();

		void SetVaoID(int vaoId);
		void SetVertexCount(int vertexCount);
		void SetTerrainHeightData(unsigned char * data);
		void SetSize(int size);
		void SetScale(glm::vec3 scale);
		void SetTerrainTextureCollection(TerrainTextureCollection collection);

		int GetVaoID();
		int GetVertexCount();
		unsigned char * GetTerrainHeightData();
		int GetSize();
		glm::vec3 GetScale();
		TerrainTextureCollection GetTerrainTextureCollection();

		float GetHeight(int x, int z);
		float GetRelativeHeight(float x, float z);

	private:
		bool InBounds(int x, int z);

	private:
		int m_vaoId;
		int m_vertexCount;
		unsigned char * m_terrainHeightData;
		int m_size;
		glm::vec3 m_scale;
		TerrainTextureCollection m_terrainCollection;
	};

}