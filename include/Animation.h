#pragma once

#include <string>
#include "SDL2/SDL.h"

class Animation 
{

    public:
        Animation(bool repeat = true): m_Repeat(repeat){ m_IsEnded = false;}
        void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip Flip = SDL_FLIP_NONE);
		void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

        virtual void Update(float dt) = 0;
        inline bool IsEnded(){return m_IsEnded;}

    protected:
    	int m_Speed;
		int m_SpriteRow;
		int m_FrameCount;
        bool m_Repeat;
        bool m_IsEnded;
        int m_CurrentFrame;
        std::string m_TextureID;
};

/*class Animation
{
public:
	Animation(){}
	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip Flip = SDL_FLIP_NONE);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);


private:
	int m_Speed;
	int m_SpriteRow;
	int m_FrameCount;
	int m_CurrentFrame;
	std::string m_TextureID;
};*/