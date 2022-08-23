# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/05/04 10:58:28 by lwiedijk      #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2022/08/23 15:23:40 by mteerlin      ########   odam.nl          #
=======
#    Updated: 2022/08/19 15:16:04 by lwiedijk      ########   odam.nl          #
>>>>>>> 44cec2f9ee905b0b22e9c8369a5173da428565aa
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
<<<<<<< HEAD
SRCS		=	lexer/lexer2.c
=======
SRCS		=	lexer.c
>>>>>>> 44cec2f9ee905b0b22e9c8369a5173da428565aa
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
