#include "Utils/Animation.h"

namespace Utils {
	Animation::Animation(Sprite* sprite, int playDirection, int playColumn, int colCount, int rowCount){
		this->fp = 0;
		this->sprite = sprite;
		if(colCount < 1)
			colCount = 1;
		if(rowCount < 1)
			rowCount = 1;
		if(playDirection != 2 && playDirection != 4 && playDirection != 6 && playDirection != 8)
			playDirection = 6;
		this->isBlt = (rowCount > 1 || colCount > 1);
		this->sprite->setBltEnabled(this->isBlt);
		this->bltRectWidth = sprite->getTextureWidth() / colCount;
		this->bltRectHeight = sprite->getTextureHeight() / rowCount;
		this->colCount = colCount;
		this->rowCount = rowCount;
		this->currentFrame = 0;
		if(playDirection == 4 || playDirection == 6)
			this->frameCount = colCount;
		else
			this->frameCount = rowCount;
		this->bltDirection = playDirection;
		this->bltPlayColumn = playColumn;
		this->_isPlaying = false;
		this->onAlphaEgt = NULL;
		this->onAlphaElt = NULL;
		this->onXEgt = NULL;
		this->onXElt = NULL;
		this->onYEgt = NULL;
		this->onYElt = NULL;
		this->onPlayFinish = NULL;
	}
	Animation::~Animation(){
		;
	}
	//播放，frame表示从第几帧开始播放，-1表示从当前帧开始播放，只影响帧播放，不影响区域变化
	void Animation::play(int frame){
		this->_isPlaying = true;
		if(frame == -1)
			return;
		this->currentFrame = frame;
	}
	//停止播放，同play
	void Animation::stop(){
		this->_isPlaying = false;
	}
	//是否正在播放，默认为false不播放
	bool Animation::isPlaying(){
		return this->_isPlaying;
	}
	void Animation::onUpdate(){
		this->fp ++;
		if(this->_isPlaying){
			this->sprite->setBltW(this->bltRectWidth);
			this->sprite->setBltH(this->bltRectHeight);
			if(this->speedBlt < 0)
				this->speedBlt = - this->speedBlt;
			if(this->speedBlt != 0){
				if(this->bltDirection == 4){
					this->sprite->setBltRect(this->currentFrame * this->bltRectWidth, this->bltPlayColumn * this->bltRectHeight, this->bltRectWidth, this->bltRectHeight);
					if(this->fp % this->speedBlt == 0)
						this->currentFrame --;
					if(this->currentFrame < 0)
						this->currentFrame = this->colCount - 1;
					this->currentFrame %= colCount;
				}else if(this->bltDirection == 6){
					this->sprite->setBltRect(this->currentFrame * this->bltRectWidth, this->bltPlayColumn * this->bltRectHeight, this->bltRectWidth, this->bltRectHeight);
					if(this->fp % this->speedBlt == 0)
						this->currentFrame ++;
					if(this->currentFrame > this->colCount - 1)
						this->currentFrame = 0;
					this->currentFrame %= colCount;
				}else if(this->bltDirection == 2){
					this->sprite->setBltRect(this->bltPlayColumn * this->bltRectWidth, this->currentFrame * this->bltRectHeight, this->bltRectWidth, this->bltRectHeight);
					if(this->fp % this->speedBlt == 0)
						this->currentFrame ++;
					if(this->currentFrame > this->rowCount - 1)
						this->currentFrame = 0;
					this->currentFrame %= rowCount;
				}else if(this->bltDirection == 8){
					this->sprite->setBltRect(this->bltPlayColumn * this->bltRectWidth, this->currentFrame * this->bltRectHeight, this->bltRectWidth, this->bltRectHeight);
					if(this->fp % this->speedBlt == 0)
						this->currentFrame ++;
					if(this->currentFrame > this->rowCount - 1)
						this->currentFrame = 0;
					this->currentFrame %= rowCount;
				}
			}
		}
		this->sprite->onUpdate();
		this->callEventListener();
		this->sprite->setX(this->sprite->getX() + this->speedX);
		this->sprite->setY(this->sprite->getY() + this->speedY);
		this->sprite->setW(this->sprite->getW() + this->speedW);
		this->sprite->setH(this->sprite->getH() + this->speedW);
		this->sprite->setAlpha(this->sprite->getAlpha() + this->speedAlpha);
	}
	Sprite *Animation::getSprite(){
		return this->sprite;
	}
	/*
	class 
	{
	private:
		Sprite *sprite;
		bool isBlt; //是否是需要分割的图块
		int bltRectWidth; //分割每个图块宽度，通过colCount计算获得
		int bltRectHeight; //分割每个图块高度，通过rowCount计算获得
		int rowCount; //行数
		int colCount; //列数
		int frameCount; //总帧数
		int currentFrame; //当前帧
		int bltDirection; //图块变化方向，2468为对应变化方向
		bool _isPlaying; //是否播放中
	public:
		double speedX; //x轴移动速度，单位为每帧移动的像素数
		double speedY; //y轴移动速度，单位为每帧移动的像素数
		double speedW; //宽度变化速度，单位为每帧变化的像素数
		double speedH; //高度变化速度，单位为每帧变化的像素数
		double speedAlpha; //透明度变化速度，单位为每帧变化的透明度数
		int speedBlt; //图块变化速度，单位为多少游戏帧执行一次动画帧，平均一帧约为5毫秒
	};*/

	void Animation::setOnAlphaEgtEventListener(function<void()> event, int dest){
		this->onAlphaEgt = event;
		this->alphaEgtEventDest = dest;
	}
	void Animation::setOnAlphaEltEventListener(function<void()> event, int dest){
		this->onAlphaElt = event;
		this->alphaEltEventDest = dest;
	}
	void Animation::setOnXEgtEventListener(function<void()> event, int dest){
		this->onXEgt = event;
		this->xEgtEventDest = dest;
	}
	void Animation::setOnXEltEventListener(function<void()> event, int dest){
		this->onXElt = event;
		this->xEltEventDest = dest;
	}
	void Animation::setOnYEgtEventListener(function<void()> event, int dest){
		this->onYEgt = event;
		this->yEgtEventDest = dest;
	}
	void Animation::setOnYEltEventListener(function<void()> event, int dest){
		this->onYElt = event;
		this->yEltEventDest = dest;
	}
	void Animation::setOnPlayFinishEventListener(function<void()> event){
		this->onPlayFinish = event;
	}
	void Animation::callEventListener(){
		if(this->onAlphaEgt != NULL && this->sprite->getAlpha() >= this->alphaEgtEventDest){
			this->onAlphaEgt();
			this->onAlphaEgt = NULL;
		}
		if(this->onAlphaElt != NULL && this->sprite->getAlpha() <= this->alphaEltEventDest){
			this->onAlphaElt();
			this->onAlphaElt = NULL;
		}
		if(this->onXEgt != NULL && this->sprite->getX() >= this->xEgtEventDest){
			this->onXEgt();
			this->onXEgt = NULL;
		}
		if(this->onXElt != NULL && this->sprite->getX() <= this->xEltEventDest){
			this->onXElt();
			this->onXElt = NULL;
		}
		if(this->onYEgt != NULL && this->sprite->getY() >= this->yEgtEventDest){
			this->onYEgt();
			this->onYEgt = NULL;
		}
		if(this->onYElt != NULL && this->sprite->getY() <= this->yEltEventDest){
			this->onYElt();
			this->onYElt = NULL;
		}
		if(this->onPlayFinish != NULL && this->_isPlaying && this->speedBlt > 0){
			if(this->bltDirection == 4 && this->currentFrame == 0){
				this->onPlayFinish();
				this->onPlayFinish = NULL;
			}
			if(this->bltDirection == 6 && this->currentFrame == this->colCount - 1){
				this->onPlayFinish();
				this->onPlayFinish = NULL;
			}
			if(this->bltDirection == 2 && this->currentFrame == 0){
				this->onPlayFinish();
				this->onPlayFinish = NULL;
			}
			if(this->bltDirection == 8 && this->currentFrame == this->rowCount - 1){
				this->onPlayFinish();
				this->onPlayFinish = NULL;
			}
		}
	}
}