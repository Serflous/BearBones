#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../Objects/ResourceLoader.h"
#include "../Objects/World.h"
#include "../Input/InputManager.h"
#include "../Rendering/Renderer.h"
#include "../Objects/Camera.h"
#include "../Collision/CollisionDetector.h"

namespace Core
{

	typedef void(*f)(int);
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
			 * @param callback A function pointer for the callback.
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

		void RegisterEntityForCollision(std::shared_ptr<Objects::Entity> entity);

		static void StaticDrawCallback();
		static void StaticReshapeCallback(int x, int y);
		static void StaticKeyboardCallback(unsigned char key, int x, int y);
		static void StaticKeyboardUpCallback(unsigned char key, int x, int y);
		static void StaticSpecialKeyboardCallback(int key, int x, int y);
		static void StaticSpecialKeyboardUpCallback(int key, int x, int y);
		static void StaticMouseCallback(int button, int state, int x, int y);
		static void StaticMousePositionCallback(int x, int y);
		static void StaticUpdateCallback(int value);
		static void APIENTRY StaticMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	private:
		BearBones();
		~BearBones();
		BearBones(const BearBones & other);

		int m_winX;
		int m_winY;
		f m_updateCallback;
		static BearBones * m_instance;

		std::shared_ptr<Objects::ResourceLoader> m_loader;
		std::shared_ptr<Rendering::Renderer> m_renderer;
		std::shared_ptr<Objects::World> m_world;
		std::shared_ptr<Objects::Camera> m_camera;
		std::unique_ptr<Collision::CollisionDetector> m_collisionDetector;
	};


}