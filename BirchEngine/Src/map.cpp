#include "map.h"
#include "TextureManager.h"

int lvl1[20][25] = 
{
	// this is the map grid 
	{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0},

};

Map::Map()
{
	// loading in the textures for the different fields 
	dirt = TextureManager::LoadTexture("assets/dirt.png");
	water = TextureManager::LoadTexture("assets/water.png");
	grass = TextureManager::LoadTexture("assets/grass.png");

	LoadMap(lvl1); 

	src.x = 0;
	src.y = 0; 
	src.w = 32;
	src.h = 32;

	dest.w = 32;
	dest.h = 32;
	dest.x = 0;
	dest.y = 0; 
}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0; 

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column]; 

			dest.x = column * 32;
			dest.y = row * 32; 

			// setting the textures to the different numbers 
			switch (type)
			{
			case 0: 
				TextureManager::Draw(water, src, dest);
				break; 
			case 1: 
				TextureManager::Draw(grass, src, dest);
				break; 
			case 2: 
				TextureManager::Draw(dirt, src, dest);
				break;
			default: 
				break; 
			}
		}
	}
}