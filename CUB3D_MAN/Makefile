NAME = cub3d
CC = cc

HEADER     =    cub3d.h
CFLAGS =  -fsanitize=address -g3 #-Wall -Wextra -Werror
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit


SRCS = main.c \
		init.c \
		./Parsing/get_next_line.c \
		./Parsing/get_next_line_utils.c \
		./Parsing/parse_color.c \
		./Parsing/parse_map.c \
		./Parsing/parse_texter.c \
		./Parsing/parsing.c \
		./Parsing/split.c \
		./Parsing/utils.c \
		./Parsing/utils2.c \
		

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
