#include "BearBones.h"

Core::BearBones * Core::BearBones::m_instance;

Core::BearBones * Core::BearBones::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new BearBones();
	}
	return m_instance;
}

Core::BearBones::BearBones()
{

}

Core::BearBones::~BearBones()
{

}

Core::BearBones::BearBones(const BearBones & other)
{

}

int Core::BearBones::InitializeWindow(int * argc, char ** argv, int winX, int winY)
{
	glutInit(argc, argv);
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_MULTISAMPLE, 16);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	m_winX = winX;
	m_winY = winY;
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(winX, winY);
	glutCreateWindow("Bear Bones");
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "Glew error: " << glewGetErrorString(error) << std::endl;
	}
	glutDisplayFunc(StaticDrawCallback);
	glutIdleFunc(StaticDrawCallback);
	glutTimerFunc(16, StaticUpdateCallback, 0);
	glutReshapeFunc(StaticReshapeCallback);
	glutKeyboardFunc(StaticKeyboardCallback);
	glutKeyboardUpFunc(StaticKeyboardUpCallback);
	glutSpecialFunc(StaticSpecialKeyboardCallback);
	glutSpecialUpFunc(StaticSpecialKeyboardUpCallback);
	glutMouseFunc(StaticMouseCallback);
	glutMotionFunc(StaticMousePositionCallback);
	glutPassiveMotionFunc(StaticMousePositionCallback);
	glClearColor(0.3922f, 0.5843f, 0.9294f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(StaticMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

	glutSetCursor(GLUT_CURSOR_NONE);

	m_primitiveIds = std::make_shared<std::map<Util::BB_Primitives, GLuint>>();
	m_loader = std::make_shared<Objects::ResourceLoader>();
	GeneratePrimitives();

	m_renderer = std::make_shared<Rendering::Renderer>();
	m_renderer->SetPrimitiveIds(m_primitiveIds);

	m_world = std::make_shared<Objects::World>();
	m_camera = std::make_shared<Objects::Camera>();
	m_collisionDetector = std::make_unique<Collision::CollisionDetector>();
	return 0;

}

void Core::BearBones::BeginMainGameLoop()
{
	m_renderer->Init();
	glutMainLoop();
}

void Core::BearBones::DrawCallback()
{
	m_renderer->RenderWorld(m_world, m_camera);
	glutSwapBuffers();
}

void Core::BearBones::ReshapeCallback(int x, int y)
{
	glViewport(0, 0, x, y);
	m_winX = x;
	m_winY = y;
	m_renderer->SetDimensions(x, y);
}

void Core::BearBones::Update(int dx)
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - dx;
	glutTimerFunc(16, StaticUpdateCallback, currentTime);

	m_collisionDetector->TestForCollisions(m_collisionCallback);

	m_updateCallback(deltaTime);
	glutWarpPointer(m_winX / 2, m_winY / 2);
}

void Core::BearBones::GetWindowSize(int & x, int & y)
{
	x = m_winX;
	y = m_winY;
}

void Core::BearBones::Quit()
{
	glutExit();
}

void Core::BearBones::SetUpdateCallback(f callback)
{
	m_updateCallback = callback;
}

void Core::BearBones::GetResourceLoader(std::shared_ptr<Objects::ResourceLoader> & loader)
{
	loader = m_loader;
}

void Core::BearBones::GetWorld(std::shared_ptr<Objects::World> & world)
{
	world = m_world;
}

void Core::BearBones::GetCamera(std::shared_ptr<Objects::Camera> & camera)
{
	camera = m_camera;
}

void Core::BearBones::RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity)
{
	m_collisionDetector->RegisterEntityForCollision(entity);
}

void Core::BearBones::SetCollisionCallback(fc callback)
{
	m_collisionCallback = callback;
}

void Core::BearBones::StaticDrawCallback()
{
	m_instance->DrawCallback();
}

void Core::BearBones::StaticReshapeCallback(int x, int y)
{
	m_instance->ReshapeCallback(x, y);
}

void Core::BearBones::StaticKeyboardCallback(unsigned char key, int x, int y)
{
	Input::InputManager::GetInstance()->KeyCallback(key, true);
}

void Core::BearBones::StaticKeyboardUpCallback(unsigned char key, int x, int y)
{
	Input::InputManager::GetInstance()->KeyCallback(key, false);
}

void Core::BearBones::StaticSpecialKeyboardCallback(int key, int x, int y)
{
	Input::InputManager::GetInstance()->KeyCallback(127 + key, true);
}

void Core::BearBones::StaticSpecialKeyboardUpCallback(int key, int x, int y)
{
	Input::InputManager::GetInstance()->KeyCallback(127 + key, false);
}

void Core::BearBones::StaticMouseCallback(int button, int state, int x, int y)
{
	Input::InputManager::GetInstance()->MouseCallback(button, state, x, y);
}

void Core::BearBones::StaticMousePositionCallback(int x, int y)
{
	Input::InputManager::GetInstance()->MouseMotionCallback(x, y);
}

void Core::BearBones::StaticUpdateCallback(int value)
{
	m_instance->Update(value);
}

void APIENTRY Core::BearBones::StaticMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	using namespace std;
	if (source == GL_DEBUG_SOURCE_API)
		return;
	cout << endl;
	cout << "Source: ";
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		cout << "API.";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		cout << "Window System.";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		cout << "Shader.";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		cout << "Third Party.";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		cout << "Application.";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		cout << "Other.";
		break;
	}
	cout << endl;
	cout << "Message: " << message << endl;
	cout << "Type: ";
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		cout << "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cout << "Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cout << "Undefined_Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cout << "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cout << "Performance";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cout << "Other";
		break;
	}
	cout << endl;
	cout << "Severity: ";
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		cout << "Low";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cout << "Medium";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cout << "High";
		break;
	}
	cout << endl;
}

void Core::BearBones::GeneratePrimitives()
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

	GLuint cubeId = m_loader->LoadPrimitive(cubePositions, cubeElements);
	m_primitiveIds->insert({ Util::BB_CUBE, cubeId });

}