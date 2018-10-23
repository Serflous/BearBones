#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <GLM/gtx/transform.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>

#include "../Objects/World.h"
#include "../Shaders/ShaderBase.h"
#include "../Shaders/StaticShader.h"
#include "../Shaders/BoundingBoxShader.h"
#include "../Shaders/PrimitiveShader.h"
#include "../Shaders/TerrainShader.h"
#include "../Objects/Camera.h"
#include "../Util/MathUtil.h"
#include "../Util/Types.h"

namespace Rendering
{

		/**
		 * Class that contains information about the render target, the shaders, and functions that will actually draw the world.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class Renderer
	{
	public:
		Renderer();
		Renderer(const Renderer & other);
		~Renderer();

			/**
			 * Initializes the renderer. Must be called before any rendering can be done.
			 */
		void Init();
			/**
			 * Sets the dimensions of the render target.
			 * @param[in] x The width of the screen.
			 * @param[in] y The height of the screen.
			 */
		void SetDimensions(int x, int y);
			/**
			 * Renders a world onto the screen using a particular camera as reference.
			 * @param[in] A pointer to the world to draw.
			 * @param[in] A pointer to the camera to use.
			 */
		void RenderWorld(std::shared_ptr<Objects::World> world, std::shared_ptr<Objects::Camera> camera);

	private:
			/**
			 * Prepares OepnGL for a new render frame.
			 */
		void PrepareRender();
			/**
			 * Renders an OBJ model.
			 * @param[in] A pointer to an OBJ model
			 */
		void RenderOBJModel(std::shared_ptr<Objects::ObjModel> model);

		void RenderPrimitive(std::shared_ptr<Objects::PrimitiveModel> model);
		void RenderTerrain(std::shared_ptr<Objects::Terrain> terrain);

			/**
			 * Creates the projection matrix for rendering.
			 */
		void CreateProjectionMatrix();
			/**
			 * Loads a shader program.
			 * @param[in] vertShader The location of the vertex shader.
			 * @param[in] fragShader The location of the fragment shdaer.
			 * @param[out] shader A pointer to a ShaderBase object to create the shader into.
			 */
		void LoadShader(std::string vertShader, std::string fragShader, std::shared_ptr<Shaders::ShaderBase> & shader);
			/**
			 * Loads and compiles a shader.
			 * @param[in] filename The filename of the shader.
			 * @param[in] type The type of shader.
			 * @return The ID of the compiled shader program.
			 */
		int LoadShaderFile(std::string filename, int type);

		int m_x, m_y;
		glm::mat4x4 m_projectionMatrix;
		std::shared_ptr<Shaders::ShaderBase> m_staticShader;
		std::shared_ptr<Shaders::ShaderBase> m_boundingBoxShader;
		std::shared_ptr<Shaders::ShaderBase> m_primitiveShader;
		std::shared_ptr<Shaders::ShaderBase> m_terrainShader;
		const float FOV = 45.0f;
		const float NEAR_PLANE = 0.1f;
		const float FAR_PLANE = 1000.0f;
	};

}