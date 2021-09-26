NAME		=	pipex

SRC_PATH	=	src/

SRC_FILES	=	src/main.c \
			src/utils.c \

LIBFT_PATH	=	libft/

LIBFT_LIB	=	libft/libft.a

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

LIBFT_OBJS	=	$(LIBFT_PATH)*.o

LIBFTMAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM		=	rm -rf

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

all:			$(NAME)

$(NAME):		$(SRC_OBJS)
				@$(LIBFTMAKE)
				@$(CC) $(SRC_OBJS) $(LIBFT_LIB) -o $(NAME)
				@echo "$(NAME) created"


clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(SRC_OBJS)
			@echo "pipex .o deleted"

fclean:			clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@echo "libft.a deleted"
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:			all clean fclean re lmake
