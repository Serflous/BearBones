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
	m_boundingBoxShader = std::make_shared<Shaders::BoundingBoxShader>();
	m_primitiveShader = std::make_shared<Shaders::PrimitiveShader>();

	LoadShader("res/Shaders/staticShader.vert", "res/Shaders/staticShader.frag", m_staticShader);
	LoadShader("res/Shaders/boundingBoxShader.vert", "res/Shaders/boundingBoxShader.frag", m_boundingBoxShader);
	LoadShader("res/Shaders/primitiveShader.vert", "res/Shaders/primitiveShader.frag", m_primitiveShader);
	m_terrainShader = std::make_shared<Shaders::TerrainShader>();

	LoadShader("res/Shaders/staticShader.vert", "res/Shaders/staticShader.frag", m_staticShader);
	LoadShader("res/Shaders/boundingBoxShader.vert", "res/Shaders/boundingBoxShader.frag", m_boundingBoxShader);
	LoadShader("res/Shaders/terrainShader.vert", "res/Shaders/terrainShader.frag", m_terrainShader);

	m_staticShader->Start();
	std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadProjectionMatrix(m_projectionMatrix);
	m_staticShader->Stop();

	m_boundingBoxShader->Start();
	std::dynamic_pointer_cast<Shaders::BoundingBoxShader>(m_boundingBoxShader)->LoadProjectionMatrix(m_projectionMatrix);
	m_boundingBoxShader->Stop();

	m_primitiveShader->Start();
	std::dynamic_pointer_cast<Shaders::PrimitiveShader>(m_primitiveShader)->LoadProjectionMatrix(m_projectionMatrix);
	m_primitiveShader->Stop();

	m_terrainShader->Start();
	std::dynamic_pointer_cast<Shaders::TerrainShader>(m_terrainShader)->LoadProjectionMatrix(m_projectionMatrix);
	m_terrainShader->Stop();
}

void Rendering::Renderer::SetDimensions(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Rendering::Renderer::RenderWorld(std::shared_ptr<Objects::World> world, std::shared_ptr<Objects::Camera> camera)
{
	PrepareRender();
	m_staticShader->Start();
	std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadViewMatrix(Util::MathUtil::GetViewMatrix(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, camera->GetPitch(), camera->GetYaw(), camera->GetRoll()));
	m_staticShader->Stop();
	m_boundingBoxShader->Start();
	std::dynamic_pointer_cast<Shaders::BoundingBoxShader>(m_boundingBoxShader)->LoadViewMatrix(Util::MathUtil::GetViewMatrix(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, camera->GetPitch(), camera->GetYaw(), camera->GetRoll()));
	m_boundingBoxShader->Stop();
	m_primitiveShader->Start();
	std::dynamic_pointer_cast<Shaders::PrimitiveShader>(m_primitiveShader)->LoadViewMatrix(Util::MathUtil::GetViewMatrix(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, camera->GetPitch(), camera->GetYaw(), camera->GetRoll()));
	m_primitiveShader->Stop();
	m_terrainShader->Start();
	std::dynamic_pointer_cast<Shaders::TerrainShader>(m_terrainShader)->LoadViewMatrix(Util::MathUtil::GetViewMatrix(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, camera->GetPitch(), camera->GetYaw(), camera->GetRoll()));
	m_terrainShader->Stop();

	std::shared_ptr<std::vector<std::shared_ptr<Objects::StaticEntity>>> staticEntities = world->GetStaticEntities();
	std::shared_ptr<std::vector<std::shared_ptr<Objects::RigidBody>>> rigidBodies = world->GetRigidBodies();
	std::shared_ptr<std::vector<std::shared_ptr<Objects::Terrain>>> terrains = world->GetTerrains();
	
	std::vector<std::shared_ptr<Objects::StaticEntity>>::iterator staticEntityIter;
	std::vector<std::shared_ptr<Objects::RigidBody>>::iterator rigidBodiesIter;
	std::vector<std::shared_ptr<Objects::Terrain>>::iterator terrainIter;
	for (staticEntityIter = staticEntities->begin(); staticEntityIter != staticEntities->end(); staticEntityIter++)
	{
		if (dynamic_cast<Objects::ObjModel*>((*staticEntityIter)->GetModel().get()) != nullptr)
		{
			m_staticShader->Start();
			std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*staticEntityIter)->GetPosition(), (*staticEntityIter)->GetRotation(), (*staticEntityIter)->GetScale()));
			RenderOBJModel(std::dynamic_pointer_cast<Objects::ObjModel>((*staticEntityIter)->GetModel()));
			m_staticShader->Stop();
		}
		else
		{
			m_primitiveShader->Start();
			std::dynamic_pointer_cast<Shaders::PrimitiveShader>(m_primitiveShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*staticEntityIter)->GetPosition(), (*staticEntityIter)->GetRotation(), (*staticEntityIter)->GetScale()));
			std::dynamic_pointer_cast<Shaders::PrimitiveShader>(m_primitiveShader)->LoadColour(std::dynamic_pointer_cast<Objects::PrimitiveModel>((*staticEntityIter)->GetModel())->GetColour());
			RenderPrimitive(std::dynamic_pointer_cast<Objects::PrimitiveModel>((*staticEntityIter)->GetModel()));
			m_primitiveShader->Stop();
		}
		
	}

	for (rigidBodiesIter = rigidBodies->begin(); rigidBodiesIter != rigidBodies->end(); rigidBodiesIter++)
	{
		if (dynamic_cast<Objects::ObjModel*>((*rigidBodiesIter)->GetModel().get()) != nullptr)
		{
			m_staticShader->Start();
			std::dynamic_pointer_cast<Shaders::StaticShader>(m_staticShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*rigidBodiesIter)->GetPosition(), (*rigidBodiesIter)->GetRotation(), (*rigidBodiesIter)->GetScale()));
			RenderOBJModel(std::dynamic_pointer_cast<Objects::ObjModel>((*rigidBodiesIter)->GetModel()));
			m_staticShader->Stop();
		}
		else
		{
			m_primitiveShader->Start();
			std::dynamic_pointer_cast<Shaders::PrimitiveShader>(m_primitiveShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*rigidBodiesIter)->GetPosition(), (*rigidBodiesIter)->GetRotation(), (*rigidBodiesIter)->GetScale()));
			std::dynamic_pointer_cast<Shaders::PrimitiveShader>(m_primitiveShader)->LoadColour(std::dynamic_pointer_cast<Objects::PrimitiveModel>((*rigidBodiesIter)->GetModel())->GetColour());
			RenderPrimitive(std::dynamic_pointer_cast<Objects::PrimitiveModel>((*rigidBodiesIter)->GetModel()));
			m_primitiveShader->Stop();
		}
	}

	/*m_boundingBoxShader->Start();
	std::dynamic_pointer_cast<Shaders::BoundingBoxShader>(m_boundingBoxShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	RenderPrimitive();
	m_boundingBoxShader->Stop();*/

	for (terrainIter = terrains->begin(); terrainIter != terrains->end(); terrainIter++)
	{
		m_terrainShader->Start();
		std::dynamic_pointer_cast<Shaders::TerrainShader>(m_terrainShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*terrainIter)->GetPosition(), glm::vec3(0, 0, 0), (*terrainIter)->GetScale()));
		RenderTerrain(*terrainIter);
		m_terrainShader->Stop();
	}

	for (staticEntityIter = staticEntities->begin(); staticEntityIter != staticEntities->end(); staticEntityIter++)
	{
		/*Collision::AABB bb = (*staticEntityIter)->GetBoundingBox();
		glm::vec3 scale = bb.GetMaxBounds() - bb.GetMinBounds();
		m_boundingBoxShader->Start();
		std::dynamic_pointer_cast<Shaders::BoundingBoxShader>(m_boundingBoxShader)->LoadTransformationMatrix(Util::MathUtil::GetTransformationMatrix((*staticEntityIter)->GetPosition(), (*staticEntityIter)->GetRotation(), scale));
		RenderEntityAABB();
		m_boundingBoxShader->Stop();*/
	}

}

void Rendering::Renderer::PrepareRender()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.392f, 0.584f, 0.929f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Rendering::Renderer::RenderOBJModel(std::shared_ptr<Objects::ObjModel> model)
{
	glBindVertexArray(model->GetVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	model->GetTexture()->Bind();
	glDrawElements(GL_TRIANGLES, model->GetVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

}

void Rendering::Renderer::RenderTerrain(std::shared_ptr<Objects::Terrain> terrain)
{
	glBindVertexArray(terrain->GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	terrain->GetTerrainTextureCollection()->GetBaseTexture()->Bind();
	glActiveTexture(GL_TEXTURE1);
	terrain->GetTerrainTextureCollection()->GetTextureAt(0)->Bind();
	glActiveTexture(GL_TEXTURE2);
	terrain->GetTerrainTextureCollection()->GetTextureAt(1)->Bind();
	glActiveTexture(GL_TEXTURE3);
	terrain->GetTerrainTextureCollection()->GetTextureAt(2)->Bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, terrain->GetVertexCount(), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Rendering::Renderer::RenderPrimitive(std::shared_ptr<Objects::PrimitiveModel> model)
{
	glBindVertexArray(model->GetVAOID());
	glEnableVertexAttribArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, model->GetVertexCount(), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisableVertexAttribArray(0);
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