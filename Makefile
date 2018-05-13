# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 20:57:47 by mpascaud          #+#    #+#              #
#    Updated: 2018/05/13 18:27:13 by mpascaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in.a

TAGS = -Wall -Werror -Wextra

SRC = get_next_line.c ft_strnew.c ft_strlen.c ft_strncat.c ft_strcpy.c ft_isdigit.c ft_strstr.c ft_strcmp.c ft_atoi.c \
	  gnl.c gnl_auxis.c \
	  build1.c build2_name.c build3_place_start_end.c build4_tunnels.c build4_tunnels2.c build5_place.c \
	  possible_to_way.c way1.c way2.c way3_is_there1.c way3_is_there2.c \
	  listlist.c listlist_waylist.c \
	  free.c free_auxis.c

BIN = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@ gcc $(TAGS) -c $(SRC)
	@ ar rc $(NAME) $(BIN)
	@ ranlib $(NAME)
	@ gcc -fsanitize=address -o lem-in lem-in.c lem-in.a

clean:
	@ rm -rf $(BIN) lem-in.o

fclean: clean
	@ rm -rf $(NAME)
	@ rm -rf lem-in

re: fclean all


.PHONY: all clean fclean re
