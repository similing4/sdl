#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils/Sprite.h"

using namespace std;
extern void global_errlog(const char *str);
namespace Utils {
	class Animation
	{
	private:
		Sprite *sprite;
		bool isBlt; //是否是需要分割的图块
		int bltRectWidth; //分割每个图块宽度，通过colCount计算获得
		int bltRectHeight; //分割每个图块高度，通过rowCount计算获得
		int bltPlayColumn; //动画的行（列）
		int rowCount; //行数
		int colCount; //列数
		int frameCount; //总帧数
		unsigned long fp; //游戏帧数内部计数
		bool _isPlaying; //是否播放中
	public:
		/*
			sprite：动画精灵对象
			playDirection：播放方向，由2468控制，默认6，即→
			playColumn：播放第几行（列），默认0，即第一列
			colCount：精灵分割的列数
			rowCount：精灵分割的行数
		*/
		Animation(Sprite* sprite,int playDirection = 6, int playColumn = 0, int colCount = 1, int rowCount = 1);
		~Animation();
		void play(int frame = -1); //播放，frame表示从第几帧开始播放，-1表示从当前帧开始播放，只影响帧播放，不影响区域变化
		void stop(); //停止播放，同play
		Sprite *getSprite();
		bool isPlaying(); //是否正在播放，默认为false不播放
		double speedX; //x轴移动速度，单位为每帧移动的像素数
		double speedY; //y轴移动速度，单位为每帧移动的像素数
		double speedW; //宽度变化速度，单位为每帧变化的像素数
		double speedH; //高度变化速度，单位为每帧变化的像素数
		double speedAlpha; //透明度变化速度，单位为每帧变化的透明度数
		int currentFrame; //当前帧
		int speedBlt; //图块变化速度，单位为多少游戏帧执行一次动画帧，平均一帧约为5毫秒
		int bltDirection; //图块变化种类，2468为对应变化方向
		virtual void onUpdate();
	};
}