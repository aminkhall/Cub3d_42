NAME 	=	cub
CC 		=	cc

HEADER 	=	cub.h

CFLAGS 	= 	-Wall -Wextra -Werror

SRC 	=	get_next_line.c \
			get_next_line_utils.c \
			parse_color.c \
			parse_map.c \
			parse_texter.c \
			parsing.c \
			split.c \
			utils.c \

OBJ 	= 	${SRC:.c=.o}

all: ${NAME}


${NAME} : ${OBJ}
	 ${CC} ${OBJ} $(CFLAGS) -o ${NAME} 

%.o : %.c $(HEADER)
	 ${CC}  -c $< -o $@
	
clean :
	@rm -f ${OBJ}

re: fclean all

fclean : clean
	@rm -f ${NAME}
	
.PHONY: all clean fclean re