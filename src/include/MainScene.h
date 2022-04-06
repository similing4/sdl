#pragma once
#include "BaseScene.h"
#include <iostream>

namespace Scene {
	class MainScene : public BaseScene{
	private:
		SDL_Surface *logoSurface;
		SDL_Texture *logoTexture;
		SDL_Rect logoRect;
		int currentAlpha;
		int alphaChangeSpeed;
	public:
		MainScene(SDL_Renderer *MainRenderRend, SDL_Window *MainRenderWindow);
		virtual ~MainScene();
		void onInit();
	    void onDispose();
	    virtual void onUpdate();
	    virtual void onEvent(SDL_Event event);
	};
}