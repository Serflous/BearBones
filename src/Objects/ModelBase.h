#pragma once

#include <GLM/vec3.hpp>

#include <vector>

namespace Objects
{

	class ModelBase
	{
	public:
		ModelBase();
		ModelBase(const ModelBase & other);
		virtual ~ModelBase();

		void SetVAOID(int vaoId);
		void SetVertexCount(int vertexCount);
		void SetVerticies(std::vector<glm::vec3> verts);

		int GetVAOID();
		int GetVertexCount();
		std::vector<glm::vec3> GetVerticies();

	protected:
		int m_vaoId;
		int m_vertexCount;
		std::vector<glm::vec3> m_verticies;
	};

}