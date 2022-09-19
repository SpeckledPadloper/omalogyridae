# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/05/04 10:58:28 by lwiedijk      #+#    #+#                  #
#    Updated: 2022/09/19 11:37:57 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	executer.c path_builder.c error_handling.c executer_utils.c heredoc_handling.c
OBJS_DIR	=	objs/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
CFLAGS		=	-g

LIBFT_DIR	=	libft/
LIBFT		=	$(addprefix $(LIBFT_DIR), libft.a)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	make fclean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
