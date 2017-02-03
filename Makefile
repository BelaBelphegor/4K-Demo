NAME				= 4k-demo
SRCS				= main.c
SRCSPATH			= ./srcs/
INCLUDES			= ./includes
CC					= clang
CFLAGS				= -fomit-frame-pointer -Os -Wall -Wextra -Werror
SDL2				= -framework SDL2
SDL2_MIXER			= -framework SDL2_mixer
SDL2_HEADER 		= -I ~/Library/Frameworks/SDL2.framework/Headers
SDL2_HEADER_MIXER	= -I ~/Library/Frameworks/SDL2_mixer.framework/Headers
SDL					= -F ~/Library/Frameworks $(SDL2_MIXER) $(SDL2)
SDL_HEADER			= -F ~/Library/Frameworks $(SDL2_HEADER_MIXER) $(SDL2_HEADER)
INCLUDES_O			= -I $(INCLUDES) -I ./libft/includes
INCLUDES_C			=  $(CFLAGS) $(SDL) $(SDL_HEADER) $(LFLAGS)
SRC					= $(addprefix $(SRCSPATH), $(SRCS))
OBJS				= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES_C) 

%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) $(SDL_HEADER) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

sdl_install:
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/

.PHONY: all clean fclean re
