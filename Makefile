# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/21 12:25:06 by mteerlin      #+#    #+#                  #
#    Updated: 2022/09/27 14:03:58 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

VPATH	=	$(shell find src -type d) $(shell find libft -type d)
SRC		:= src/main.c \
src/error/error.c \
src/lexer/charchecks.c \
src/lexer/fsm_op.c \
src/lexer/fsm_op2.c \
src/lexer/lexer.c \
src/lexer/stx_error.c \
src/parcer/parcer.c \
src/parcer/separate.c \
src/parcer/separation_utils.c \
src/tests/tests.c \
src/utils/filelst_utils.c \
src/utils/token_section_utils.c \
src/utils/token_utils.c \
src/utils/token_utils2.c    

OBJ_DIR := 	obj/
OBJ		= 	$(addprefix $(OBJ_DIR), $(SRC:src/%.c=%.o))

LIBFT_DIR := $(INCL_DIR)libft/
LIBFT	:= $(LIBFT_DIR)libft.a

AR		?= ar rcs;
SANFLAGS ?= -fsanitize=address -g
CFLAGS	?= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@echo $(HDR)
			@echo "Compiling minishell."
			@$(CC) $(CFLAGS) -lreadline $(LIBFT) $(OBJ) -o $(NAME)
#			@$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJ) -lft -o $(NAME)
			@echo "Compilation finished."

$(LIBFT):
			@echo "Making library libft."
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) bonus

$(OBJ_DIR)%.o:		%.c $(HDR_DIR)$(HDR)
			@echo creating object files.
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@

test:		
			@echo $(VPATH)
			@echo " "
			@echo $(SRC)
			@echo " "
			@echo $(OBJ)
			@echo " "
			@echo $(HDR)

clean:
			@echo "Removing object files"
			@rm -rf $(OBJ_DIR) $(LIBFT_DIR)*.o

fclean:
			@$(MAKE) --no-print-directory clean
			@echo "Removing excecutables"
			@rm -f $(NAME) $(LIBFT)
re:
			@$(MAKE) --no-print-directory fclean
			@$(MAKE) --no-print-directory all

.PHONY:		all, clean, fclean, re, test;
