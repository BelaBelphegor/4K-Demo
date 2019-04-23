NAME				= 4k-demo
SRCS				= main.c \
					  metaball.c 
SRCSPATH			= ./srcs/
INCLUDES			= ./includes
CC					= clang
CFLAGS				= -fomit-frame-pointer -Os
INCLUDES_O			= -I $(INCLUDES) -I ./libft/includes -I ~/.brew/Cellar/sdl2/2.0.9/include/
INCLUDES_C			=  $(CFLAGS) $(SDL) $(SDL_HEADER) $(LFLAGS) -L ~/.brew/Cellar/sdl2/2.0.9/lib/ -l SDL2-2.0.0
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
