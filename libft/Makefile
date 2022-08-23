# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/28 15:02:52 by mteerlin      #+#    #+#                  #
#    Updated: 2022/01/06 13:56:47 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
REG_OBJ		= ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o \
				ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o \
				ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o \
				ft_memmove.o ft_memset.o ft_putchar_fd.o ft_putendl_fd.o \
				ft_putnbr_fd.o ft_putstr_fd.o ft_split.o ft_strchr.o \
				ft_strdup.o ft_strjoin.o ft_strlcat.o ft_strlcpy.o \
				ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o \
				ft_strtrim.o ft_strrchr.o ft_substr.o ft_tolower.o \
				ft_toupper.o
BONUS_OBJ	= ft_atof.o ft_atol.o ft_itoa_base.o ft_lstadd_back.o \
				ft_lstadd_front.o ft_lstclear.o ft_lstdelone.o ft_lstiter.o \
				ft_lstlast.o ft_lstnew.o ft_lstmap.o ft_lstsize.o ft_isspace.o \
				ft_intlen.o

HEADER		= libft.h
CFLAGS 		= -Wall -Wextra -Werror
ifdef		WITH_BONUS
OBJECTS		= $(REG_OBJ) $(BONUS_OBJ)
else
OBJECTS		= $(REG_OBJ)
endif

all: 		$(NAME)

$(NAME):	$(OBJECTS)
			@ar rcs $(NAME) $(OBJECTS)

%.o:		%.c $(HEADER)
			@$(CC) -c $(CFLAGS) -o $@ $<

bonus:
			@$(MAKE) WITH_BONUS=1 all

so:
			@$(CC) -shared -o libft.so -fPIC $(OBJECTS)

clean:
			@rm -f *.o *.so

fclean:
			@$(MAKE) clean
			@rm -f $(NAME)

re:
			@$(MAKE) fclean
			@$(MAKE) all

.PHONY:		all clean fclean re
