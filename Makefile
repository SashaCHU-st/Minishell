NAME = minishell
FLAGS = -Wall -Wextra -Werror 
#-g -fsanitize=address
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

RL_FLAGS = -lreadline

SRCS = newmain.c \
		input_validation.c \
		split_func.c \
			
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	cc $(FLAGS) $(OBJS) $(LIBFT_LIB) $(RL_FLAGS) -o $(NAME)

$(LIBFT_LIB): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re