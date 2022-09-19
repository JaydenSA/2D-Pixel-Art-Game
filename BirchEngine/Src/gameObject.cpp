#include "gameObject.h"
#include "TextureManager.h"

gameObject::gameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	// setting the x and y with the inputs 
	xpos = x;
	ypos = y;
}

void gameObject::Update()
{
	xpos++;
	ypos++; 

	// srcRect is the original resolution of the image 
	srcRect.h = 820; 
	srcRect.w = 893; 
	srcRect.x = 0;
	srcRect.y = 0; 

	// destRect is the resolution you want it scaled it to, divide to go smaller, multiply to go bigger 
	// setting the location with x and y coordinates 
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w / 15; 
	destRect.h = srcRect.h / 15;
}

void gameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}