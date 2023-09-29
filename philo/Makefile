# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:40:40 by eduarodr          #+#    #+#              #
#    Updated: 2023/07/20 19:02:13 by eduarodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread  -g #-fsanitize=thread

RM = rm -f

SOURCES = main.c \
		srcs/utils.c\
		srcs/philo.c\
		srcs/init_philo.c\
		srcs/checker.c\
		srcs/forks.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "\033[4;33m[+] Compiling..\033[1;0m"
	$(CC) $(CFLAGS) $(SOURCES) -o ${NAME}
	@echo "\033[4;32m[✓] Ready!\033[1;0m"
clean:
	@echo "\033[4;33m[+] Cleaning objects..\033[1;0m"
	$(RM) $(OBJECTS)
	@echo "\e[4;32m[✓]Objects cleaned!\033[1;0m"

fclean: clean
	@echo "\033[4;33m[+] Cleaning functions..\033[1;0m"
	$(RM) $(NAME) philo
	@echo "\033[4;32m[✓]Functions cleaned!\033[1;0m"

re: fclean all

.PHONY: all clean fclean re
