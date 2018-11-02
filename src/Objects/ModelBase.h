#pragma once

#include <GLM/vec3.hpp>

#include <vector>

namespace Objects
{
	/**
	 * 
	 * @author
	 * @version 0.1
	 */
	class ModelBase
	{
	public:
		ModelBase();
		ModelBase(const ModelBase & other);
		virtual ~ModelBase();

		/**
		 * 
		 * @param[in] vaoId The ID number of the model.
		 */
		void SetVAOID(int vaoId);
		/**
		 * Sets the number of vertexes found on the model.
		 * @param[in] vertexCount The number of vertexes on the model.
		 */
		void SetVertexCount(int vertexCount);
		/**
		 * Sets the verticies of the model.
		 * @param[in] verts The verticies of the model.
		 */
		void SetVerticies(std::vector<glm::vec3> verts);

		/**
		 *
		 * @return The ID number of the model.
		 */
		int GetVAOID();
		/**
		 * Gets the number of vertexes found on the model.
		 * @return The number of vertexes on the model.
		 */
		int GetVertexCount();
		/**
		 * Gets the verticies of the model.
		 * @return The verticies of the model.
		 */
		std::vector<glm::vec3> GetVerticies();

	protected:
		int m_vaoId;
		int m_vertexCount;
		std::vector<glm::vec3> m_verticies;
	};

}