#include <Core/BearBones.h>
#include <Collision/CollisionDetector.h>
#include <Collision/BoundingSphere.h>
#include <Collision/AABB.h>
#include <Collision/OBB.h>

std::shared_ptr<Objects::RigidBody> rockEnt1, rockEnt2, rockEnt3, rockEnt4, rockEnt5;

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

void collisionCallback(std::shared_ptr<Objects::Entity> entity1, std::shared_ptr<Objects::Entity> entity2, glm::vec3 direction)
{
	std::cout << "Collision detected at point: X-(" << direction.x << ") Y-(" << direction.y << ") Z-(" << direction.z << ")" << std::endl;
}

void updateCallback(int dx)
{
	int currentMouseX = 0;
	int currentMouseY = 0;
	int winX = 0;
	int winY = 0;
	//CalculateFrameRate();
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
		std::cout << "Camera Rotation: x-" << camera->GetPitch() << " y-" << camera->GetYaw() << " z-" << camera->GetRoll() << std::endl;
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

	if (im->GetKeyState('j') == Input::KS_KEY_PRESSED || im->GetKeyState('j') == Input::KS_KEY_REPEAT)
	{
		glm::vec3 pos = rockEnt1->GetPosition();
		pos.x -= 0.001f * dx;
		rockEnt1->SetPosition(pos);
		rockEnt1->UpdateBoundingBox();
	}
	if (im->GetKeyState('l') == Input::KS_KEY_PRESSED || im->GetKeyState('l') == Input::KS_KEY_REPEAT)
	{
		glm::vec3 pos = rockEnt1->GetPosition();
		pos.x += 0.001f * dx;
		rockEnt1->SetPosition(pos);
		rockEnt1->UpdateBoundingBox();
	}
	if (im->GetKeyState('r') == Input::KS_KEY_PRESSED)
	{
		bb->RegisterRigidBodyForPhysics(rockEnt1);
		bb->RegisterRigidBodyForPhysics(rockEnt2);
		bb->RegisterRigidBodyForPhysics(rockEnt3);
		bb->RegisterRigidBodyForPhysics(rockEnt4);
		bb->RegisterRigidBodyForPhysics(rockEnt5);
	}
	if (im->GetKeyState('f') == Input::KS_KEY_PRESSED)
	{
		rockEnt4->ApplyForce(glm::vec3(2500, 0, -5000), 16);
	}
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
	camera->SetPosition(-13.0f, 2.0f, 13.0f);
	camera->SetRotation(glm::vec3(6, 83, 0));

	// Add resources here
	/*std::shared_ptr<Objects::Texture> tex = loader->LoadTexture("res/ECL_Texture.png");
	std::shared_ptr<Objects::ObjModel> model = loader->LoadOBJModel("res/ECL_baked.obj", tex);
	std::shared_ptr<Objects::StaticEntity> entity = loader->CreateStaticEntity(model, glm::vec3(0, -25, 0), glm::vec3(270, 0, 0), glm::vec3(10, 10, 10));
	world->AddTexture(tex);
	world->AddObjModel(model);
	world->AddStaticEntity(entity);*/
	std::shared_ptr<Objects::Texture> tex = loader->LoadTexture("res/rock.png");
	std::shared_ptr<Objects::ObjModel> model = loader->LoadOBJModel("res/rock.obj", tex);
	std::shared_ptr<Objects::PrimitiveModel> primCube = loader->CreateCubePrimitive(glm::vec3(0.827, 0.827, 0.827));
	std::shared_ptr<Objects::PrimitiveModel> primSphere1 = loader->CreateSpherePrimitive(glm::vec3(1, 0, 0));//glm::vec3(0.827, 0.827, 0.827));
	std::shared_ptr<Objects::PrimitiveModel> primSphere2 = loader->CreateSpherePrimitive(glm::vec3(0, 1, 0));
	std::shared_ptr<Objects::PrimitiveModel> primSphere3 = loader->CreateSpherePrimitive(glm::vec3(0, 0, 1));
	std::shared_ptr<Objects::PrimitiveModel> primSphere4 = loader->CreateSpherePrimitive(glm::vec3(1, 0, 1));
	std::shared_ptr<Objects::PrimitiveModel> primSphere5 = loader->CreateSpherePrimitive(glm::vec3(1, 1, 0));
	rockEnt1 = loader->CreateRigidBody(primSphere1, glm::vec3(0, 50, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	rockEnt2 = loader->CreateRigidBody(primSphere2, glm::vec3(10, 50, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	rockEnt3 = loader->CreateRigidBody(primSphere3, glm::vec3(10, 50, 10), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	rockEnt4 = loader->CreateRigidBody(primSphere4, glm::vec3(10, 50, 20), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	rockEnt5 = loader->CreateRigidBody(primSphere5, glm::vec3(20, 50, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	rockEnt1->SetMass(1);
	rockEnt2->SetMass(2);
	rockEnt3->SetMass(3);
	rockEnt4->SetMass(1);
	rockEnt5->SetMass(1);
	rockEnt1->ApplyForce(glm::vec3(190, 0, 0), 16);
	rockEnt2->ApplyForce(glm::vec3(0, 0, 210), 16);
	rockEnt3->ApplyForce(glm::vec3(30, 0, 0), 16);
	rockEnt4->ApplyForce(glm::vec3(0, 0, -200), 16);

	//bb->SetGravity(-0.0000001f);
	bb->SetGravity(glm::vec3(0, -9.8, 0));
	
	std::shared_ptr<Objects::TerrainTextureCollection> terrainTextures = loader->LoadTerrainTextures("res/Grass_Terrain.png", "res/Dirt_Terrain.png", "res/Rock_Terrain.png", "res/RockIce_Terrain.png");
	std::shared_ptr<Objects::Terrain> terrain = loader->LoadTerrain("res/heightFlat256.png", 256, glm::vec3(10, 1, 10), terrainTextures);
	terrain->SetPosition(glm::vec3(0, 0, 0));

	world->AddTexture(tex);
	world->AddObjModel(model);
	world->AddPrimitiveModel(primSphere1);
	world->AddPrimitiveModel(primSphere2);
	world->AddPrimitiveModel(primSphere3);
	world->AddPrimitiveModel(primSphere4);
	world->AddPrimitiveModel(primSphere5);
	world->AddRigidBody(rockEnt1);
	world->AddRigidBody(rockEnt2);
	world->AddRigidBody(rockEnt3);
	world->AddRigidBody(rockEnt4);
	world->AddRigidBody(rockEnt5);
	world->AddTerrain(terrain);

	bb->RegisterEntityForCollision(rockEnt1);
	bb->RegisterEntityForCollision(rockEnt2);
	bb->RegisterEntityForCollision(rockEnt3);
	bb->RegisterEntityForCollision(rockEnt4);
	bb->RegisterEntityForCollision(rockEnt5);
	//bb->RegisterRigidBodyForPhysics(rockEnt1);
	//bb->RegisterRigidBodyForPhysics(rockEnt2);

	// Set the update callback and begin the main loop
	bb->SetUpdateCallback(updateCallback);
	bb->SetCollisionCallback(collisionCallback);
	bb->BeginMainGameLoop();

}