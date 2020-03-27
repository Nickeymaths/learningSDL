#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#undef main

const int SCREEN_HIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init();
SDL_Texture* loadTexture(const std::string& path);
bool loadMedia();
void close();

SDL_Window* window = nullptr;
SDL_Texture* image = nullptr;
SDL_Renderer* screen = nullptr;

int main() {
	bool quit = false;
	SDL_Event e;
	if (init()) {
		if (loadMedia()) {
			while (!quit) {
				// Handle event
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				SDL_RenderClear(screen);
				SDL_RenderCopy(screen, image, nullptr, nullptr);
				SDL_RenderPresent(screen);
			}
		}
	}
	return 0;
}

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error init video" << std::endl;
		success = false;
	}
	else {
		window = SDL_CreateWindow("Pham Thanh Vinh",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cerr << "Error create window" << std::endl;
			success = false;
		}
		else {
			screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (screen == nullptr) {
				std::cerr << "Error init screen" << std::endl;
				success = false;
			}
			else {
				// set color
				SDL_SetRenderDrawColor(screen, 0xFF, 0xFF, 0xFF, 0xFF);
				if (!IMG_Init(IMG_INIT_PNG)) {
					std::cerr << "False to init IMG PNG" << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}
SDL_Texture* loadTexture(const std::string& path) {
	SDL_Texture* loadTexture = nullptr;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == nullptr) {
		std::cerr << "Error load Image" << std::endl;
	}
	else {
		loadTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
		if (loadTexture == nullptr) {
			std::cerr << "Error creat texture" << std::endl;
		}
		
		SDL_FreeSurface(loadSurface);
	}
	return loadTexture;
}
bool loadMedia() {
	bool success = true;
	image = loadTexture("Tank.png");
	if (image == nullptr) {
		std::cerr << "Erro load media" << std::endl;
		success = false;
	}
	return success;
}
void close() {
	SDL_DestroyTexture(image);
	image = nullptr;
	SDL_DestroyRenderer(screen);
	SDL_DestroyWindow(window);
	screen = nullptr;
	window = nullptr;
	IMG_Quit();
	SDL_Quit();
}