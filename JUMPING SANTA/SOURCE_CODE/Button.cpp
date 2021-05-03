#include "Button.h"

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(SDL_Event* event, int size)
{
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		int button_width, button_height;
		if (size == PLAYPAUSE_BUTTON)
		{
			button_width = PLAYPAUSE_BUTTON_WIDTH;
			button_height = PLAYPAUSE_BUTTON_HEIGHT;
		}
		else if (size == MENU_BUTTON)
		{
			button_width = MENU_BUTTON_WIDTH;
			button_height = MENU_BUTTON_HEIGHT;
		}

		else if (size == BACK_BUTTON)
		{
			button_width = BACK_BUTTON_WIDTH;
			button_height = BACK_BUTTON_HEIGHT;
		}

		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void Button::Render(SDL_Renderer* gRenderer, BaseObject gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer);
}