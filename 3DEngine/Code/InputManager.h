/*
	3D Engine
	InputManager.h
	Purpose: Creates and manages the input devices.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "Dinput.h"
#include "windows.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	/*
		Initializes the directInput and creates input devices.

		@param HINSTANCE: The Modulehandle needed for directInput.
		@param HWND: The window that will catch the input of the input devices.
		@param screenWidth: The width of the screen, used to determine the borders of mouse.
		@param screenHeigth: The height of the screen, used to determine the borders of mouse.
	*/
	bool initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);

	/*
		Reads and processes the input every frame.
	*/
	bool frame();

	/*
		Passes a KeyboardListener to myKeyboard.

		@param argKeyboardListener: The Keyboardlistener to be passed through.
	*/
	void addListenerToKeyboard(KeyboardListener* argKeyboardListener);

	/*
		Passes a MouseListener to myMouse.

		@param argMouseListener: The MouseListener to be passed through.
	*/
	void addListenerToMouse(MouseListener* argMouseListener);

	/*
		Passes a JoystickListener to myJoystick.

		@param argJoystickListener: The JoystickListener to be passed through.
	*/
	void addListenerToJoystick(JoystickListener* argJoystickListener);

private:
	IDirectInput8* directInput;
	Keyboard* myKeyboard;
	Mouse* myMouse;
	Joystick* myJoystick;
};
#endif