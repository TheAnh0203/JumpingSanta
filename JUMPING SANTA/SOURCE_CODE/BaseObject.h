#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "GameBase.h"

class BaseObject
{
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
public:
	BaseObject();
	~BaseObject();

	void Free();
	
	bool LoadText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);
	bool LoadFile(std::string path, SDL_Renderer* gRenderer);

	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);
};

#endif // !BASEOBJECT_H