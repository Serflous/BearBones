#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

	class ResourceLoader
	{
	public:
		ResourceLoader();
		ResourceLoader(const ResourceLoader & other);
		~ResourceLoader();

		Texture LoadTexture(std::string filename, int x, int y);
		ObjModel LoadOBJModel(std::string filename, Texture texture);
		StaticEntity CreateStaticEntity(ObjModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	private:
		int LoadToVAO(std::vector<glm::vec3> positions, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> normals, std::vector<int> indicies);
		void AddDataToVAO(int attribList, int coordSize, std::vector<glm::vec2> data);
		void AddDataToVAO(int attribList, int coordSize, std::vector<glm::vec3> data);
		void AddIndiciesToVAO(std::vector<int> indicies);
	};

}