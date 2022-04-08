#include "Scene/MainScene.h"

using namespace std;
using namespace Utils;
namespace Scene {
 	MainScene::MainScene(SDL_Renderer *MainRenderRend, SDL_Window *MainRenderWindow) : BaseScene(MainRenderRend, MainRenderWindow){
 		this->onInit();
 	}
	MainScene::~MainScene(){
		delete this->loadingAnimation->getSprite();
		delete this->loadingAnimation;
	}
	void MainScene::onInit(){
		Sprite *loadingSprite = new Sprite(this->MainRenderRend, "resources/images/mota_launch.png", 151, 60, 241, 179, 0);
		Sprite *mosterSprite = new Sprite(this->MainRenderRend, "resources/charactors/031-Monster01.png", 200, 300, 64, 64);
		this->loadingAnimation = new Animation(loadingSprite);
		this->loadingAnimation->speedAlpha = 1.5;
		this->mosterAnimation = new Animation(mosterSprite, 6, 0, 4, 4);
		this->mosterAnimation->speedBlt = 10;
		this->mosterAnimation->play();
	}
	void MainScene::onUpdate(){
		this->loadingAnimation->onUpdate();
		this->mosterAnimation->onUpdate();
		if(this->loadingAnimation->getSprite()->getAlpha() == 255)
			this->loadingAnimation->speedAlpha = -1.5;
		if(this->loadingAnimation->getSprite()->getAlpha() == 0)
			this->loadingAnimation->speedAlpha = 1.5;
	}
	void MainScene::onEvent(SDL_Event event){
		;
	}
}