#pragma once
#include "tinyxml2.h"
using namespace tinyxml2;

class LevelLoader
{
public:
	LevelLoader();
	int** LoadLevel(const char* filename);
	void CreateLevel();
	void CreateXMLDoc();
	void DrawLevel(int** level);
};