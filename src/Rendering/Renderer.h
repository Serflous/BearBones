#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <GLM/gtx/transform.hpp>

#include <string>
#include <iostream>
#include <fstream>

#include "../Objects/World.h"
#include "../Shaders/ShaderBase.h"
#include "../Shaders/StaticShader.h"
#include "../Objects/Camera.h"
#include "../Util/MathUtil.h"

namespace Rendering
{

	class Renderer
	{
	public:
		Renderer();
		Renderer(const Renderer & other);
		~Renderer();

		void Init();
		void SetDimensions(int x, int y);
		void RenderWorld(Objects::World world, Objects::Camera camera);

	private:
		void PrepareRender();
		void RenderOBJModel(Objects::ObjModel model);

		void CreateProjectionMatrix();
		void LoadShader(std::string vertShader, std::string fragShader, std::shared_ptr<Shaders::ShaderBase> & shader);
		int LoadShaderFile(std::string filename, int type);

		int m_x, m_y;
		glm::mat4x4 m_projectionMatrix;
		std::shared_ptr<Shaders::ShaderBase> m_staticShader;
		const float FOV = 70.0f;
		const float NEAR_PLANE = 0.1f;
		const float FAR_PLANE = 1000.0f;
	};

}