#include "Level.h"
#include "LevelLoader.h"

Level::Level(void)
{
	//dont use this
}

Level::Level(const char* levelName, const char* image, const char* file)
{
	xmlFile = file;
	name = levelName;
	imageLink = image;
}

Level::~Level(void)
{
}

int** Level::LoadLevel()
{
	LevelLoader loader;
	return loader.LoadLevel(xmlFile);
}
