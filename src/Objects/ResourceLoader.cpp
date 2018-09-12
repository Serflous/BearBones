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

Objects::Texture Objects::ResourceLoader::LoadTexture(std::string filename, int x, int y)
{
	GLuint texId = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS |  SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	Texture tex;
	tex.SetTextureID(texId);

	std::cout << "Texture loaded: " << filename << std::endl;

	return tex;
}

Objects::ObjModel Objects::ResourceLoader::LoadOBJModel(std::string filename, Texture texture)
{
	std::ifstream in(filename);
	if (!in)
	{
		throw new std::invalid_argument("File not found: " + filename);
	}

	/*std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indicies;
	std::vector<float> verticesArray;
	std::vector<float> normalArray;
	std::vector<float> textureArray;
	std::string line;

	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			verticies.push_back(v);
		}
		else if (line.substr(0, 3) == "vn ")
		{
			std::istringstream s(line.substr(3));
			glm::vec3 n;
			s >> n.x; s >> n.y; s >> n.z;
			normals.push_back(n);
		}
		else if (line.substr(0, 3) == "vt ")
		{
			std::istringstream s(line.substr(3));
			glm::vec2 uv;
			s >> uv.x; s >> uv.y;
			textures.push_back(uv);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(2));
			std::string a, b, c;
			std::string f1v, f1t, f1n, f2v, f2t, f2n, f3v, f3t, f3n;
			s >> a; s >> b; s >> c;

			std::stringstream ss(a);
			getline(ss, f1v, '/');
			getline(ss, f1t, '/');
			getline(ss, f1n);

			ss.clear();
			ss.str(b);
			getline(ss, f2v, '/');
			getline(ss, f2t, '/');
			getline(ss, f2n);

			ss.clear();
			ss.str(c);
			getline(ss, f3v, '/');
			getline(ss, f3t, '/');
			getline(ss, f3n);

			ProcessVertex(f1v, f1t, f1n, indicies, textures, normals, textureArray, normalArray);
			ProcessVertex(f2v, f2t, f2n, indicies, textures, normals, textureArray, normalArray);
			ProcessVertex(f3v, f3t, f3n, indicies, textures, normals, textureArray, normalArray);
		}
	}
	std::vector<glm::vec3>::iterator vertIter;
	for (vertIter = verticies.begin(); vertIter != verticies.end(); vertIter++)
	{
		verticesArray.push_back((*vertIter).x);
		verticesArray.push_back((*vertIter).y);
		verticesArray.push_back((*vertIter).z);
	}

	int vaoId = LoadToVAO(verticesArray, textureArray, normalArray, indicies);*/

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

	Objects::ObjModel model;
	model.SetVAOID(vaoId);
	model.SetVertexCount(indicies.size());
	model.SetTexture(texture);
	model.SetVerticies(verticies);
	model.SetUVs(textures);
	model.SetNormals(normals);

	std::cout << "Model loaded: " << filename << std::endl;

	return model;
}

Objects::Entity Objects::ResourceLoader::CreateEntity(Objects::ObjModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	Objects::Entity entity;
	entity.SetModel(model);
	entity.SetPosition(position);
	entity.SetRotation(rotation);
	entity.SetScale(scale);
	return entity;
}

void Objects::ResourceLoader::ProcessVertex(std::string v, std::string t, std::string n, std::vector<int> &indicies, std::vector<glm::vec2> &textures, std::vector<glm::vec3> &normals, std::vector<float> &textureArray, std::vector<float> &normalArray)
{
	int currentVertexPointer = atoi(v.c_str()) - 1;
	int texPointer = atoi(t.c_str()) - 1;
	int normPointer = atoi(n.c_str()) - 1;

	indicies.push_back(currentVertexPointer);

	glm::vec2 currentTex = textures[texPointer];
	textureArray.push_back(currentTex.x);
	textureArray.push_back(1 - currentTex.y);

	glm::vec3 currentNorm = normals[normPointer];
	normalArray.push_back(currentNorm.x);
	normalArray.push_back(currentNorm.y);
	normalArray.push_back(currentNorm.z);
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