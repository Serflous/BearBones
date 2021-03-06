#include "ResourceLoader.h"

Objects::ResourceLoader::ResourceLoader()
{
	m_guiQuad = 0;
}

Objects::ResourceLoader::ResourceLoader(const ResourceLoader & other)
{
	m_guiQuad = other.m_guiQuad;
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
	const aiScene * scene = importer.ReadFile(filename, aiProcess_FlipUVs | aiProcess_Triangulate);
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

std::shared_ptr<Objects::StaticEntity> Objects::ResourceLoader::CreateStaticEntity(std::shared_ptr<Objects::ModelBase> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<Objects::StaticEntity> entity = std::make_shared<Objects::StaticEntity>();
	entity->SetModel(model);
	entity->SetPosition(position);
	entity->SetRotation(rotation);
	entity->SetScale(scale);
	entity->CreateBoundingBox(Util::BB_BV_OBB);
	return entity;
}

std::shared_ptr<Objects::StaticEntity> Objects::ResourceLoader::CreateStaticEntity(std::shared_ptr<Objects::ModelBase> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string key, double value)
{
	std::shared_ptr<Objects::StaticEntity> entity = std::make_shared<Objects::StaticEntity>();
	entity->SetModel(model);
	entity->SetPosition(position);
	entity->SetRotation(rotation);
	entity->SetScale(scale);
	entity->CreateBoundingBox(Util::BB_BV_OBB);
	entity->SetAffordances(key, value);
	return entity;
}

std::shared_ptr<Objects::StaticEntity> Objects::ResourceLoader::CreateStaticEntity(std::shared_ptr<Objects::ModelBase> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::map<std::string, double> map)
{
	std::shared_ptr<Objects::StaticEntity> entity = std::make_shared<Objects::StaticEntity>();
	entity->SetModel(model);
	entity->SetPosition(position);
	entity->SetRotation(rotation);
	entity->SetScale(scale);
	entity->CreateBoundingBox(Util::BB_BV_OBB);
	entity->SetAffordanceMap(map);
	return entity;
}

std::shared_ptr<Objects::AffordanceEntity> Objects::ResourceLoader::CreateAffordanceEntity(std::shared_ptr<Objects::ModelBase> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::map<std::string, double> map)
{
	std::shared_ptr<Objects::AffordanceEntity> entity = std::make_shared<Objects::AffordanceEntity>();
	entity->SetModel(model);
	entity->SetPosition(position);
	entity->SetRotation(rotation);
	entity->SetScale(scale);
	entity->CreateBoundingBox(Util::BB_BV_OBB);
	entity->SetAffordanceMap(map);
	return entity;
}

std::shared_ptr<Objects::PrimitiveModel> Objects::ResourceLoader::CreateCubePrimitive(glm::vec3 colour)
{
	// Cube
	std::vector<glm::vec3> cubePositions =
	{
		glm::vec3(-1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f)
	};
	std::vector<int> cubeElements =
	{
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3,
	};

	GLuint cubeId = LoadPrimitive(cubePositions, cubeElements);
	std::shared_ptr<Objects::PrimitiveModel> model = std::make_shared<Objects::PrimitiveModel>();
	model->SetVAOID(cubeId);
	model->SetVertexCount(cubeElements.size());
	model->SetVerticies(cubePositions);
	model->SetColour(colour);

	return model;
}

std::shared_ptr<Objects::PrimitiveModel> Objects::ResourceLoader::CreateSpherePrimitive(glm::vec3 colour)
{
	// Sphere
	// Code adapted from https://linustechtips.com/main/topic/758200-drawing-spheres-in-opengl/
	std::vector<glm::vec3> spherePositions;
	std::vector<int> sphereElements;
	int latLevel = 40;
	int longLevel = 40;

	for (int i = 0; i <= latLevel; ++i)
	{

		double V = i / (double)latLevel;
		double phi = V * glm::pi<double>();

		for (int j = 0; j <= longLevel; ++j)
		{

			double U = j / (double)longLevel;
			double theta = U * (glm::pi<double>() * 2);

			double x = cosf(theta) * sinf(phi);
			double y = cosf(phi);
			double z = sinf(theta) * sinf(phi);

			spherePositions.push_back(glm::vec3(x, y, z));
		}
	}

	for (int i = 0; i < longLevel * latLevel + longLevel; i++)
	{

		sphereElements.push_back(i);
		sphereElements.push_back(i + longLevel + 1);
		sphereElements.push_back(i + longLevel);

		sphereElements.push_back(i + longLevel + 1);
		sphereElements.push_back(i);
		sphereElements.push_back(i + 1);
	}

	GLuint sphereId = LoadPrimitive(spherePositions, sphereElements);

	std::shared_ptr<Objects::PrimitiveModel> model = std::make_shared<Objects::PrimitiveModel>();
	model->SetVAOID(sphereId);
	model->SetVertexCount(sphereElements.size());
	model->SetVerticies(spherePositions);
	model->SetColour(colour);

	return model;
}

std::shared_ptr<Objects::RigidBody> Objects::ResourceLoader::CreateRigidBody(std::shared_ptr<Objects::ModelBase> model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<Objects::RigidBody> entity = std::make_shared<Objects::RigidBody>();
	entity->SetModel(model);
	entity->SetPosition(position);
	entity->SetRotation(rotation);
	entity->SetScale(scale);
	entity->CreateBoundingBox(Util::BB_BV_OBB);
	std::shared_ptr<Collision::BoundingVolume> bb = entity->GetBoundingVolume();
	std::shared_ptr<Collision::OBB> obb = std::dynamic_pointer_cast<Collision::OBB>(bb);
	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = std::numeric_limits<float>::max();
	maxX = maxY = maxZ = std::numeric_limits<float>::min();
	std::vector<glm::vec3>::iterator iter;
	std::vector<glm::vec3> verts = model->GetVerticies();
	for (iter = verts.begin(); iter != verts.end(); iter++)
	{
		glm::vec3 vert = (*iter);
		if (vert.x < minX)
			minX = vert.x;
		if (vert.y < minY)
			minY = vert.y;
		if (vert.z < minZ)
			minZ = vert.z;
		if (vert.x > maxX)
			maxX = vert.x;
		if (vert.y > maxY)
			maxY = vert.y;
		if (vert.z > maxZ)
			maxZ = vert.z;
	}
	entity->SetCenterOfGravity(glm::vec3
	(
		(minX + maxX) / 2.0,
		(minY + maxY) / 2.0,
		(minZ + maxZ) / 2.0
	));
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
int Objects::ResourceLoader::LoadToVAO(std::vector<glm::vec2> positions)
{
	GLuint vaoId = 0;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	AddDataToVAO(0, 2, positions);

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

std::shared_ptr<Objects::TerrainTextureCollection> Objects::ResourceLoader::LoadTerrainTextures(std::string baseTexture, std::string rTexture, std::string gTexture, std::string bTexture)
{
	std::shared_ptr<Texture> baseTex = LoadTexture(baseTexture);
	std::shared_ptr<Texture> rTex = LoadTexture(rTexture);
	std::shared_ptr<Texture> gTex = LoadTexture(gTexture);
	std::shared_ptr<Texture> bTex = LoadTexture(bTexture);

	std::shared_ptr<TerrainTextureCollection> collection = std::make_shared<TerrainTextureCollection>();
	collection->SetBaseTexture(baseTex);
	collection->SetTexture(0, rTex);
	collection->SetTexture(1, gTex);
	collection->SetTexture(2, bTex);

	return collection;
}

std::shared_ptr<Objects::Terrain> Objects::ResourceLoader::LoadTerrain(std::string filename, int mapSize, glm::vec3 scale, std::shared_ptr<TerrainTextureCollection> collection)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file)
	{
		std::cerr << "Error loading terrain" << std::endl;
		return NULL;
	}
	int width, height, channels;
	unsigned char * terrainData = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_L);
	std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>();
	terrain->SetScale(scale);
	terrain->SetSize(mapSize);
	terrain->SetTerrainHeightData(terrainData);
	terrain->SetTerrainTextureCollection(collection);

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> uvs;
	std::vector<int> indices;

	for (int z = 0; z < mapSize; z++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			int y = terrain->GetHeight(x, z);
			verts.push_back(glm::vec3(x, y, z));
			norms.push_back(glm::vec3(0, 1, 0));
			uvs.push_back(glm::vec2((float)x / ((float)mapSize - 1), (float)z / ((float)mapSize - 1)));
		}
	}
	for (int z = 0; z < mapSize - 1; z++)
	{
		for (int x = 0; x < mapSize - 1; x++)
		{
			indices.push_back((z * mapSize + x));
			indices.push_back(((z + 1) * mapSize) + x);
			indices.push_back((z * mapSize) + x + 1);

			indices.push_back((z * mapSize) + x + 1);
			indices.push_back(((z + 1) * mapSize) + x);
			indices.push_back(((z + 1) * mapSize) + x + 1);
		}
	}

	terrain->SetVertexCount(indices.size());

	GLuint vaoId = LoadToVAO(verts, uvs, norms, indices);
	terrain->SetVaoID(vaoId);

	return terrain;
}

GLuint Objects::ResourceLoader::GetGUIQuad()
{
	if (m_guiQuad <= 0)
	{
		std::vector<glm::vec2> positions =
		{
			glm::vec2(1, 1),
			glm::vec2(-1, 1),
			glm::vec2(1, -1),
			glm::vec2(-1, -1)
		};
		m_guiQuad = LoadToVAO(positions);
	}
	return m_guiQuad;
}