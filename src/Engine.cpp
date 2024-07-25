#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Warrior.h"
#include "SDL2/SDL.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include <iostream>
#include "Enemy.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init() 
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) 
	{
		SDL_Log("Failed to Initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(m_Window == nullptr) 
	{
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(m_Renderer == nullptr) 
	{
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load())
	{
		std::cout << "Failed to load map" << std::endl;
		return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMaps("level1");

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");

	/*TextureManager::GetInstance()->Load("player", "assets/slime.png");
	TextureManager::GetInstance()->Load("player_walk", "assets/slimewalk.png");
	TextureManager::GetInstance()->Load("bg", "assets/epic_background.png");*/

	Warrior* player = new Warrior(new Properties("player_idle", 392, 64, 64, 64));
	Enemy* boss = new Enemy(new Properties("boss_idle", 96, 96, 96, 96));

	m_GameObjects.push_back(player);
    m_GameObjects.push_back(boss);

	Camera::GetInstance()->SetTarget(player->GetOrigin());
	return m_IsRunning = true;
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("bg", 0, 0, 1536, 927, 1, 1, 0.5);
	m_LevelMap->Render();
	//player->Draw();
	for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();

	SDL_RenderPresent(m_Renderer);
}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
	//player->Update(dt);
	for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Update(dt);

	Camera::GetInstance()->Update(dt);
	m_LevelMap->Update();

}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}

bool Engine::Clean() 
{
	for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Clean();

	TextureManager::GetInstance()->Clean();
	MapParser::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
}

void Engine::Quit() 
{
	m_IsRunning = false;
}