# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 16:43:20 by ofadhel           #+#    #+#              #
#    Updated: 2024/10/02 20:22:04 by ofadhel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRCS = $(shell find srcs -name '*.cpp')

OBJS = $(SRCS:%.cpp=objs/%.o)

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

CC = g++

objs/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf  $(NAME) $(OBJS)

fclean: clean
	rm -rf objs

re: fclean all

.PHONY: all clean fclean re
