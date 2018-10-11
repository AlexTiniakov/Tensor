# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otiniako <otiniako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/11 00:07:54 by otiniako          #+#    #+#              #
#    Updated: 2018/10/11 00:08:58 by otiniako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

CPP = clang++

FLAGS = -Wall -Wextra -Werror -std=c++11

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)
	@echo "\033[1;92mtest is created!\033[1;92m"
$(NAME): $(OBJ)
	@$(CPP) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ): %.o: %.cpp
	@$(CPP) $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all