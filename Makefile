# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 16:43:20 by ofadhel           #+#    #+#              #
#    Updated: 2024/08/03 18:10:39 by ofadhel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRCS = $(shell find srcs -name '*.cpp')

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

CC = g++

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf  $(NAME) $(OBJS)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
