#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include "Texture.h"
#include "ObjModel.h"
#include "Entity.h"

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
		Entity CreateEntity(ObjModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	private:
		void ProcessVertex(std::string v, std::string t, std::string n, std::vector<int> &indicies, std::vector<glm::vec2> &textures, std::vector<glm::vec3> &normals, std::vector<float> &textureArray, std::vector<float> &normalArray);
		int LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indicies);
		void AddDataToVAO(int attribList, int coordSize, std::vector<float> data);
		void AddIndiciesToVAO(std::vector<int> indicies);
	};

}