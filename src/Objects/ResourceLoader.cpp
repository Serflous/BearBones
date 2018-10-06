#include "ResourceLoader.h"

Objects::ResourceLoader::ResourceLoader()
{

}

Objects::ResourceLoader::ResourceLoader(const ResourceLoader & other)
{

}

Objects::ResourceLoader::~ResourceLoader()
{

}

std::shared_ptr<Objects::Texture> Objects::ResourceLoader::LoadTexture(std::string filename)
{
	GLuint texId = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS |  SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	std::shared_ptr<Texture> tex = std::make_shared<Texture>();
	tex->SetTextureID(texId);

	std::cout << "Texture loaded: " << filename << std::endl;

	return tex;
}

std::shared_ptr<Objects::ObjModel> Objects::ResourceLoader::LoadOBJModel(std::string filename, std::shared_ptr<Texture> texture)
{
	std::ifstream in(filename);
	if (!in)
	{
		throw new std::invalid_argument("File not found: " + filename);
	}

	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(filename, aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw std::invalid_argument("Model load error: " + filename);
	}

	if (scene->mNumMeshes <= 0)
		throw std::invalid_argument("Model has no meshes: " + filename);

	aiMesh * mesh = scene->mMeshes[0];

	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indicies;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		verticies.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		textures.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indicies.push_back(face.mIndices[j]);
		}
	}

	int vaoId = LoadToVAO(verticies, textures, normals, indicies);

	std::shared_ptr<Objects::ObjModel> model = std::make_shared<Objects::ObjModel>();
	model->SetVAOID(vaoId);
	model->SetVertexCount(indicies.size());
	model->SetTexture(texture);
	model->SetVerticies(verticies);
	model->SetUVs(textures);
	model->SetNormals(normals);

	std::cout << "Model loaded: " << filename << std::endl;

	return model;
}

std::shared_ptr<Objects::StaticEntity> Objects::ResourceLoader::CreateStaticEntity(std::shared_ptr<Objects::ObjModel> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<Objects::StaticEntity> entity = std::make_shared<Objects::StaticEntity>();
	entity->SetModel(model);
	entity->SetPosition(position);
	entity->SetRotation(rotation);
	entity->SetScale(scale);
	entity->CreateBoundingBox();
	return entity;
}

GLuint Objects::ResourceLoader::LoadPrimitive(std::vector<glm::vec3> positions, std::vector<int> indicies)
{
	return LoadToVAO(positions, indicies);
}

int Objects::ResourceLoader::LoadToVAO(std::vector<glm::vec3> positions, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> normals, std::vector<int> indicies)
{
	GLuint vaoId = 0;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	AddIndiciesToVAO(indicies);
	AddDataToVAO(0, 3, positions);
	AddDataToVAO(1, 2, textureCoords);
	AddDataToVAO(2, 3, normals);
	glBindVertexArray(0);
	return vaoId;
}

int Objects::ResourceLoader::LoadToVAO(std::vector<glm::vec3> positions, std::vector<int> indicies)
{
	GLuint vaoId = 0;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	AddIndiciesToVAO(indicies);
	AddDataToVAO(0, 3, positions);

	glBindVertexArray(0);
	return vaoId;
}

void Objects::ResourceLoader::AddDataToVAO(int attribList, int coordSize, std::vector<glm::vec2> data)
{
	GLuint vboId = 0;
	
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribList, coordSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Objects::ResourceLoader::AddDataToVAO(int attribList, int coordSize, std::vector<glm::vec3> data)
{
	GLuint vboId = 0;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, 3 * data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribList, coordSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Objects::ResourceLoader::AddIndiciesToVAO(std::vector<int> indicies)
{
	GLuint vboId = 0;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), &indicies.front(), GL_STATIC_DRAW);
}