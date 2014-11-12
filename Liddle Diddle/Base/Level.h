#pragma once

class Level
{
public:
	Level(void);
	Level(const char* levelName, const char* image, const char* file);
	~Level(void);
	int** LoadLevel();
	const char* GetFile(){return xmlFile;}
	const char* GetName(){return name;}
	const char* GetImage(){return imageLink;}

private:
	const char* name;
	const char* imageLink;
	const char* xmlFile;
};

