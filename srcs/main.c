#include <SDL2/SDL.h>
// #include <SDL_mixer.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "metaball.h"

#define WINDW_W 1200
#define WINDW_H 800

static int random_min_max(int min, int max)
{
	return min + rand() % (max + 1 - min);
}

void	SDL_PutPixel(SDL_Texture *texture, int x, int y, int color)
{
	int					pitch;
	uint32_t			*pixels;
	uint32_t			position;
	(void)color;
	(void)x;
	(void)y;	

	SDL_Color	ucolor;
	ucolor.r = 0;
	ucolor.b = 80;
	ucolor.g = 0;
	if (SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch) < 0)
	{
		dprintf(2, "Error: %s\n", SDL_GetError());
		return ;
	}	
	position = y * (pitch / sizeof(unsigned int)) + x;
	pixels[position] = color;
	SDL_UnlockTexture(texture);
}

int		main(void)
{
	/*
	 ** SDL Initialisation and window handling variables.
	 */
	SDL_Window		*pwindow;
	SDL_Renderer	*renderer;
	SDL_Event		e;
	Uint8			*keystate;
	int				quit;

	/*
	 ** Rendering variables
	 */
	unsigned int	*pixels;
	SDL_Texture 	*texture;
	int				i;
	int				j;

	/*
	 ** Metaballs variables
	 */
	const int			MAX_METABALLS = 8;
	t_metaball			*ball_list[MAX_METABALLS];
	const float			MIN_THRESHOLD = 0.98f;
	const float			MAX_THRESHOLD = 1.01f;
	float				sum;
	int					metaball_iterator;

	/*
	 ** Timestamp for framerate. Need rework.
	 */
	unsigned int	current_time;
	unsigned int	elapsed_time;
	int				delta;
	/*
	 ** Main code.
	 */
	i = -1;
	j = -1;
	pixels = NULL;
	renderer = NULL;
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (-1);
	pwindow = SDL_CreateWindow("4K-demo", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDW_W, WINDW_H, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		return (-1);
	texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDW_W, WINDW_H);
	keystate = NULL;
	keystate = (Uint8 *)SDL_GetKeyboardState(NULL);
	quit = 1;
	metaball_iterator = -1;
	srand(time(NULL));
	while (++metaball_iterator < MAX_METABALLS)
	{
		ball_list[metaball_iterator] = (t_metaball *)malloc(sizeof(t_metaball) + 1);
		metaball_init(ball_list[metaball_iterator], random_min_max(0, WINDW_W), random_min_max(0, WINDW_H), random_min_max(10, 50), -1, 1, random_min_max(1, 2));
	}
	current_time = 0;
	elapsed_time = SDL_GetTicks();
	pixels = (unsigned int *)malloc(WINDW_H * WINDW_W * sizeof(unsigned int));
	while (quit)
	{
		current_time = SDL_GetTicks();
		delta = current_time - elapsed_time;
		elapsed_time = current_time;
		if (delta < (1000 / 60))
			SDL_Delay((1000 / 60) - delta);
		i = -1;
		memset(pixels, 0, WINDW_W * WINDW_H * sizeof(unsigned int));	
		SDL_UpdateTexture(texture, NULL, pixels, WINDW_W * sizeof(unsigned int));
		while (j = -1, ++i < WINDW_H)
			while (++j < WINDW_W)
			{
				sum = 0;
				metaball_iterator = -1;
				while (++metaball_iterator < MAX_METABALLS)
				{
					sum += metaball_equation(ball_list[metaball_iterator], j, i);
					if (sum >= MIN_THRESHOLD && sum <= MAX_THRESHOLD)
						SDL_PutPixel(texture, j, i, ball_list[metaball_iterator]->_color);
				}
			}
		metaball_iterator = -1;
		while (++metaball_iterator < MAX_METABALLS)
		{
			if ((ball_list[metaball_iterator]->_x + ball_list[metaball_iterator]->_radius) >= WINDW_W - ball_list[metaball_iterator]->_radius || ball_list[metaball_iterator]->_x <= 0 + ball_list[metaball_iterator]->_radius)
				ball_list[metaball_iterator]->_dir_x *= -1;
			if (ball_list[metaball_iterator]->_y + ball_list[metaball_iterator]->_radius >= WINDW_H - ball_list[metaball_iterator]->_radius || ball_list[metaball_iterator]->_y <= 0 + ball_list[metaball_iterator]->_radius)
				ball_list[metaball_iterator]->_dir_y *= -1;
			ball_list[metaball_iterator]->_x += ball_list[metaball_iterator]->_dir_x * ball_list[metaball_iterator]->_speed * (delta / 16);
			ball_list[metaball_iterator]->_y += ball_list[metaball_iterator]->_dir_y * ball_list[metaball_iterator]->_speed * (delta / 16);
		}
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 0;
		}	
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		(void)pixels;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(pwindow);
}
