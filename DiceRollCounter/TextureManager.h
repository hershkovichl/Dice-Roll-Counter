#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>


class TextureManager
{
	static std::unordered_map<std::string, sf::Texture> textures;
	static void LoadTexture(const char* fileName);
public:
	static sf::Texture& GetTexture(const char* textureKey);
	static void Clear(); //clean up pour mess ( clear all textures from the unordered_map)

};

