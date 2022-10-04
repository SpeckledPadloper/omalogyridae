# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lwiedijk <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/05/04 10:58:28 by lwiedijk      #+#    #+#                  #
#    Updated: 2022/09/19 15:05:18 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include sources.mk

NAME		=	minishell
OBJS_DIR	=	objs/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
HEADERS		=	src/lexer/hdr/lexer.h,		\
				src/lexer/hdr/charchecks.h,	\
				src/lexer/hdr/fsm.h
CFLAGS		=	-g

LIBFT_DIR	=	libft/
LIBFT		=	$(addprefix $(LIBFT_DIR), libft.a)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(VPATH) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

test:
	@echo $(VPATH)

clean:
	$(RM) $(OBJS)
	make fclean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
