NAME		=	pipex

BONUS		=	pipex_bonus

SRC_PATH	=	src/

SRC_FILES	=	src/main.c \
			src/utils.c \
			src/exec.c \
			src/free.c \
			src/get_path.c \
			src/init.c \

BONUS_FILES	=	src/bonus/main_bonus.c \
			src/bonus/utils_bonus.c \
			src/bonus/exec_bonus.c \
			src/bonus/free_bonus.c \
			src/bonus/get_path_bonus.c \
			src/bonus/init_bonus.c \

LIBFT_PATH	=	libft/

LIBFT_LIB	=	libft/libft.a

INCLUDE_PATH	=	include/

SRC_OBJS	=	$(SRC_FILES:.c=.o)

BONUS_OBJS	=	$(BONUS_FILES:.c=.o)

LIBFT_OBJS	=	$(LIBFT_PATH)*.o

LIBFTMAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

CC		=	clang

CFLAGS		=	-Wall -Wextra -Werror -Iinclude

RM		=	rm -rf

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

all:			$(NAME)

bonus:			$(BONUS)

$(NAME):		$(SRC_OBJS)
				@$(LIBFTMAKE)
				@$(CC) $(CFLAGS) $(SRC_OBJS) $(LIBFT_LIB) -o $(NAME)
				@echo "$(NAME) created"

$(BONUS):		$(BONUS_OBJS)
				@$(LIBFTMAKE)
				@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_LIB) -o $(BONUS)
				@echo "$(BONUS) created"



clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(SRC_OBJS) $(BONUS_OBJS)
			@echo "pipex .o deleted"

fclean:			clean
				@$(RM) $(NAME) $(BONUS) $(LIBFT_LIB)
				@echo "libft.a deleted"
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:			all clean fclean re lmake bonus
