# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: event <event@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 17:15:33 by Link           #+#    #+#              #
#    Updated: 2023/10/18 11:11:17 by event            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
SRCS_N	=	lem_in						\
			utils/init					\
			utils/bugs					\
			parsing/read_input			\
			map_manipulation/add_link	\
			map_manipulation/add_room

SRCS	=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N)))
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -c $(OBJS) -Llibft -lft -o $(NAME)

$(LIBFT):
	@$(MAKE) -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
