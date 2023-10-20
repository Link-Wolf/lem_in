# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 17:15:33 by Link           #+#    #+#              #
#    Updated: 2023/10/20 10:52:41 by iCARUS           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
SRCS_N	=	lem_in						\
			utils/init					\
			utils/bugs					\
			utils/print_parsing			\
			parsing/read_input			\
			map_manipulation/add_link	\
			map_manipulation/add_room	\
			map_manipulation/delete_room

SRCS	=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N)))
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) -Llibft $(OBJS) -lft -fsanitize=address -static-libasan

$(LIBFT):
	@$(MAKE) -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -Llibft -lft -c $< -o $@ -fsanitize=address -g

clean:
	@$(MAKE) -C libft/ fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
