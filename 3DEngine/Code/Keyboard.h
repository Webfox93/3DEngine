#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "windows.h"
#include "Dinput.h"
#include "KeyboardListener.h"
#include <vector>
#include <array>

class Keyboard
{
public:
	Keyboard(IDirectInputDevice8* argDevice);
	~Keyboard();
	
	void addKeyboardListener(KeyboardListener* argKeyboardListener);
	bool read();
	void processInput();
	void updateListeners();
private:

	IDirectInputDevice8* keyboard;
	std::array<unsigned char, 256> keyboardState;
	std::array<unsigned char, 256> keyboardStateOld;
	std::vector<KeyboardListener*> keyboardListeners;
};

#endif