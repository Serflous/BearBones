#include "InputManager.h"

Input::InputManager * Input::InputManager::m_instance;

Input::InputManager::InputManager()
{
	for (int i = 0; i < 550; i++)
	{
		m_keys[i] = KS_KEY_RELEASED;
		m_prevKeys[i] = KS_KEY_RELEASED;
	}
	for (int i = 0; i < 3; i++)
	{
		m_buttonState[i] = BS_BUTTON_UP;
		m_prevButtonState[i] = BS_BUTTON_UP;
	}
}

Input::InputManager::~InputManager()
{

}
Input::InputManager::InputManager(const InputManager & other)
{

}

Input::InputManager * Input::InputManager::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new InputManager();
	}
	return m_instance;
}

Input::KeyState Input::InputManager::GetKeyState(int key)
{
	if (m_prevKeys[key] == KS_KEY_PRESSED)
		m_keys[key] = KS_KEY_REPEAT;
	m_prevKeys[key] = m_keys[key];
	return m_keys[key];
}

void Input::InputManager::GetMousePosition(int & x, int & y)
{
	x = m_x;
	y = m_y;
}

Input::ButtonState Input::InputManager::GetButtonState(int button)
{
	if (m_prevButtonState[button] == BS_BUTTON_CLICK)
		m_buttonState[button] = BS_BUTTON_DOWN;
	m_prevButtonState[button] = m_buttonState[button];
	return m_buttonState[button];
}

void Input::InputManager::KeyCallback(int key, bool pressed)
{
	m_keys[key] = pressed ? KS_KEY_PRESSED : KS_KEY_RELEASED;
}

void Input::InputManager::MouseCallback(int button, int state, int x, int y)
{
	m_x = x;
	m_y = y;
	m_buttonState[button] = state == GLUT_DOWN ? BS_BUTTON_CLICK : BS_BUTTON_UP;
}

void Input::InputManager::MouseMotionCallback(int x, int y)
{
	m_x = x;
	m_y = y;
}