#include <Core/BearBones.h>
#include <Collision/CollisionDetector.h>

std::shared_ptr<Objects::RigidBody> body1, body2, body3, body4, body5;


void CalculateFrameRate()
{
	static float framesPerSecond = 0.0f;       // This will store our fps
	static float lastTime = 0.0f;       // This will hold the time from the last frame
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		if (true) fprintf(stderr, "\nCurrent Frames Per Second: %d\n\n", (int)framesPerSecond);
		framesPerSecond = 0;
	}
}

void collisionCallback(std::shared_ptr<Objects::Entity> entity1, std::shared_ptr<Objects::Entity> entity2)
{
	entity2->SetPosition(glm::vec3(entity2->GetPosition().x + 0.1f, entity2->GetPosition().y, entity2->GetPosition().z), true);
}

void updateCallback(int dx)
{
	int currentMouseX = 0;
	int currentMouseY = 0;
	int winX = 0;
	int winY = 0;
	CalculateFrameRate();
	// Get the managers.
	Core::BearBones * bb = Core::BearBones::GetInstance();
	Input::InputManager * im = Input::InputManager::GetInstance();
	std::shared_ptr<Objects::Camera> camera;

	// Get the window size and mouse positions
	bb->GetWindowSize(winX, winY);
	im->GetMousePosition(currentMouseX, currentMouseY);
	// find the change in the mouse position.
	int deltaX = currentMouseX - (winX / 2);
	int deltaY = currentMouseY - (winY / 2);

	bb->GetCamera(camera);

	// Rotate the camera.
	camera->Rotate(deltaX, deltaY, dx);

	// On x -> Quit the game.
	if (im->GetKeyState('x') == Input::KS_KEY_PRESSED)
	{
		bb->Quit();
	}
	// On t -> Print camera location
	if (im->GetKeyState('t') == Input::KS_KEY_PRESSED)
	{
		glm::vec3 position = camera->GetPosition();
		std::cout << "Camera Position: x-" << position.x << " y-" << position.y << " z-" << position.z << std::endl;
	}
	// On w -> Walk forward.
	if (im->GetKeyState('w') == Input::KS_KEY_PRESSED || im->GetKeyState('w') == Input::KS_KEY_REPEAT)
	{
		camera->Walk(Objects::FORWARD, dx);
	}
	// On s -> Walk backwards
	if (im->GetKeyState('s') == Input::KS_KEY_PRESSED || im->GetKeyState('s') == Input::KS_KEY_REPEAT)
	{
		camera->Walk(Objects::BACKWARD, dx);
	}
	// On a -> Strafe left
	if (im->GetKeyState('a') == Input::KS_KEY_PRESSED || im->GetKeyState('a') == Input::KS_KEY_REPEAT)
	{
		camera->Strafe(Objects::LEFT, dx);
	}
	// On d -> Strafe right
	if (im->GetKeyState('d') == Input::KS_KEY_PRESSED || im->GetKeyState('d') == Input::KS_KEY_REPEAT)
	{
		camera->Strafe(Objects::RIGHT, dx);
	}
	if (im->GetKeyState('l') == Input::KS_KEY_PRESSED)// || im->GetKeyState('l') == Input::KS_KEY_REPEAT)
	{
		//body1->SetPosition(glm::vec3(body1->GetPosition().x + 0.1f, body1->GetPosition().y, body1->GetPosition().z), true);
		//body1->SetVelocity(glm::vec3(0.01f, 0, 0));
		//body1->SetAcceleration(glm::vec3(0.00001f, 0, 0));
		body1->SetTorque(glm::vec3(0.1f, 0, 0));
	}
	body1->Step(dx);
}

int main(int argc, char ** argv)
{
	// Initialize Bear Bones
	Core::BearBones * bb = Core::BearBones::GetInstance();
	bb->InitializeWindow(&argc, argv, 1280, 720);
	
	// Get the pointers to the loader, world, and camera.
	std::shared_ptr<Objects::ResourceLoader> loader;
	bb->GetResourceLoader(loader);
	std::shared_ptr<Objects::World> world;
	bb->GetWorld(world);
	std::shared_ptr<Objects::Camera> camera;
	bb->GetCamera(camera);
	// Set the camera position
	//camera->SetPosition(-132.0f, 0.0f, 167.0f);
	camera->SetPosition(0.0f, 0.0f, 0.0f);

	// Add resources here
	/*std::shared_ptr<Objects::Texture> tex = loader->LoadTexture("res/ECL_Texture.png");
	std::shared_ptr<Objects::ObjModel> model = loader->LoadOBJModel("res/ECL_baked.obj", tex);
	std::shared_ptr<Objects::StaticEntity> entity = loader->CreateStaticEntity(model, glm::vec3(0, -25, 0), glm::vec3(270, 0, 0), glm::vec3(10, 10, 10));
	world->AddTexture(tex);
	world->AddObjModel(model);
	world->AddStaticEntity(entity);*/
	std::shared_ptr<Objects::Texture> tex = loader->LoadTexture("res/rock.png");
	std::shared_ptr<Objects::ObjModel> model = loader->LoadOBJModel("res/rock.obj", tex);

	body1 = loader->CreateRigidBody(model, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	body2 = loader->CreateRigidBody(model, glm::vec3(20, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	body3 = loader->CreateRigidBody(model, glm::vec3(40, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	body4 = loader->CreateRigidBody(model, glm::vec3(60, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	body5 = loader->CreateRigidBody(model, glm::vec3(80, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	bb->RegisterEntityForCollision(body1);
	bb->RegisterEntityForCollision(body2);
	bb->RegisterEntityForCollision(body3);
	bb->RegisterEntityForCollision(body4);
	bb->RegisterEntityForCollision(body5);

	world->AddTexture(tex);
	world->AddObjModel(model);

	world->AddRigidBody(body1);
	world->AddRigidBody(body2);
	world->AddRigidBody(body3);
	world->AddRigidBody(body4);
	world->AddRigidBody(body5);

	// Set the update callback and begin the main loop
	bb->SetUpdateCallback(updateCallback);
	bb->SetCollisionCallback(collisionCallback);
	bb->BeginMainGameLoop();

}