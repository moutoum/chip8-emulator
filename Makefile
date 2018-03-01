NAME	=	chip8

SRC	=	src/main.cpp src/Chip8.cpp

CXXFLAGS =	-I./include \
		-W -Wall -Werror -Wextra \
		-g

CC	=	g++

LDFLAGS	=	-lsfml-graphics \
		-lsfml-window \
		-lsfml-system

OBJ	=	$(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: $(NAME) clean fclean re
