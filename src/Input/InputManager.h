#pragma once

#include <GL/glut.h>

namespace Input
{

		/**
		 * Represents the state of a key.
		 */
	enum KeyState
	{
		KS_KEY_PRESSED, /** The key has been pressed */
		KS_KEY_REPEAT, /** The key is being held */
		KS_KEY_RELEASED /** The key has been released */
	};

		/**
		 * Represents the state of a mouse button.
		 */
	enum ButtonState
	{
		BS_BUTTON_CLICK, /** The mouse button has been clicked. */
		BS_BUTTON_DOWN, /** The mouse button is down. */
		BS_BUTTON_UP /** The mouse button has is up */
	};

		/**
		 * The singleton class for managing the input for the engine. Stores the state of each mouse and keyboard to be polled at will.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class InputManager
	{
	public:
			/**
			 * Gets the singleton instance of the input manager.
			 * @return A pointer to the InputManager instance.
			 */
		static InputManager * GetInstance();
			/**
			 * Gets the current key state of the key.
			 * @param[in] key The key to check.
			 * @return The state of the key. Will be KS_KEY_PRESSED on first check, then it updates to KS_KEY_REPEAT for every subsequent check.
			 * @note The key is an integer. Can pass a char in place and it will use the ASCII value automatically.
			 */
		KeyState GetKeyState(int key);
			/**
			 * Gets the mouse position.
			 * @param[out] x The x position of the mouse.
			 * @param[out] y The y position of the mouse.
			 */
		void GetMousePosition(int & x, int & y);
			/**
			 * Gets the button state of the mouse.
			 * @param[in] button The mouse button to check.
			 * @return The current state of the button. Will be BS_BUTTON_CLICK on first check, and it updates to BS_BUTTON_DOWN  for every subsequent check.
			 */
		ButtonState GetButtonState(int button);
			/**
			 * The callback that will set the key internal values.
			 * @param[in] key The key that recieved the event.
			 * @param[in] pressed If the key has been pressed or not.
			 */
		void KeyCallback(int key, bool pressed);
			/**
			 * The callback that will set the mouse internal values.
			 * @param[in] button The button that recieved the event.
			 * @param[in] state The state of the button.
			 * @param[in] x The x position of the mouse at the time of the event.
			 * @param[in] y The y position of the mouse at the time of the event.
			 */
		void MouseCallback(int button, int state, int x, int y);
			/**
			 * The callback that will set the mouse position.
			 * @param[in] x The x position of the mouse.
			 * @param[in] y The y position of the mouse.
			 */
		void MouseMotionCallback(int x, int y);

	private:
		InputManager();
		~InputManager();
		InputManager(const InputManager & other);

		static InputManager * m_instance;
		KeyState m_keys[550];
		KeyState m_prevKeys[550];
		int m_x, m_y;
		ButtonState m_buttonState[3];
		ButtonState m_prevButtonState[3];
	};

}