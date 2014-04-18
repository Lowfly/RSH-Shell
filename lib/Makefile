
NAME	=	libmy.a

CC	=	gcc

RM	=	rm -f

HEADER	=	my.h

CFLAGS	+=	-Wall -Wextra

CFLAGS	+=	-I inc

SRC	=	src/my_putstr.c \
		src/my_strlen.c \
		src/tab_len.c \
		src/my_putchar.c \
		src/my_strdup.c \
		src/my_str_to_wordtab.c \
		src/my_concat.c \
		src/my_strcat.c \
		src/my_strcmp.c \
	 	src/free_dtab.c \
	 	src/my_getnbr.c

OBJ	=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)
		cp inc/my.h ../inc/my.h
		ranlib $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
