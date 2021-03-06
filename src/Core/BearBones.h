#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GLM/gtc/type_ptr.hpp>

#include <iostream>
#include <map>

#include "../Objects/ResourceLoader.h"
#include "../Objects/World.h"
#include "../Affordance/AffordanceEngine.h"
#include "../Input/InputManager.h"
#include "../Rendering/Renderer.h"
#include "../Objects/Camera.h"
#include "../Util/Types.h"
#include "../Objects/Waypoint.h"
#include "../Collision/CollisionDetector.h"
#include "../Physics/PhysicsEngine.h"
#include "../AI/AIEntity.h"

namespace Core
{

	typedef void(*f)(int);
	typedef void(*fc)(std::shared_ptr<Objects::Entity> ent1, std::shared_ptr<Objects::Entity> ent2, glm::vec3 direction);
		/**
		* This is the main class of the engine. It is a singleton class that manages all of the engine's resources, and controls the interfaces
		* with FreeGLUT.
		* @author Mathew Causby
		* @version 0.1
		*/
	class BearBones
	{

	public:
			/**
			 * Gets the singleton instance of the BearBones engine.
			 * @return A pointer to the instance.
			 */
		static BearBones * GetInstance();

			/**
			 * Initializes the engine. Will create the window and sets the size.
			 * @param[inout] argc The amount of input arguments, supplied from main.
			 * @param[inout] argv The input argument array.
			 * @param[in] winX The width of the window.
			 * @param[in] winY The height of the window.
			 */
		int InitializeWindow(int * argc, char ** argv, int winX, int winY);

			/**
			 * Begins the main game loop. Will keep calling the update callback.
			 */
		void BeginMainGameLoop();

			/**
			 * The draw callback, called internally.
			 * @todo Make private.
			 */
		void DrawCallback();

			/**
			 * The reshape callback. Called internally
			 * @todo Make private
			 */
		void ReshapeCallback(int x, int y);

			/**
			 * The internal update function
			 * @param[in] dx The delta time.
			 * @todo Make private.
			 */
		void Update(int dx);

			/**
			 * Gets the current window size.
			 * @param[out] x The width of the window.
			 * @param[out] y The height of the window.
			 */
		void GetWindowSize(int & x, int & y);

			/**
			 * Closes and destroys the engine.
			 */
		void Quit();

			/**
			 * Sets the update callback to call every frame.
			 * @param[in] callback A function pointer for the callback.
			 */
		void SetUpdateCallback(f callback);

			/**
			 * Gets the resource loader used in the engine.
			 * @param[out] loader A pointer to the resource loader
			 */
		void GetResourceLoader(std::shared_ptr<Objects::ResourceLoader> & loader);

			/**
			 * Gets the world objects for the engine.
			 * @param[out] world A pointer to the world.
			 */
		void GetWorld(std::shared_ptr<Objects::World> & world);

			/**
			 * Gets the camera currently used in the engine.
			 * @param[out] A pointer to the camera.
			 */
		void GetCamera(std::shared_ptr<Objects::Camera> & camera);

			/**
			 * Sets the gravity for the game world.
			 * @param[in] gravity The force of gravity to apply.
			 */
		void SetGravity(glm::vec3 gravity);

			/**
			 * Registers an entity for collision.
			 * @param[in] entity The entity to apply collision to.
			 */
		void RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity);

			/**
			 * Registers an rigid body to be affected by physics.
			 * @param[in] rb The rigid body to apply physics to.
			 */
		void RegisterRigidBodyForPhysics(std::shared_ptr<Objects::RigidBody> rb);

			/**
			 * Sets a callback to the game engine for any collisions that occur.
			 * @param[in] callback The callback.
			 */
		void SetCollisionCallback(fc callback);

			/**
			 * Gets information pertaining to an AI entity.
			 * @param[out] ai Pointer to the AI entity.
			 */
		void GetAI(std::shared_ptr<Objects::AIEntity> & ai);

			/**
			 * Sends a callback to update how the world is rendered.
			 */
		static void StaticDrawCallback();

			/**
			 * Sends a callback to account for window size change.
			 * @param[in] x The X value of the window.
			 * @param[in] y The Y value of the window.
			 */
		static void StaticReshapeCallback(int x, int y);

			/**
			 * Sends a callback for any keys pressed.
			 * @param[in] key The key that has been pressed.
			 * @param[in] x
			 * @param[in] y
			 */
		static void StaticKeyboardCallback(unsigned char key, int x, int y);

			/**
			 * Sends a callback for any keys that are not being pressed.
			 * @param[in] key The key that is no longer being pressed.
			 * @param[in] x
			 * @param[in] y
			 */
		static void StaticKeyboardUpCallback(unsigned char key, int x, int y);

			/**
			 * Sends a callback for any special keys pressed.
			 * @param[in] key The special key that has been pressed.
			 * @param[in] x
			 * @param[in] y
			 */
		static void StaticSpecialKeyboardCallback(int key, int x, int y);

			/**
			 * Sends a callback for any special keys that are not being pressed.
			 * @param[in] key The special key that is no longer being pressed.
			 * @param[in] x
			 * @param[in] y
			 */
		static void StaticSpecialKeyboardUpCallback(int key, int x, int y);

			/**
			 * Sends a callback for any mouse buttons pressed.
			 * @param[in] button The button that has been pressed.
			 * @param[in] state The state of the button being pressed
			 * @param[in] x
			 * @param[in] y
			 */
		static void StaticMouseCallback(int button, int state, int x, int y);

			/**
			 * Sends a callback for any mouse movements given.
			 * @param[in] x The value of the mouse's X coordinate.
			 * @param[in] y The value of the mouse's Y coordinate.
			 */
		static void StaticMousePositionCallback(int x, int y);

			/**
			 * Sends a callback for any updates that need to be sent to the game engine.
			 * @param[in] value
			 */
		static void StaticUpdateCallback(int value);

			/**
			 * Sends a callback for any error messages that the game engine receives.
			 * @param[in] source Where the message was sent from.
			 * @param[in] type The type of message.
			 * @param[in] id The identification number of the message.
			 * @param[in] severity The severity of the message.
			 * @param[in] length The length of the message.
			 * @param[out] message Pointer to the contents of the message.
			 * @param[out] userParam Pointer to the user parameters.
			 */
		static void APIENTRY StaticMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	private:
		BearBones();
		~BearBones();
		BearBones(const BearBones & other);

		int m_winX;
		int m_winY;
		f m_updateCallback;
		fc m_collisionCallback;
		static BearBones * m_instance;

		std::shared_ptr<Objects::ResourceLoader> m_loader;
		std::shared_ptr<Rendering::Renderer> m_renderer;
		std::shared_ptr<Objects::World> m_world;
		std::shared_ptr<Objects::Camera> m_camera;
		std::unique_ptr<Collision::CollisionDetector> m_collisionDetector;
		std::shared_ptr<AffordanceEngine> m_affordanceEngine;
		std::shared_ptr<Physics::PhysicsEngine> m_physicsEngine;
		std::shared_ptr<Objects::AIEntity> m_ai;	
		/*std::shared_ptr<std::vector<std::shared_ptr<Objects::Waypoint>>> m_waypoints;
		std::shared_ptr<Objects::Waypoint> m_currentWaypoint;
		float waitTime = 0.0f;
		bool waiting = false;*/
	};


}