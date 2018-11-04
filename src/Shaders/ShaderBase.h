#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

namespace Shaders
{

		/**
		 * Abstract class that is the base of all shaders.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class ShaderBase
	{
	public:
		ShaderBase();
		ShaderBase(const ShaderBase & other);
		~ShaderBase();
			/**
			 * Starts the shader.
			 */
		void Start();
			/**
			 * Stops the shader.
			 */
		void Stop();
			/**
			 * Pure virtual function for binding all of the attributes in the shader.
			 */
		virtual void BindAttributes() = 0;
			/**
			 * Pure virtual function for getting all of the uniform locations in the shader.
			 */
		virtual void GetAllUniforms() = 0;
			/**
			 * Sets the ID of the entire shader program
			 * @param[in] id The ID of the shader.
			 */
		void SetProgramID(int id);
			/**
			 * Sets the ID of the vertex shader.
			 * @param[in] id The ID of the shader.
			 */
		void SetVertexShaderID(int id);
			/**
			 * Sets the ID of the fragment shader.
			 * @param[in] id The ID of the shader.
			 */
		void SetFragmentShaderID(int id);
			/**
			 * Gets the ID of the entire shader program
			 * @return The ID of the shader.
			 */
		int GetProgramID();
			/**
			 * Gets the ID of the vertex shader.
			 * @return The ID of the shader.
			 */
		int GetVertexShaderID();
			/**
			 * Gets the ID of the fragment shader.
			 * @return The ID of the shader.
			 */
		int GetFragmentShaderID();

	protected:
			/**
			 * Binds an atribute list to a label/name.
			 * @param[in] attrib The number of the attribute list.
			 * @param[in] name The name to bind it to.
			 */
		void BindAttrib(int attrib, const char * name);
			/**
			 * Gets the location of the uniform with a particular name.
			 * @param[in] name The name to get the location of.
			 * @return The location of the uniform.
			 */
		GLuint GetUniform(const char * name);
			/**
			 * Loads a float to the shader.
			 * @param[in] location The location to upload the value to.
			 * @param[in] value The value to upload.
			 */
		void LoadFloat(GLuint location, float value);
			/**
			* Loads an int to the shader.
			* @param[in] location The location to upload the value to.
			* @param[in] value The value to upload.
			*/
		void LoadInt(GLuint location, int value);
			/**
			* Loads an unsigned int to the shader.
			* @param[in] location The location to upload the value to.
			* @param[in] value The value to upload.
			*/
		void LoadUInt(GLuint location, unsigned int value);
			/**
			* Loads a vec3 to the shader.
			* @param[in] location The location to upload the value to.
			* @param[in] value The value to upload.
			*/
		void LoadVec3(GLuint location, glm::vec3 value);
			/**
			* Loads a boolean to the shader.
			* @param[in] location The location to upload the value to.
			* @param[in] value The value to upload.
			*/
		void LoadBoolean(GLuint location, bool value);
			/**
			* Loads a mat4x4 to the shader.
			* @param[in] location The location to upload the value to.
			* @param[in] value The value to upload.
			*/
		void LoadMatrix4(GLuint location, glm::mat4x4 value);

	private:
		int m_programId;
		int m_vertexShaderId;
		int m_fragmentShaderId;
	};

}