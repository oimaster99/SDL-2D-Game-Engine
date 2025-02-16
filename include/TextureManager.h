#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include "SDL2/SDL.h"
#include <map>

class TextureManager 
{
public:
	static TextureManager* GetInstance() {return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}

	bool Load(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Drop(std::string id);
	void Clean();

	void Draw(std::string id, int x, int y, int width, int height, float scaleX = 1, float scaleY = 1, float scrollRatio = 0, SDL_RendererFlip flip=SDL_FLIP_NONE);
	void DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
	//void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip);


private:
	TextureManager(){}
	std::map<std::string, SDL_Texture*> m_TextureMap;
	static TextureManager* s_Instance;

};

#endif