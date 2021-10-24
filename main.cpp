// SDL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

extern "C" {
#include "SDL.h"
#include "SDL_image.h"
}
constexpr int RenderTextureMaxLength = 655360;
constexpr int SpriteMaxLength = 65536;
struct Texture {
    SDL_Texture* texture = NULL;
    int w;
    int h;
};
struct Sprite {
    int zIndex;
    int x;
    int y;
    int w;
    int h;
    int xd = 1; //横向分割1个
    int yd = 1; //纵向分割1个
    int textureIndex; //对应的纹理
    int currentPlayIndex = 0; //当前播放帧(从左到右从上到下)
};

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
Sprite sprites[SpriteMaxLength]; //精灵
bool sprites_pos[SpriteMaxLength] = { false }; //精灵是否被使用
Texture render_texture[RenderTextureMaxLength]; //图片
bool render_texture_pos[RenderTextureMaxLength] = { false }; //图片是否被使用


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
    int w = image->w;
    int h = image->h;
    SDL_FreeSurface(image);
    for (int i = 0; i < RenderTextureMaxLength; i++) {
        if (!render_texture_pos[i]) {
            render_texture[i].texture = tex;
            render_texture[i].w = w;
            render_texture[i].h = h;
            render_texture_pos[i] = true;
            return i;
        }
    }
    SDL_DestroyTexture(tex);
    return -1;
}

void deleteTexture(int index) {
    if (render_texture_pos[index]) {
        SDL_DestroyTexture(render_texture[index].texture);
        render_texture[index].texture = NULL;
        render_texture_pos[index] = false;
    }
}

int addSprite(const char* imagePath, int x, int y, int w, int h, int xd, int yd, int zIndex, int currentPlayIndex) {
    int ret = addTexture(imagePath);
    if (ret == -1)
        return -1;
    for (int i = 0; i < SpriteMaxLength; i++) {
        if (!sprites_pos[i]) {
            sprites[i].textureIndex = ret;
            sprites[i].xd = xd;
            sprites[i].yd = yd;
            sprites[i].zIndex = zIndex;
            sprites[i].currentPlayIndex = currentPlayIndex;
            sprites_pos[i] = true;
            return i;
        }
    }
    deleteTexture(ret);
    return -1;
}

void deleteSprite(int index) {
    if (sprites_pos[index]) {
        sprites_pos[index] = false;
        deleteTexture(sprites[index].textureIndex);
    }
}

void cleanTextureAndSprite() {
    for (int i = 0; i < SpriteMaxLength; i++)
        deleteSprite(i);
    for (int i = 0; i < RenderTextureMaxLength; i++)
        deleteTexture(i);
}

int main(int argc, char* argv[]) {
    FILE* rf;
    freopen_s(&rf, "stdout.log", "w", stdout);
    if (SDL_Init(SDL_INIT_VIDEO))
        return errorAndExit("SDL_Init Error: ");
    win = SDL_CreateWindow("Mota", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 17 * 32, 11 * 32, SDL_WINDOW_SHOWN);
    if (win == nullptr)
        return errorAndExit("SDL_CreateWindow Error: ");
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
        return errorAndExit("SDL_CreateRender Error: ");

    SDL_Rect sourceRect;
    SDL_Rect destRect;
    while(true) {
        SDL_RenderClear(ren);
        for (int i = 0; i < SpriteMaxLength; i++)
            if (sprites_pos[i]) {
                sourceRect.w = (render_texture[sprites[i].textureIndex].w / sprites[i].xd);
                sourceRect.h = (render_texture[sprites[i].textureIndex].h / sprites[i].yd);
                sourceRect.x = (sprites[i].currentPlayIndex % sprites[i].xd) * sourceRect.w;
                sourceRect.y = (sprites[i].currentPlayIndex / sprites[i].xd) * sourceRect.h;
                destRect.x = sprites[i].x;
                destRect.y = sprites[i].y;
                destRect.w = sprites[i].w;
                destRect.h = sprites[i].h;
                SDL_RenderCopy(ren, render_texture[sprites[i].textureIndex].texture, &sourceRect, &destRect);
            }
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