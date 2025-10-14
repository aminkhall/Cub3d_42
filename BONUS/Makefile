NAME = cub3d_bonus
CC = cc

HEADER     =    cub3d_bonus.h
# CFLAGS =  -fsanitize=address -g3 #-Wall -Wextra -Werror
# MLXFLAGS = #-lmlx -framework OpenGL -framework AppKit
MLX_DIR = minilibx-linux
CFLAGS =  -I$(MLX_DIR) 
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = 	main_bonus.c \
		raysrendring.c\
		3dmap.c \
		minimap.c \
		init.c \
		door_mouse_bonus.c \
		animation_bonuc.c \
		./Parsing/get_next_line_bonus.c \
		./Parsing/get_next_line_utils_bonus.c \
		./Parsing/parse_color_bonus.c \
		./Parsing/parse_map_bonus.c \
		./Parsing/parse_texter_bonus.c \
		./Parsing/parsing_bonus.c \
		./Parsing/split_bonus.c \
		./Parsing/utils_bonus.c \
		./Parsing/utils2_bonus.c \
		./Parsing/utils3_bonus.c \
		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	 ${CC} $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
