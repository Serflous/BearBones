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

	m_loader = std::make_shared<Objects::ResourceLoader>();
	m_renderer = std::make_shared<Rendering::Renderer>();
	m_world = std::make_shared<Objects::World>();
	m_camera = std::make_shared<Objects::Camera>();
	m_collisionDetector = std::make_unique<Collision::CollisionDetector>();
	m_physicsEngine = std::make_shared<Physics::PhysicsEngine>();
	m_renderer->SetGUIVaoId(m_loader->GetGUIQuad());

	m_collisionDetector->SetWorld(m_world);
	m_collisionDetector->SetPhysicsEngine(m_physicsEngine);

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
	m_world->Update();
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

	m_collisionDetector->TestForCollisions(m_collisionCallback, dx);
	m_physicsEngine->Simulate(deltaTime);
	m_updateCallback(deltaTime);
	glutWarpPointer(m_winX / 2, m_winY / 2);

	glutTimerFunc(16, StaticUpdateCallback, currentTime);

	//if (waiting) 
	//{
	//	waitTime += ((float)deltaTime/1000);
	//	if (waitTime > m_ai->GetWaitTime()) {
	//		waiting = false;
	//		waitTime = 0;
	//	}
	//}
	//else {
	//	bool reachedDestination = m_ai->IncrementMovement(deltaTime);

	//	//pick a new waypoint. maybe dont move for a certain amount of deltaTime..
	//	if (reachedDestination)
	//	{
	//		waiting = true;
	//		m_currentWaypoint = m_currentWaypoint->GetNextWaypoint();
	//		m_ai->SetDestination(m_currentWaypoint->GetPosition());
	//	}
	//}
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

void Core::BearBones::GetAI(std::shared_ptr<Objects::AIEntity> & ai)
{
	ai = m_ai;
}

void Core::BearBones::SetGravity(glm::vec3 gravity)
{
	m_physicsEngine->SetGravity(gravity);
}

void Core::BearBones::RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity)
{
	m_collisionDetector->RegisterEntityForCollision(entity);
}

void Core::BearBones::RegisterRigidBodyForPhysics(std::shared_ptr<Objects::RigidBody> rb)
{
	m_physicsEngine->RegisterRidigBodyForPhysics(rb);
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