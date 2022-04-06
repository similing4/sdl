#include "MainScene.h"

using namespace std;
namespace Scene {
 	MainScene::MainScene(SDL_Renderer *MainRenderRend, SDL_Window *MainRenderWindow) : BaseScene(MainRenderRend, MainRenderWindow){
 		this->onInit();
 	}
	MainScene::~MainScene(){
	}
	void MainScene::onInit(){
		this->currentAlpha = 0;
		this->alphaChangeSpeed = 5;
		this->logoSurface = IMG_Load("resources/images/mota_launch.png");
		if (this->logoSurface == NULL){
			global_errlog(L"资源加载失败：resources/images/mota_launch.png");
			exit(0);
		}
		this->logoTexture = SDL_CreateTextureFromSurface(MainRenderRend, logoSurface);
		this->logoRect.x = 151;
		this->logoRect.y = 60;
		this->logoRect.w = 241;
		this->logoRect.h = 179;
	}
	void MainScene::onUpdate(){
		this->currentAlpha += alphaChangeSpeed;
		if(this->currentAlpha > 255){
			this->currentAlpha = 255;
			this->alphaChangeSpeed = -this->alphaChangeSpeed;
		}else if(this->currentAlpha <= 0){
			this->currentAlpha = 0;
			this->alphaChangeSpeed = -this->alphaChangeSpeed;
		}
		SDL_SetTextureBlendMode(this->logoTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(this->logoTexture, this->currentAlpha);
		SDL_RenderCopy(this->MainRenderRend, this->logoTexture, NULL, &this->logoRect);
	}
	void MainScene::onEvent(SDL_Event event){
		;
	}
}