# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/11 11:12:30 by tle-coza     #+#   ##    ##    #+#        #
#    Updated: 2018/03/08 15:29:46 by tle-coza    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

HEADER = ft_printf.h ../libft.h

SRC = ft_printf.c check_spec.c get_spec.c parse_args.c argsize.c print_str.c \
	  print_nb.c compute_nb.c

LIBFT	= ../libft.a
LIB_INC	= -I ../libft.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ../
	libtool -v -static -o $@ $^ $(LIBFT)

%.o: %.c
	gcc $(FLAGS) $(LIB_INC) -I ft_printf.h -c $< -o $@ 

clean:
	/bin/rm -f $(OBJ) ft_printf.h.gch ./libft/libft.h.gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
