#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#include <stdio.h>
#include <iostream>

//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;


void logSDLError(std::ostream& os, const std::string& msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void clear(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	//SDL_RenderPresent(renderer);
}

void draw(SDL_Renderer* renderer, SDL_Rect* rect) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, rect);
	SDL_RenderPresent(renderer);
}

void drawdisparo(SDL_Renderer* renderer, SDL_Rect* disparo) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, disparo);
	SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {

	bool disparant = false;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
		"An SDL2 window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Rect rectangle;
	rectangle.x = 50;
	rectangle.y = 50;
	rectangle.w = 50;
	rectangle.h = 50;

	SDL_Rect disparo;
	disparo.x = 40;
	disparo.y = 10;
	disparo.w = 40;
	disparo.h = 10;

	clear(renderer);

	int quit = 0;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				// Handle arrow keys
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_LEFT:
					rectangle.x -= 20;
					break;
				case SDL_SCANCODE_RIGHT:
					rectangle.x += 20;
					break;
				case SDL_SCANCODE_UP:
					rectangle.y -= 20;
					break;
				case SDL_SCANCODE_DOWN:
					rectangle.y += 20;
					break;
				case SDL_SCANCODE_SPACE:
					disparant = true;

				default:
					break;
				}

			}
			
			
			
			else if (event.type == SDL_QUIT) {
				quit = 1;
				puts("QUIT!");
				break;
			}
		}
		if (disparant) {
			drawdisparo(renderer, &disparo);
			disparo.x++;
	
		}

		clear(renderer);
		draw(renderer, &rectangle);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;



	

}