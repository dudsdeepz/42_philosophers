# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:40:40 by eduarodr          #+#    #+#              #
#    Updated: 2023/06/23 14:46:42 by eduarodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

SOURCES = main.c \
		srcs/utils.c\
		srcs/philo.c\

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o ${NAME}

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME) philo

re: fclean all

.PHONY: all clean fclean re