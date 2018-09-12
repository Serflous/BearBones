#include "Renderer.h"

Rendering::Renderer::Renderer()
{

}

Rendering::Renderer::Renderer(const Renderer & other)
{

}

Rendering::Renderer::~Renderer()
{

}

void Rendering::Renderer::Init()
{
	CreateProjectionMatrix();
	m_staticShader = std::make_shared<Shaders::StaticShader>();

	LoadShader("res/Shaders/staticShader.vert", "res/Shaders/staticShader.frag", m_staticShader);

	m_staticShader->Start();
	std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadProjectionMatrix(m_projectionMatrix);
	m_staticShader->Stop();
}

void Rendering::Renderer::SetDimensions(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Rendering::Renderer::RenderWorld(Objects::World world, Objects::Camera camera)
{
	PrepareRender();
	m_staticShader->Start();
	//std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadViewMatrix(Util::MathUtil::GetViewMatrix(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z, camera.GetPitch(), camera.GetYaw(), camera.GetRoll()));
	m_staticShader->Stop();
	std::vector<Objects::Entity> entities = world.GetEntities();
	std::vector<Objects::Entity>::iterator entityIter;
	for (entityIter = entities.begin(); entityIter != entities.end(); entityIter++)
	{
		m_staticShader->Start();
		std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*entityIter).GetPosition(), (*entityIter).GetRotation(), (*entityIter).GetScale()));
		RenderOBJModel((*entityIter).GetModel());
		m_staticShader->Stop();
	}

}

void Rendering::Renderer::PrepareRender()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.392f, 0.584f, 0.929f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Rendering::Renderer::RenderOBJModel(Objects::ObjModel model)
{
	glBindVertexArray(model.GetVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	model.GetTexture().Bind();
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Rendering::Renderer::CreateProjectionMatrix()
{
	float aspectRatio = (float)m_x / (float)m_y;
	m_projectionMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void Rendering::Renderer::LoadShader(std::string vertShader, std::string fragShader, std::shared_ptr<Shaders::ShaderBase> & shader)
{
	GLuint vertexShaderId = LoadShaderFile(vertShader, GL_VERTEX_SHADER);
	if (vertexShaderId <= 0)
	{
		return;
	}
	std::cout << "Vertex shader loaded: " << vertShader << " with ID-" << vertexShaderId << std::endl;
	GLuint fragmentShaderId = LoadShaderFile(fragShader, GL_FRAGMENT_SHADER);
	if (fragmentShaderId <= 0)
	{
		return;
	}
	std::cout << "Fragment shader loaded: " << fragShader << " with ID-" << fragmentShaderId << std::endl;
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	shader->SetProgramID(programId);
	shader->SetVertexShaderID(vertexShaderId);
	shader->SetFragmentShaderID(fragmentShaderId);
	shader->BindAttributes();
	glLinkProgram(programId);
	glValidateProgram(programId);
	shader->GetAllUniforms();
	std::cout << "Shader program successfully loaded with ID-" << programId << std::endl;
}

int Rendering::Renderer::LoadShaderFile(std::string filename, int type)
{
	std::string shaderContent, line = "";
	std::ifstream fileStream(filename);
	int programId;
	if (!fileStream.is_open())
	{
		throw new std::invalid_argument(filename + " shader failed to open.");
	}
	while (getline(fileStream, line))
	{
		shaderContent.append(line + '\n');
	}
	fileStream.close();

	programId = glCreateShader(type);
	const char * shaderSource = shaderContent.c_str();
	std::cout << filename << " loaded successfully. Compiling..." << std::endl;
	glShaderSource(programId, 1, &shaderSource, NULL);
	glCompileShader(programId);
	GLint compileStatus = GL_FALSE;
	glGetShaderiv(programId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		throw new std::runtime_error(filename + " failed to compile.");
		}
	else
	{
		std::cout << filename << " compiled successfully." << std::endl;
	}

	return programId;
}