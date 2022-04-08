#include "Utils/Sprite.h"

using namespace std;

namespace Utils {
 	Sprite::Sprite(SDL_Renderer *MainRenderRend, string path, double x, double y, double w, double h, double alpha){
 		this->path = path;
		this->surface = IMG_Load(path.c_str());
		if (this->surface == NULL){
			string errmsg = "资源加载失败：" + path;
			global_errlog(errmsg.c_str());
			exit(0);
		}
		this->MainRenderRend = MainRenderRend;
		this->texture = SDL_CreateTextureFromSurface(MainRenderRend, this->surface);
		this->isBltEnabled = false;
		this->alpha = alpha;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->bltx = 0;
		this->blty = 0;
		this->bltw = 100;
		this->blth = 100;
 	}
	Sprite::~Sprite(){
		SDL_DestroyTexture(this->texture);
		SDL_FreeSurface(this->surface);
	}
	void Sprite::setBltEnabled(bool enabled) {
		this->isBltEnabled = enabled;
	}
	void Sprite::setBltRect(int x,int y,int w,int h){
		this->bltx = x;
		this->blty = y;
		this->bltw = w;
		this->blth = h;
	}
	void Sprite::setBltX(int x){
		this->bltx = x;
	}
	void Sprite::setBltY(int y){
		this->blty = y;
	}
	void Sprite::setBltW(int w){
		this->bltw = w;
	}
	void Sprite::setBltH(int h){
		this->blth = h;
	}
	int Sprite::getBltX(){
		return this->bltx;
	}
	int Sprite::getBltY(){
		return this->blty;
	}
	int Sprite::getBltW(){
		return this->bltw;
	}
	int Sprite::getBltH(){
		return this->blth;
	}
	void Sprite::setRect(double x,double y,double w,double h){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	void Sprite::setAlpha(double alpha){
		if(alpha > 255)
			alpha = 255;
		if(alpha < 0)
			alpha = 0;
		this->alpha = alpha;
	}
	void Sprite::setX(double x){
		this->x = x;
	}
	void Sprite::setY(double y){
		this->y = y;
	}
	void Sprite::setW(double w){
		this->w = w;
	}
	void Sprite::setH(double h){
		this->h = h;
	}
	double Sprite::getAlpha(){
		return this->alpha;
	}
	double Sprite::getX(){
		return this->x;
	}
	double Sprite::getY(){
		return this->y;
	}
	double Sprite::getW(){
		return this->w;
	}
	double Sprite::getH(){
		return this->h;
	}
	int Sprite::getTextureWidth(){
		return this->surface->w;
	}
	int Sprite::getTextureHeight(){
		return this->surface->h;
	}
	void Sprite::onUpdate(){
		SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(this->texture, (int)this->alpha);
		SDL_Rect rect;
		SDL_Rect bltRect;
		rect.x = (int)this->x;
		rect.y = (int)this->y;
		rect.w = (int)this->w;
		rect.h = (int)this->h;
		bltRect.x = (int)this->bltx;
		bltRect.y = (int)this->blty;
		bltRect.w = (int)this->bltw;
		bltRect.h = (int)this->blth;
		if(this->isBltEnabled){
			SDL_RenderCopy(this->MainRenderRend, this->texture, &bltRect, &rect);
		}else
			SDL_RenderCopy(this->MainRenderRend, this->texture, NULL, &rect);
	}
}