#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "../Objects/ResourceLoader.h"
#include "../Objects/World.h"
#include "../Input/InputManager.h"
#include "../Rendering/Renderer.h"
#include "../Objects/Camera.h"

namespace Core
{

	typedef void(*f)(int);
	class BearBones
	{

	public:
		static BearBones * GetInstance();

		int InitializeWindow(int * argc, char ** argv, int winX, int winY);
		void BeginMainGameLoop();
		void DrawCallback();
		void ReshapeCallback(int x, int y);
		void Update(int dx);
		void GetWindowSize(int & x, int & y);
		void Quit();
		void SetUpdateCallback(f callback);
		void GetResourceLoader(std::shared_ptr<Objects::ResourceLoader> & loader);
		void GetWorld(std::shared_ptr<Objects::World> & world);
		void GetCamera(std::shared_ptr<Objects::Camera> & camera);

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
	};


}