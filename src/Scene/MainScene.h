#pragma once
#include "Scene/BaseScene.h"
#include "Utils/Sprite.h"
#include "Utils/Animation.h"
#include <iostream>

using namespace Utils;
namespace Scene {
	class MainScene : public BaseScene{
	private:
		Animation *loadingAnimation;
		Animation *mosterAnimation;
		bool loadingAnimationFinished;
	public:
		MainScene(SDL_Renderer *MainRenderRend, SDL_Window *MainRenderWindow);
		virtual ~MainScene();
		void onInit();
	    void onDispose();
	    virtual void onUpdate();
	    virtual void onEvent(SDL_Event event);
	};
}