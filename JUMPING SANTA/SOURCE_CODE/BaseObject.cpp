#include "BaseObject.h"

BaseObject::BaseObject()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

void BaseObject::Free()
{
	if (mTexture != nullptr)
	{
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

bool BaseObject::LoadText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer)
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		std::cout << "Unable to render text surface." << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == nullptr)
		{
			std::cout << "Unable to create texture from rendered text." << std::endl;
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != nullptr;
}

bool BaseObject::LoadFile(std::string path, SDL_Renderer* gRenderer)
{
	Free();

	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == nullptr)
	{
		std::cout << "Unable to load image." << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
		if (mTexture == nullptr)
		{
			std::cout << "Unable to create texture from surface." << std::endl;
		}
		else
		{
			mWidth = tempSurface->w;
			mHeight = tempSurface->h;
		}

		SDL_FreeSurface(tempSurface);
	}

	return mTexture != nullptr;
}

void BaseObject::Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	SDL_Rect renderSpace = { x, y, mWidth, mHeight };

	if (clip != nullptr)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
}