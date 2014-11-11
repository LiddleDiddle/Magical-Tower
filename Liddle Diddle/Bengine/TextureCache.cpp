#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace Bengine
{

	TextureCache::TextureCache(void)
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//lookup the texture and see if it's in the map
		auto mit = _textureMap.find(texturePath);

		//check if its not int the map
		if(mit == _textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it into the map
			_textureMap.insert(make_pair(texturePath,newTexture));
		
			std::cout << "Loaded Texture!\n";
			return newTexture;
		}
		//return texture
	
		return mit->second;
	}

	TextureCache::~TextureCache(void)
	{
	}

}