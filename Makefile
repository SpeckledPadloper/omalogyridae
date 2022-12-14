# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/21 12:25:06 by mteerlin      #+#    #+#                  #
#    Updated: 2022/11/11 11:44:30 by lwiedijk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

VPATH	=	$(shell find src -type d) $(shell find libft -type d)
SRC		:= src/builtins/cd_update_pwd.c \
src/builtins/env_utils.c \
src/builtins/export_utils.c \
src/builtins/new_padloper_env.c \
src/builtins/padloper_cd.c \
src/builtins/padloper_echo.c \
src/builtins/padloper_env.c \
src/builtins/padloper_exit.c \
src/builtins/padloper_export.c \
src/builtins/padloper_pwd.c \
src/builtins/padloper_unset.c \
src/error/error.c \
src/executer/error_handling.c \
src/executer/executer.c \
src/executer/executer_utils.c \
src/executer/file_handling_builtin.c \
src/executer/file_handling_open.c \
src/executer/file_handling_rdir_close.c \
src/executer/heredoc_handling.c \
src/executer/init_metadata.c \
src/executer/path_builder.c \
src/lexer/charchecks.c \
src/lexer/fsm_op.c \
src/lexer/fsm_op2.c \
src/lexer/lexer.c \
src/lexer/stx_error.c \
src/main.c \
src/parcer/expand.c \
src/parcer/expand2.c \
src/parcer/parcer.c \
src/parcer/separate.c \
src/parcer/separation_utils.c \
src/parcer/simple_cmd.c \
src/parcer/stitching.c \
src/signals/signals.c \
src/utils/filelst_utils.c \
src/utils/line_navigation.c \
src/utils/simple_cmd_utils.c \
src/utils/token_section_utils.c \
src/utils/token_section_utils2.c \
src/utils/token_utils.c \
src/utils/token_utils2.c

HDR		:= src/error/error.h \
src/executer/hdr/executer.h \
src/hdr/minishell.h \
src/hdr/ms_enums.h \
src/hdr/structs.h \
src/lexer/hdr/charchecks.h \
src/lexer/hdr/fsm.h \
src/lexer/hdr/lexer.h \
src/lexer/hdr/stx_error.h \
src/parcer/hdr/expand.h \
src/parcer/hdr/parcer.h \
src/parcer/hdr/separate.h \
src/signals/hdr/sigpadloper.h \
src/utils/hdr/filelst_utils.h \
src/utils/hdr/line_navigation.h \
src/utils/hdr/simple_cmd_utils.h \
src/utils/hdr/token_utils.h 


OBJ_DIR := 	obj/
OBJ		= 	$(addprefix $(OBJ_DIR), $(SRC:src/%.c=%.o))

LIBFT_DIR := $(INCL_DIR)libft/
LIBFT	:= $(LIBFT_DIR)libft.a

READLIB = -L$(shell brew --prefix readline)/lib -lreadline
READFLAGS = -I$(shell brew --prefix readline)/include

AR		?= ar rcs;
SANFLAGS ?= -fsanitize=address -g
CFLAGS	?= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@echo $(HDR)
			@echo "Compiling minishell."
			@$(CC) $(CFLAGS) $(READLIB) $(READFLAGS) $(LIBFT) $(OBJ) -o $(NAME)
			@echo "Compilation finished."

$(LIBFT):
			@echo "Making library libft."
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) bonus

$(OBJ_DIR)%.o:	%.c $(HDR)
			@echo creating object files.
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(READFLAGS) -c $< -o $@

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
