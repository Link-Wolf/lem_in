# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: link <link@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 17:15:33 by Link           #+#    #+#              #
#    Updated: 2023/10/18 12:46:26 by link             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
SRCS_N	=	lem_in						\
			utils/init					\
			utils/bugs					\
			utils/print_parsing			\
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
	$(CC) $(CFLAGS) -Llibft -lft -o $(NAME) $(OBJS)

$(LIBFT):
	@$(MAKE) -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -Llibft -lft -c $< -o $@

clean:
	@$(MAKE) -C libft/ fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
