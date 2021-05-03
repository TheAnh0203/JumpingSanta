#ifndef BUTTON_H
#define BUTTON_H

#include "BaseObject.h"

#define PLAYPAUSE_BUTTON 1
#define MENU_BUTTON 2
#define BACK_BUTTON 3

const int MENU_BUTTON_WIDTH = 138;
const int MENU_BUTTON_HEIGHT = 66;
const int PLAYPAUSE_BUTTON_WIDTH = 70;
const int PLAYPAUSE_BUTTON_HEIGHT = 59;
const int BACK_BUTTON_WIDTH = 71;
const int BACK_BUTTON_HEIGHT = 59;

class Button
{
private:
	SDL_Point position;
public:
	Button(int x, int y);
	bool IsInside(SDL_Event* event, int size);
	void Render(SDL_Renderer* gRenderer, BaseObject gButtonTexture);
};
#endif // !BUTTON_H