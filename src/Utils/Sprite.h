#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;
extern void global_errlog(const char *str);
namespace Utils {
	class Sprite
	{
	private:
		SDL_Renderer *MainRenderRend;
		SDL_Surface *surface;
		SDL_Texture *texture;
		string path;
		bool isBltEnabled;
		double x;
		double y;
		double w;
		double h;
		int bltx;
		int blty;
		int bltw;
		int blth;
		double alpha;
	public:
		Sprite(SDL_Renderer *MainRenderRend, string path, double x = 0, double y = 0, double w = 100, double h = 100, double alpha = 255);
		~Sprite();
		void setBltEnabled(bool enabled);
		void setBltRect(int x,int y,int w,int h);
		void setBltX(int x);
		void setBltY(int y);
		void setBltW(int w);
		void setBltH(int h);
		int getBltX();
		int getBltY();
		int getBltW();
		int getBltH();
		void setRect(double x,double y,double w,double h);
		void setAlpha(double alpha);
		void setX(double x);
		void setY(double y);
		void setW(double w);
		void setH(double h);
		double getAlpha();
		double getX();
		double getY();
		double getW();
		double getH();
		int getTextureWidth();
		int getTextureHeight();
		virtual void onUpdate();
	};
}