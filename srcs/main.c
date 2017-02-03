#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "metaball.h"

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
	unsigned int	pixels[800 * 600];
	SDL_Texture 	*texture;
  	int				i;
	int				j;

	/*
	 ** Metaballs variables
	 */
	const int			MAX_METABALLS = 15;
	t_metaball			*ball_list[MAX_METABALLS];
	const float			MIN_THRESHOLD = 0.99f;
	const float			MAX_THRESHOLD = 1.01f;
	float				sum;
	int					metaball_iterator;
	/*
	 ** Main code.
	 */
	i = -1;
	j = -1;
	renderer = NULL;
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (-1);
	pwindow = SDL_CreateWindow("4K-demo", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		return (-1);
	 texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

	keystate = NULL;
	keystate = (Uint8 *)SDL_GetKeyboardState(NULL);
	quit = 1;
//	memset(pixels, 255, 800 * 600 * sizeof(unsigned int));	
//	SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(unsigned int));
	metaball_iterator = -1;
	while (++metaball_iterator < MAX_METABALLS)
	{
		ball_list[metaball_iterator] = (t_metaball *)malloc(sizeof(t_metaball) + 1);
		metaball_init(ball_list[metaball_iterator], rand() % 800, rand() % 600, 1 + rand() % 40);
	}
	while (j = -1, ++i < 800)
			while (++j < 600)
			{
				sum = 0;
				metaball_iterator = -1;
				while (++metaball_iterator < MAX_METABALLS)
				{
					sum += metaball_equation(ball_list[metaball_iterator], j, i);
					if (sum >= MIN_THRESHOLD && sum <= MAX_THRESHOLD)
						SDL_PutPixel(texture, i, j, 0x00FFFF00);

				}
			}
	while (quit)
	{
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
