#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  576

// Define the mighty cow as something drawable @ some x,y-coordinate:
typedef struct _koe_ {
	int x;
	int y;
	int cow_colors[3];
} koe;

// Predefining all functions
void create_playable_environment();
void recreate_playable_environment();
void unleash_the_beast(koe *koetje);
void check_init_sdl();
void make_check_window();
void make_check_render();
void process_input(koe *koetje);
void proper_shutdown(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	// We are going to check if SDL is initialised
	check_init_sdl();

	// We are going to make a window and check if it is working
	make_check_window();

	// We are going to make the rendering and check if it is working
	make_check_render();

	// Create our playable cow named Greta 	
	koe greta = {(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), {135, 54, 0}};

	struct _koe_ all_me_cows[10];

	for (int i = 0; i < 10; i++) 
	{

		int x = rand() % SCREEN_WIDTH;	
		int y = rand() % SCREEN_HEIGHT;
		int color_r = rand() % 255;
		int color_g = rand() % 255;
		int color_b = rand() % 255;
		
		koe cow_duplicate = {x, y, {color_r, color_g, color_b}};
		all_me_cows[i] = cow_duplicate;
	
	}

	while (1)
	{
		// Step 1 render the cow environment (grass)
		create_playable_environment();

		// Step 2 Show all the other cows
		for (int i = 0; i < 10; i++) 
		{

			struct _koe_ the_one_cow = all_me_cows[i];
			unleash_the_beast(&the_one_cow);

		}

		// Step 3 Make sure Greta can move
		process_input(&greta);

		// Step 4 Show Greta
		unleash_the_beast(&greta);

		// Step 5 Rerender the cow environment
		recreate_playable_environment();
	}

	return 0;
}

void create_playable_environment()
{
	// Refresh the backbuffer to its original state:
	// RGB (39, 174, 96) should be a green grass color
	SDL_SetRenderDrawColor(renderer, 39, 174, 96, 255);
	SDL_RenderClear(renderer);
}

void recreate_playable_environment()
{
	// Render redrawn scene to front buffer, showing it in the 
	// actual window:
	SDL_RenderPresent(renderer);
	// Remember ~ 60 FPS of smooth Greta movements - PC Master Race!
	SDL_Delay(16);
}

void unleash_the_beast(koe *koetje)
{
	// Update Greta's location based on the input data:
	SDL_Rect lijf = {koetje->x, koetje->y, 16, 16};
	SDL_Rect kop = {koetje->x + 4, koetje->y - 8, 8, 8};
	SDL_Rect staart = {koetje->x + 7, koetje->y + 16, 2, 2};
	SDL_Rect linkervoorpoot = {koetje->x - 3, koetje->y + 2, 3, 3};
	SDL_Rect rechtervoorpoot = {koetje->x + 16, koetje->y + 2, 3, 3};
	SDL_Rect linkerachterpoot = {koetje->x - 3, koetje->y + 12, 3, 3};
	SDL_Rect rechterachterpoot = {koetje->x + 16, koetje->y + 12, 3, 3};
				
	// RGB (135, 54, 0) should be a brown fur color for Greta
	SDL_SetRenderDrawColor(renderer, (Uint8)koetje->cow_colors[0], (Uint8)koetje->cow_colors[1], (Uint8)koetje->cow_colors[2], 255);

	// Redraw Grata in the backbuffer to her updated location:
	SDL_RenderFillRect(renderer, &lijf);
	SDL_RenderFillRect(renderer, &kop);
	SDL_RenderFillRect(renderer, &staart);
	SDL_RenderFillRect(renderer, &linkervoorpoot);
	SDL_RenderFillRect(renderer, &rechtervoorpoot);
	SDL_RenderFillRect(renderer, &linkerachterpoot);
	SDL_RenderFillRect(renderer, &rechterachterpoot);
}

void check_init_sdl()
{
	srand((uint8_t) time(0));
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
}

void make_check_window()
{
	unsigned int window_flags = 0;

	window = SDL_CreateWindow("All your grass belongs to Greta", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
		window_flags);
	if (window == NULL)
	{
		printf("Failed to create window -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
}

void make_check_render()
{
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;
	
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == NULL) // error handling:
	{
		printf("Failed to create renderer -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
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
