# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 17:15:33 by Link           #+#    #+#              #
#    Updated: 2023/10/24 13:06:05 by iCARUS           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
SRCS_N	=	lem_in							\
			utils/init						\
			utils/bugs						\
			utils/print_parsing				\
			utils/delete_things				\
			parsing/read_input				\
			map_manipulation/add_link		\
			map_manipulation/add_room		\
			map_manipulation/include_link	\
			processing/throw_ants			\
			processing/process_map			\
			processing/check_for_trivials	\
			processing/conflicts			\
			processing/sort_pathes			\

SRCS	=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N)))
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

OBJ_COLOR		=		"\e[38;5;147m"
CLN_COLOR		=		"\e[38;5;124m"
BIN_COLOR		=		"\e[38;5;129m"
ERRASE_LINE		=		"\e[2K\r"

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -Llibft $(OBJS) -lft -fsanitize=address -static-libasan
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME)"\t\t\t\t[ ✓ ]\n\e[0m"

$(LIBFT):
	@$(MAKE) -C libft/

%.o: %.c
	@$(CC) $(CFLAGS) -Llibft -lft -c $< -o $@ -fsanitize=address -g
	@printf $(ERRASE_LINE)$(OBJ_COLOR)"\t"$@"\e[0m"

clean:
	@$(MAKE) -C libft/ fclean
	@$(RM) $(OBJS)
	@printf $(CLN_COLOR)"\tClean \t\t\t\t[ ✓ ]\n\e[0m"

fclean: clean
	@$(RM) $(NAME)
	@printf $(CLN_COLOR)"\tBinary clean \t\t\t[ ✓ ]\n\e[0m"

re: fclean all

.PHONY: all clean fclean re
