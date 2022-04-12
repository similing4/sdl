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
		this->loadingAnimationFinished = false;
		Sprite *loadingSprite = new Sprite(this->MainRenderRend, "resources/images/mota_launch.png", 166, 49, 239, 178, 0);
		this->loadingAnimation = new Animation(loadingSprite);
		this->loadingAnimation->speedAlpha = 3;
		this->loadingAnimation->setOnAlphaEgtEventListener([this]() -> void {
			this->loadingAnimation->speedAlpha = 0;
			this->loadingAnimationFinished = true;
		}, 255);

		Sprite *mosterSprite = new Sprite(this->MainRenderRend, "resources/charactors/031-Monster01.png", 200, 300, 64, 64);
		this->mosterAnimation = new Animation(mosterSprite, 6, 0, 4, 4);
		this->mosterAnimation->speedBlt = 10;
		this->mosterAnimation->play();
	}
	void MainScene::onUpdate(){
		this->loadingAnimation->onUpdate();
		if(this->loadingAnimationFinished)
			this->mosterAnimation->onUpdate();
	}
	void MainScene::onEvent(SDL_Event event){
		;
	}
}