#include "LevelLoader.h"
#include "Drawable.h"
#include <Bengine/ResourceManager.h>
#include <iostream>


const int WIDTH = 32;
const int HEIGHT = 18;

LevelLoader::LevelLoader()
{
	
}

void LevelLoader::CreateLevel()
{
	
}

int** LevelLoader::LoadLevel()
{
	XMLDocument xmlDoc;
	//creates array of level tiles
	int **level = new int* [HEIGHT];
	for (int i = 0; i < HEIGHT; ++i)
	{
		level[i] = new int[WIDTH];
		for (int j = 0; j < WIDTH; ++j)
		{
			level[i][j] = 0;
		}
	}

	//load xml file into array
	if (xmlDoc.LoadFile("TestLevel.xml") == 0)
	{
		std::cout << "loaded xml\n";
	}
	//set root
	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * rowElement;
	XMLElement * tileElement;
	
	int h = 0;
	int w = 0;
	for (rowElement = pRoot->FirstChildElement("Row"); rowElement; rowElement = rowElement->NextSiblingElement("Row"))
	{
		for(tileElement = rowElement->FirstChildElement("Tile"); tileElement; tileElement = tileElement->NextSiblingElement("Tile"))
		{
			int value;
			tileElement->QueryIntText(&value);
			level[h][w] = value;
			std::cout << level[h][w] << " ";
			w++;
		}
		h++;
		w = 0;
		std::cout << std::endl;
	}
	return level;
}

void LevelLoader::DrawLevel(int** level)
{
	//1920x1080
	
	/*for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (level[i][j] == 1)
			{
				
			}
		}
	}*/

}

