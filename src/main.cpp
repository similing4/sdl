#include "main.h"

using namespace Scene;
void global_errlog(const char *str){
    FILE* file;
    file = fopen("error.log", "a+");
    fwrite(str, sizeof(char), strlen(str), file);
    fclose(file);
}

int main(int argc, char *argv[]) {
	SDL_Renderer *MainRenderRend = NULL;
	SDL_Window *MainRenderWindow;
	SDL_Event event;
	SDL_Surface *surface = NULL;
	bool isExit = false;
 
	SDL_Init(SDL_INIT_EVERYTHING);
	MainRenderWindow = SDL_CreateWindow("TEST_SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(MainRenderWindow);
	MainRenderRend = SDL_CreateRenderer(MainRenderWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	BaseScene *scene = new MainScene(MainRenderRend, MainRenderWindow);

	while (!isExit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isExit = true;
			scene->onEvent(event);
		}
		SDL_RenderClear(MainRenderRend);
		scene->onUpdate();
		SDL_RenderPresent(MainRenderRend);
		SDL_Delay(5);
	}

	delete scene;
	SDL_DestroyWindow(MainRenderWindow);
	SDL_Quit();

	system("pause");
	return 0;
}