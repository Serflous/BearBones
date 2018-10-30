#include <Core/BearBones.h>
#include <Collision/CollisionDetector.h>
#include <Collision/BoundingSphere.h>
#include <Collision/AABB.h>
#include <Collision/OBB.h>
bool quitting = false;
std::shared_ptr<Objects::AIEntity> m_ai;
std::shared_ptr<std::vector<std::shared_ptr<Objects::Waypoint>>> m_waypoints;
std::shared_ptr<Objects::Waypoint> m_currentWaypoint;

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
	bool reachedDestination = m_ai->IncrementMovement(dx);
	if (reachedDestination)
	{
		//waiting = true;
		m_currentWaypoint = m_currentWaypoint->GetNextWaypoint();
		m_ai->SetDestination(m_currentWaypoint->GetPosition());
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
	camera->SetPosition(0, 3, 0);

	// Add resources here
	// -Textures
	std::shared_ptr<Objects::Texture> tex_Chair_Bake = loader->LoadTexture("res/Chair/Chair_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Centre_Table = loader->LoadTexture("res/Centre Table/Centre_Table_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Lecturn = loader->LoadTexture("res/Lecturn/Lecturn_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level01 = loader->LoadTexture("res/Level 01/Level01_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level02 = loader->LoadTexture("res/Level 02/Level02_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level03 = loader->LoadTexture("res/Level 03/Level03_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level04 = loader->LoadTexture("res/Level 04/Level04_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level05 = loader->LoadTexture("res/Level 05/Level05_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level06 = loader->LoadTexture("res/Level 06/Level06_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Level07 = loader->LoadTexture("res/Level 07/Level07_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room01 = loader->LoadTexture("res/Room 01/Room01_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room02 = loader->LoadTexture("res/Room 02/Room02_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room03 = loader->LoadTexture("res/Room 03/Room03_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room04 = loader->LoadTexture("res/Room 04/Room04_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room05 = loader->LoadTexture("res/Room 05/Room05_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room06 = loader->LoadTexture("res/Room 06/Room06_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room07 = loader->LoadTexture("res/Room 07/Room07_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room08 = loader->LoadTexture("res/Room 08/Room08_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room09 = loader->LoadTexture("res/Room 09/Room09_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room10 = loader->LoadTexture("res/Room 10/Room10_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room11 = loader->LoadTexture("res/Room 11/Room11_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room12 = loader->LoadTexture("res/Room 12/Room12_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room13 = loader->LoadTexture("res/Room 13/Room13_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room14 = loader->LoadTexture("res/Room 14/Room14_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room15 = loader->LoadTexture("res/Room 15/Room15_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room16 = loader->LoadTexture("res/Room 16/Room16_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room17 = loader->LoadTexture("res/Room 17/Room17_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Room18 = loader->LoadTexture("res/Room 18/Room18_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Screen = loader->LoadTexture("res/Screen/Screen_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Wing_Table = loader->LoadTexture("res/Wing Table/Wing_Table_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Wing_Table_Ground = loader->LoadTexture("res/Wing Table Ground/Wing_Table_Ground_Bake.png");
	std::shared_ptr<Objects::Texture> tex_Ground = loader->LoadTexture("res/Ground/Ground_Baked.png");

	// -Models
	std::shared_ptr<Objects::ObjModel> obj_Chair = loader->LoadOBJModel("res/Chair/Chair.mtl.obj", tex_Chair_Bake);
	std::shared_ptr<Objects::ObjModel> obj_Centre_Table = loader->LoadOBJModel("res/Centre Table/Centre_Table.obj", tex_Centre_Table);
	std::shared_ptr<Objects::ObjModel> obj_Lecturn = loader->LoadOBJModel("res/Lecturn/Lecturn.mtl.obj", tex_Lecturn);
	std::shared_ptr<Objects::ObjModel> obj_Level01 = loader->LoadOBJModel("res/Level 01/Level01.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Level02 = loader->LoadOBJModel("res/Level 02/Level02.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Level03 = loader->LoadOBJModel("res/Level 03/Level03.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Level04 = loader->LoadOBJModel("res/Level 04/Level04.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Level05 = loader->LoadOBJModel("res/Level 05/Level05.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Level06 = loader->LoadOBJModel("res/Level 06/Level06.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Level07 = loader->LoadOBJModel("res/Level 07/Level07.obj", tex_Level01);
	std::shared_ptr<Objects::ObjModel> obj_Room01 = loader->LoadOBJModel("res/Room 01/Room01.obj", tex_Room01);
	std::shared_ptr<Objects::ObjModel> obj_Room02 = loader->LoadOBJModel("res/Room 02/Room02.obj", tex_Room02);
	std::shared_ptr<Objects::ObjModel> obj_Room03 = loader->LoadOBJModel("res/Room 03/Room03.obj", tex_Room03);
	std::shared_ptr<Objects::ObjModel> obj_Room04 = loader->LoadOBJModel("res/Room 04/Room04.obj", tex_Room04);
	std::shared_ptr<Objects::ObjModel> obj_Room05 = loader->LoadOBJModel("res/Room 05/Room05.obj", tex_Room05);
	std::shared_ptr<Objects::ObjModel> obj_Room06 = loader->LoadOBJModel("res/Room 06/Room06.obj", tex_Room06);
	std::shared_ptr<Objects::ObjModel> obj_Room07 = loader->LoadOBJModel("res/Room 07/Room07.obj", tex_Room07);
	std::shared_ptr<Objects::ObjModel> obj_Room08 = loader->LoadOBJModel("res/Room 08/Room08.obj", tex_Room08);
	std::shared_ptr<Objects::ObjModel> obj_Room09 = loader->LoadOBJModel("res/Room 09/Room09.obj", tex_Room09);
	std::shared_ptr<Objects::ObjModel> obj_Room10 = loader->LoadOBJModel("res/Room 10/Room10.obj", tex_Room10);
	std::shared_ptr<Objects::ObjModel> obj_Room11 = loader->LoadOBJModel("res/Room 11/Room11.obj", tex_Room11);
	std::shared_ptr<Objects::ObjModel> obj_Room12 = loader->LoadOBJModel("res/Room 12/Room12.obj", tex_Room12);
	std::shared_ptr<Objects::ObjModel> obj_Room13 = loader->LoadOBJModel("res/Room 13/Room13.obj", tex_Room13);
	std::shared_ptr<Objects::ObjModel> obj_Room14 = loader->LoadOBJModel("res/Room 14/Room14.obj", tex_Room14);
	std::shared_ptr<Objects::ObjModel> obj_Room15 = loader->LoadOBJModel("res/Room 15/Room15.obj", tex_Room15);
	std::shared_ptr<Objects::ObjModel> obj_Room16 = loader->LoadOBJModel("res/Room 16/Room16.obj", tex_Room16);
	std::shared_ptr<Objects::ObjModel> obj_Room17 = loader->LoadOBJModel("res/Room 17/Room17.obj", tex_Room17);
	std::shared_ptr<Objects::ObjModel> obj_Room18 = loader->LoadOBJModel("res/Room 18/Room18.obj", tex_Room18);
	std::shared_ptr<Objects::ObjModel> obj_Screen = loader->LoadOBJModel("res/Screen/Screen.obj", tex_Screen);
	std::shared_ptr<Objects::ObjModel> obj_Wing_Table = loader->LoadOBJModel("res/Wing Table/Wing_Table.obj", tex_Wing_Table);
	std::shared_ptr<Objects::ObjModel> obj_Wing_Table_Ground = loader->LoadOBJModel("res/Wing Table Ground/Wing_Table_Ground.mtl.obj", tex_Wing_Table_Ground);
	std::shared_ptr<Objects::ObjModel> obj_Ground = loader->LoadOBJModel("res/Ground/Ground.obj", tex_Ground);

	// Entity
	std::shared_ptr<Objects::StaticEntity> ent_Chair = loader->CreateStaticEntity(obj_Chair, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Centre_Table = loader->CreateStaticEntity(obj_Centre_Table, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Lecturn = loader->CreateStaticEntity(obj_Lecturn, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level01 = loader->CreateStaticEntity(obj_Level01, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level02 = loader->CreateStaticEntity(obj_Level02, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level03 = loader->CreateStaticEntity(obj_Level03, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level04 = loader->CreateStaticEntity(obj_Level04, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level05 = loader->CreateStaticEntity(obj_Level05, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level06 = loader->CreateStaticEntity(obj_Level06, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Level07 = loader->CreateStaticEntity(obj_Level07, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Ground = loader->CreateStaticEntity(obj_Ground, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room01 = loader->CreateStaticEntity(obj_Room01, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room02 = loader->CreateStaticEntity(obj_Room02, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room03 = loader->CreateStaticEntity(obj_Room03, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room04 = loader->CreateStaticEntity(obj_Room04, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room05 = loader->CreateStaticEntity(obj_Room05, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room06 = loader->CreateStaticEntity(obj_Room06, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room07 = loader->CreateStaticEntity(obj_Room07, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room08 = loader->CreateStaticEntity(obj_Room08, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room09 = loader->CreateStaticEntity(obj_Room09, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room10 = loader->CreateStaticEntity(obj_Room10, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room11 = loader->CreateStaticEntity(obj_Room11, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room12 = loader->CreateStaticEntity(obj_Room12, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room13 = loader->CreateStaticEntity(obj_Room13, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room14 = loader->CreateStaticEntity(obj_Room14, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room15 = loader->CreateStaticEntity(obj_Room15, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room16 = loader->CreateStaticEntity(obj_Room16, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Room17 = loader->CreateStaticEntity(obj_Room17, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Screen = loader->CreateStaticEntity(obj_Screen, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Wing_Table = loader->CreateStaticEntity(obj_Wing_Table, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::shared_ptr<Objects::StaticEntity> ent_Wing_Table_Ground = loader->CreateStaticEntity(obj_Wing_Table_Ground, glm::vec3(30, 0, 140), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	// Terrain
	std::shared_ptr<Objects::TerrainTextureCollection> terrainTextures = loader->LoadTerrainTextures("res/carpet.png", "res/Dirt_Terrain.png", "res/Rock_Terrain.png", "res/RockIce_Terrain.png");
	std::shared_ptr<Objects::Terrain> terrain = loader->LoadTerrain("res/heightFlat256.png", 256, glm::vec3(1, 1, 1), terrainTextures);
	terrain->SetPosition(glm::vec3(0, 0, 0));

	// Load into the engine
	world->AddTexture(tex_Chair_Bake);
	world->AddTexture(tex_Centre_Table);
	world->AddTexture(tex_Lecturn);
	world->AddTexture(tex_Level01);
	world->AddTexture(tex_Level02);
	world->AddTexture(tex_Level03);
	world->AddTexture(tex_Level04);
	world->AddTexture(tex_Level05);
	world->AddTexture(tex_Level06);
	world->AddTexture(tex_Level07);
	world->AddTexture(tex_Room01);
	world->AddTexture(tex_Room02);
	world->AddTexture(tex_Room03);
	world->AddTexture(tex_Room04);
	world->AddTexture(tex_Room05);
	world->AddTexture(tex_Room06);
	world->AddTexture(tex_Room07);
	world->AddTexture(tex_Room08);
	world->AddTexture(tex_Room09);
	world->AddTexture(tex_Room10);
	world->AddTexture(tex_Room11);
	world->AddTexture(tex_Room12);
	world->AddTexture(tex_Room13);
	world->AddTexture(tex_Room14);
	world->AddTexture(tex_Room15);
	world->AddTexture(tex_Room16);
	world->AddTexture(tex_Room17);
	world->AddTexture(tex_Room18);
	world->AddTexture(tex_Screen);
	world->AddTexture(tex_Wing_Table);
	world->AddTexture(tex_Wing_Table_Ground);
	world->AddTexture(tex_Ground);

	world->AddObjModel(obj_Chair);
	world->AddObjModel(obj_Centre_Table);
	world->AddObjModel(obj_Lecturn);
	world->AddObjModel(obj_Level01);
	world->AddObjModel(obj_Level02);
	world->AddObjModel(obj_Level03);
	world->AddObjModel(obj_Level04);
	world->AddObjModel(obj_Level05);
	world->AddObjModel(obj_Level06);
	world->AddObjModel(obj_Level07);
	world->AddObjModel(obj_Room01);
	world->AddObjModel(obj_Room02);
	world->AddObjModel(obj_Room03);
	world->AddObjModel(obj_Room04);
	world->AddObjModel(obj_Room05);
	world->AddObjModel(obj_Room06);
	world->AddObjModel(obj_Room07);
	world->AddObjModel(obj_Room08);
	world->AddObjModel(obj_Room09);
	world->AddObjModel(obj_Room10);
	world->AddObjModel(obj_Room11);
	world->AddObjModel(obj_Room12);
	world->AddObjModel(obj_Room13);
	world->AddObjModel(obj_Room14);
	world->AddObjModel(obj_Room15);
	world->AddObjModel(obj_Room16);
	world->AddObjModel(obj_Room17);
	world->AddObjModel(obj_Room18);
	world->AddObjModel(obj_Screen);
	world->AddObjModel(obj_Wing_Table);
	world->AddObjModel(obj_Wing_Table_Ground);
	world->AddObjModel(obj_Ground);

	world->AddStaticEntity(ent_Chair);
	world->AddStaticEntity(ent_Centre_Table);
	world->AddStaticEntity(ent_Lecturn);
	world->AddStaticEntity(ent_Level01);
	world->AddStaticEntity(ent_Level02);
	world->AddStaticEntity(ent_Level03);
	world->AddStaticEntity(ent_Level04);
	world->AddStaticEntity(ent_Level05);
	world->AddStaticEntity(ent_Level06);
	world->AddStaticEntity(ent_Level07);
	world->AddStaticEntity(ent_Room01);
	world->AddStaticEntity(ent_Room02);
	world->AddStaticEntity(ent_Room03);
	world->AddStaticEntity(ent_Room04);
	world->AddStaticEntity(ent_Room05);
	world->AddStaticEntity(ent_Room06);
	world->AddStaticEntity(ent_Room07);
	world->AddStaticEntity(ent_Room08);
	world->AddStaticEntity(ent_Room09);
	world->AddStaticEntity(ent_Room10);
	world->AddStaticEntity(ent_Room11);
	world->AddStaticEntity(ent_Room12);
	world->AddStaticEntity(ent_Room13);
	world->AddStaticEntity(ent_Room14);
	world->AddStaticEntity(ent_Room15);
	world->AddStaticEntity(ent_Room16);
	world->AddStaticEntity(ent_Room17);
	world->AddStaticEntity(ent_Screen);
	world->AddStaticEntity(ent_Wing_Table);
	world->AddStaticEntity(ent_Wing_Table_Ground);
	world->AddStaticEntity(ent_Ground);

	world->AddTerrain(terrain);

	bb->RegisterEntityForCollision(ent_Chair);
	bb->RegisterEntityForCollision(ent_Centre_Table);
	bb->RegisterEntityForCollision(ent_Lecturn);
	bb->RegisterEntityForCollision(ent_Level01);
	bb->RegisterEntityForCollision(ent_Level02);
	bb->RegisterEntityForCollision(ent_Level03);
	bb->RegisterEntityForCollision(ent_Level04);
	bb->RegisterEntityForCollision(ent_Level05);
	bb->RegisterEntityForCollision(ent_Level06);
	bb->RegisterEntityForCollision(ent_Level07);
	bb->RegisterEntityForCollision(ent_Room01);
	bb->RegisterEntityForCollision(ent_Room02);
	bb->RegisterEntityForCollision(ent_Room03);
	bb->RegisterEntityForCollision(ent_Room04);
	bb->RegisterEntityForCollision(ent_Room05);
	bb->RegisterEntityForCollision(ent_Room06);
	bb->RegisterEntityForCollision(ent_Room07);
	bb->RegisterEntityForCollision(ent_Room08);
	bb->RegisterEntityForCollision(ent_Room09);
	bb->RegisterEntityForCollision(ent_Room10);
	bb->RegisterEntityForCollision(ent_Room11);
	bb->RegisterEntityForCollision(ent_Room12);
	bb->RegisterEntityForCollision(ent_Room13);
	bb->RegisterEntityForCollision(ent_Room14);
	bb->RegisterEntityForCollision(ent_Room15);
	bb->RegisterEntityForCollision(ent_Room16);
	bb->RegisterEntityForCollision(ent_Room17);
	bb->RegisterEntityForCollision(ent_Screen);
	bb->RegisterEntityForCollision(ent_Wing_Table);
	bb->RegisterEntityForCollision(ent_Wing_Table_Ground);
	bb->RegisterEntityForCollision(ent_Ground);

	m_waypoints = std::make_shared<std::vector<std::shared_ptr<Objects::Waypoint>>>();

	m_waypoints->push_back(std::make_shared<Objects::Waypoint>(Objects::Waypoint(glm::vec3(45, 3, 130))));
	m_waypoints->push_back(std::make_shared<Objects::Waypoint>(Objects::Waypoint(glm::vec3(15, 13, 130))));
	m_waypoints->push_back(std::make_shared<Objects::Waypoint>(Objects::Waypoint(glm::vec3(15, 13, 150))));
	m_waypoints->push_back(std::make_shared<Objects::Waypoint>(Objects::Waypoint(glm::vec3(45, 3, 150))));

	m_waypoints->at(0)->AddConnectedWaypoint(m_waypoints->at(1));
	m_waypoints->at(1)->AddConnectedWaypoint(m_waypoints->at(2));
	m_waypoints->at(2)->AddConnectedWaypoint(m_waypoints->at(3));
	m_waypoints->at(3)->AddConnectedWaypoint(m_waypoints->at(0));

	m_ai = std::make_shared<Objects::AIEntity>();

	world->AddDebugObject(m_ai);

	m_ai->SetPosition(glm::vec3(30, 5, 140));

	m_currentWaypoint = m_waypoints->at(0);
	m_ai->SetDestination(m_currentWaypoint->GetPosition());

	// Set callbacks
	bb->SetUpdateCallback(updateCallback);
	bb->SetCollisionCallback(collisionCallback);

	//Begin main game loop
	bb->BeginMainGameLoop();

}