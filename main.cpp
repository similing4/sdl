// SDL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

extern "C" {
#include "SDL.h"
#include "SDL_image.h"
}
constexpr int RenderTextureMaxLength = 655360;
constexpr int SpriteMaxLength = 65536;
typedef struct {
    SDL_Texture* texture = NULL;
}Texture;
typedef struct {
    int zIndex;
    int textureListLen;
    int* textureList; //动画图片列表，需要malloc free
    int delay; //刷新频率（毫秒），即1000fps
    int currentTextureListIndex = 0; //当前播放帧
}Sprite;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
Sprite sprites[SpriteMaxLength]; //动画列表
bool sprites_pos[SpriteMaxLength] = { false }; //0.0625MB内存用于记录这块内存是否被使用
Texture render_texture[RenderTextureMaxLength]; //2.5MB内存可容纳655,360张图片
bool render_texture_pos[RenderTextureMaxLength] = { false }; //0.625MB内存用于记录这块内存是否被使用


int errorAndExit(const char* err) {
    SDL_DestroyWindow(win);
    std::cout << err << SDL_GetError() << std::endl;
    SDL_Quit();
    fclose(stdout);
    return 1;
}

int addTexture(const char* imagePath) {
    SDL_Surface* image = IMG_Load(imagePath);
    if (image == nullptr) {
        std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, image);
    SDL_FreeSurface(image);
    for (int i = 0; i < RenderTextureMaxLength; i++) {
        if (!render_texture_pos[i]) {
            render_texture[i].texture = tex;
            render_texture_pos[i] = true;
            return i;
        }
    }
    SDL_DestroyTexture(tex);
    return -1;
}

int addSprite(const char* imagePath) {

}

bool deleteTexture(int index) {
    if (render_texture_pos[index]) {
        SDL_DestroyTexture(render_texture[index].texture);
        render_texture[index].texture = NULL;
        render_texture_pos[index] = false;
    }
}

bool deleteSprite(int index) {
    if (sprites_pos[index]) {
        for (int i = 0; i < sprites[index].textureListLen; i++)
            deleteTexture(sprites[index].textureList[i]);
        free(sprites[index].textureList);
        sprites[index].textureListLen = 0;
        sprites_pos[index] = false;
    }
}

void cleanTextureAndSprite() {
    for (int i = 0; i < SpriteMaxLength; i++)
        deleteSprite(i);
    for (int i = 0; i < RenderTextureMaxLength; i++)
        deleteTexture(i);
}

int main(int argc, char* argv[]) {
    FILE* rf = freopen("stdout.log", "w", stdout);
    if (SDL_Init(SDL_INIT_VIDEO))
        return errorAndExit("SDL_Init Error: ");
    win = SDL_CreateWindow("魔塔", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 17 * 32, 11 * 32, SDL_WINDOW_SHOWN);
    if (win == nullptr)
        return errorAndExit("SDL_CreateWindow Error: ");
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
        return errorAndExit("SDL_CreateRender Error: ");


    for (int i = 0; i < 3; ++i) {
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
    }

    cleanTextureAndSprite();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    fclose(stdout);
    return 0;
}