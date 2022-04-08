#include "Scene/BaseScene.h"

namespace Scene {
	BaseScene::BaseScene(SDL_Renderer *MainRenderRend, SDL_Window *MainRenderWindow){
		this->MainRenderRend = MainRenderRend;
		this->MainRenderWindow = MainRenderWindow;
	}
	BaseScene::~BaseScene() {
		this->MainRenderRend = NULL;
		this->MainRenderWindow = NULL;
	}
	void BaseScene::onUpdate(){
		;
	}
	void BaseScene::onEvent(SDL_Event event){
		;
	}
	int BaseScene::getWindowWidth(){
		return SDL_GetWindowSurface(MainRenderWindow)->w;
	}
	int BaseScene::getWindowHeight(){
		return SDL_GetWindowSurface(MainRenderWindow)->h;
	}
}