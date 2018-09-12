#pragma once

#include <vector>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

#include "Texture.h"

namespace Objects
{

	class ObjModel
	{
	public:
		ObjModel();
		ObjModel(const ObjModel & other);
		~ObjModel();

		void SetVAOID(int vaoId);
		void SetVertexCount(int count);
		void SetModelHeight(double height);
		void SetTexture(Texture tex);
		void SetVerticies(std::vector<glm::vec3> verts);
		void SetUVs(std::vector<glm::vec2> uvs);
		void SetNormals(std::vector<glm::vec3> norms);

		int GetVAOID();
		int GetVertexCount();
		double GetModelHeight();
		std::vector<glm::vec3> GetVerticies();
		std::vector<glm::vec2> GetUVs();
		std::vector<glm::vec3> GetNormals();
		Texture GetTexture();

	private:
		int m_vaoId;
		int m_vertexCount;
		double m_modelHeight;
		Texture m_texture;
		std::vector<glm::vec3> m_verticies;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
	};

}