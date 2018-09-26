#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture.h"
#include "ObjModel.h"
#include "Entity.h"
#include "StaticEntity.h"

namespace Objects
{

		/**
		 * Contains all the methods required for loading resources into the game.
		 * @author Mathew Causby.
		 * @version 0.1
		 */
	class ResourceLoader
	{
	public:
		ResourceLoader();
		ResourceLoader(const ResourceLoader & other);
		~ResourceLoader();

			/**
			 * Loads a texture and uploads to OpenGL.
			 * @param[in] filename The filename of the texture.
			 * @return A pointer to the newly created texture file.
			 * @sa Objects::Texture
			 */
		std::shared_ptr<Texture> LoadTexture(std::string filename);
			/**
			 * Loads a wavefront object file into the game and uplaods it to a VAO and VBO's.
			 * @param[in] filename The filename to load in.
			 * @param[in] texture The texture to assign to the model.
			 * @sa Objects::ObjModel
			 * @return A pointer to the newly created model.
			 */
		std::shared_ptr<ObjModel> LoadOBJModel(std::string filename, std::shared_ptr<Texture> texture);
			/**
			 * Creates a static entity. A static entity is one that won't move or be moved by other objects.
			 * @param[in] model The model to draw.
			 * @param[in] position The position of the entity.
			 * @param[in] rotation The rotation of the entity.
			 * @param[in] scale The scale of the entity.
			 * @sa Objects::StaticEntity
			 * @return A pointer to the newly created entity.
			 */
		std::shared_ptr<StaticEntity> CreateStaticEntity(std::shared_ptr<ObjModel> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	private:
			/**
			 * Uploads all the model information to the GPU for OpengGL to use.
			 * @param[in] positions A vector containing all the verticies of the model.
			 * @param[in] textureCoords A vector containing all the UVs of the model.
			 * @param[in] normals A vector containing all the normals of the model.
			 * @param[in] indicies A vector containing all the elements of the model.
			 * @return The ID of the VAO that was created.
			 */
		int LoadToVAO(std::vector<glm::vec3> positions, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> normals, std::vector<int> indicies);
			/**
			 * Adds vec2 data to a VBO and adds that to the VAO.
			 * @param[in] attribList The attribute list number to upload the data to.
			 * @param[in] data A vector containing the vec2 data.
			 */
		void AddDataToVAO(int attribList, int coordSize, std::vector<glm::vec2> data);
			/**
			 * Adds vec3 data to a VBO and adds that to the VAO.
			 * @param[in] attribList The attribute list number to upload the data to.
			 * @param[in] data A vector containing the vec3 data.
			 */
		void AddDataToVAO(int attribList, int coordSize, std::vector<glm::vec3> data);
			/**
			 * Adds the model elements to a VBO and adds that to the VAO.
			 * @param indicies A vector containing al the indicies.
			 */
		void AddIndiciesToVAO(std::vector<int> indicies);
	};

}