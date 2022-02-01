#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  576

// Define the mighty cow as something drawable @ some x,y-coordinate:
typedef struct _koe_ {
	int x;
	int y;
} koe;

void process_input(koe *koetje);
void proper_shutdown(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	// Spawn Greta in the middle of the window:
	koe greta = {(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)};
	
	unsigned int window_flags = 0;
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("All your grass are belong to Greta", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
		window_flags);
	if (window == NULL)
	{
		printf("Failed to create window -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
	
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == NULL) // error handling:
	{
		printf("Failed to create renderer -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
	
	while (1)
	{
		// Refresh the backbuffer to its original state:
		// RGB (39, 174, 96) should be a green grass color
		SDL_SetRenderDrawColor(renderer, 39, 174, 96, 255);
		SDL_RenderClear(renderer);
		// Process selected inputs and pay close attention to moving
		// our freshly spawned cow:
		process_input(&greta);
		
		// Update Greta's location based on the input data:
		SDL_Rect lijf = {greta.x, greta.y, 16, 16};
		SDL_Rect kop = {greta.x + 4, greta.y - 8, 8, 8};
		SDL_Rect staart = {greta.x + 7, greta.y + 16, 2, 2};
		SDL_Rect linkervoorpoot = {greta.x - 3, greta.y + 2, 3, 3};
		SDL_Rect rechtervoorpoot = {greta.x + 16, greta.y + 2, 3, 3};
		SDL_Rect linkerachterpoot = {greta.x - 3, greta.y + 12, 3, 3};
		SDL_Rect rechterachterpoot = {greta.x + 16, greta.y + 12, 3, 3};
				
		// RGB (135, 54, 0) should be a brown fur color for Greta
		SDL_SetRenderDrawColor(renderer, 135, 54, 0, 255);
		// Redraw Grata in the backbuffer to her updated location:
		SDL_RenderFillRect(renderer, &lijf);
		SDL_RenderFillRect(renderer, &kop);
		SDL_RenderFillRect(renderer, &staart);
		SDL_RenderFillRect(renderer, &linkervoorpoot);
		SDL_RenderFillRect(renderer, &rechtervoorpoot);
		SDL_RenderFillRect(renderer, &linkerachterpoot);
		SDL_RenderFillRect(renderer, &rechterachterpoot);
		
		// Render redrawn scene to front buffer, showing it in the 
		// actual window:
		SDL_RenderPresent(renderer);
		// Remember ~ 60 FPS of smooth Greta movements - PC Master Race!
		SDL_Delay(16);
	}

	return 0;
}

void process_input(koe *koetje)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				proper_shutdown();
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						proper_shutdown();
						exit(0);
						break;
					case SDL_SCANCODE_RIGHT:
						koetje->x += 4;
						break;
					case SDL_SCANCODE_LEFT:
						koetje->x -= 4;
						break;
					case SDL_SCANCODE_UP:
						koetje->y -= 4;
						break;
					case SDL_SCANCODE_DOWN:
						koetje->y += 4;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void proper_shutdown(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
