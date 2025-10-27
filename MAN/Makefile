NAME = cub3d
CC = cc

HEADER 	=	cub3d.h
MLX_DIR = minilibx-linux

CFLAGS =  -I$(MLX_DIR)   -Wall -Wextra -Werror
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm


SRCS = main.c \
		init.c \
		rays.c \
		3dmap.c \
		player.c \
		utils.c \
		./Parsing/get_next_line.c \
		./Parsing/get_next_line_utils.c \
		./Parsing/parse_color.c \
		./Parsing/parse_map.c \
		./Parsing/parse_texter.c \
		./Parsing/parsing.c \
		./Parsing/split.c \
		./Parsing/utils.c \
		./Parsing/utils2.c \
		./Parsing/utils3.c \
		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	 ${CC} $(CFLAGS)  -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
