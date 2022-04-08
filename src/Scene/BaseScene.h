#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

extern void global_errlog(const char *str);
namespace Scene {
	class BaseScene{
	protected:
	    SDL_Renderer *MainRenderRend;
	    SDL_Window *MainRenderWindow;
	public:
		BaseScene(SDL_Renderer *MainRenderRend, SDL_Window *MainRenderWindow);
		virtual ~BaseScene();
	    virtual void onUpdate();
	    virtual void onEvent(SDL_Event event);
	    int getWindowWidth();
		int getWindowHeight();
	};
}