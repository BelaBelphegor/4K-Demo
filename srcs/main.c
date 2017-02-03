#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <fcntl.h>
#include <unistd.h>

void	SDL_PutPixel(SDL_Texture *texture, int x, int y, int color)
{
	int					pitch;
	void				*pixels;
	(void)color;
	(void)x;
	(void)y;	
	
	SDL_Color	ucolor;
	ucolor.r = 0;
	ucolor.b = 80;
	ucolor.g = 0;
	if (SDL_LockTexture(texture, NULL, &pixels, &pitch) < 0)
	{
		dprintf(2, "Error: %s\n", SDL_GetError());
		return ;
	}
	*(uint32_t *)((uint8_t *)600 * 4 * y) + x * 4 = 0x00FF0000;
//	*(uint8_t *)(pixels + y * 600 * 4 + x) = 240;
	
	/**(dst + x) = (color >> 16) & 0xFF;
	*(dst + x + 1) = (color >> 8) & 0xFF;
	*(dst + x + 2) = (color) & 0xFF;*/
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
	 ** Main code.
	 */
	i = -1;
	j = -1;
	renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (-1);
	pwindow = SDL_CreateWindow("4k-demo", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		return (-1);
	 texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

	keystate = NULL;
	keystate = (Uint8 *)SDL_GetKeyboardState(NULL);
	quit = 1;
	memset(pixels, 255, 800 * 600 * sizeof(unsigned int));	
		SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(unsigned int));		
	while (j = 0, ++i < 800)
			while (++j < 600)
				SDL_PutPixel(texture, i, j, 0);	
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
