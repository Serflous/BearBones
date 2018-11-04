#pragma once

#include <vector>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

#include <memory>

#include "ModelBase.h"
#include "Texture.h"

namespace Objects
{

		/**
		 * Contains information about an wavefront object file.
		 * @author Mathew Causby
		 * @version 0.1
		 * @todo Rename all vertex counts to element counts
		 */
	class ObjModel : public ModelBase
	{
	public:
		ObjModel();
		ObjModel(const ObjModel & other);
		~ObjModel();

			/**
			 * Sets the height of the model.
			 * @param[in] height The height of the model
			 */
		void SetModelHeight(double height);
			/**
			 * Sets the texture to draw onto the model.
			 * @param[in] tex A pointer to the texture to use.
			 */
		void SetTexture(std::shared_ptr<Texture> tex);
			/**
			 * Sets the UVs of the model.
			 * @param[in] uvs A vector containing every uv map in the model.
			 */
		void SetUVs(std::vector<glm::vec2> uvs);
			/**
			 * Sets the normals of the model.
			 * @param[in] norms A vector containing every normal of the model.
			 */
		void SetNormals(std::vector<glm::vec3> norms);

			/**
			 * Gets the height of the model.
			 * @return The height of the model.
			 */
		double GetModelHeight();
			/**
			 * Gets the UVs of the model.
			 * @return A vector containing all of the UV mappings of the model
			 */
		std::vector<glm::vec2> GetUVs();
			/**
			 * Gets the normals of the model.
			 * @return A vector containing all of the normals of the model.
			 */
		std::vector<glm::vec3> GetNormals();
			/**
			 * Gets the texture to draw onto the model.
			 * @return A pointer to the texture.
			 */
		std::shared_ptr<Texture> GetTexture();

	private:
		double m_modelHeight;
		std::shared_ptr<Texture> m_texture;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
	};

}