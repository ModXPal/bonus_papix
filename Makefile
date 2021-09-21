NAME		=	pipex

SRC_PATH	=	src/

SRC_FILES	=	src/main.c \
			src/utils.c \

LIBFT_PATH	=	libft/

LIBFT_LIB	=	libft.a

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

LIBFT_OBJS	=	$(LIBFT_PATH)*.o

LIBFTMAKE	=	$(MAKE) -C $(LIBFT_PATH) bonus

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM		=	rm -rf

all:			$(NAME)

$(NAME):		$(SRC_OBJS) lmake
				$(CC) $(SRC_OBJS) $(LIBFT_OBJS) -o $(NAME)

lmake:			
			$(LIBFTMAKE)

clean:			
			make -C $(LIBFT_PATH) clean
			$(RM) $(SRC_OBJS)

fclean:			clean
				$(RM) $(NAME) $(LIBFT_PATH)$(LIBFT_LIB)

re:			fclean all

.PHONY:			all clean fclean re lmake
