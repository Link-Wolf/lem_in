# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 17:15:33 by Link           #+#    #+#              #
#    Updated: 2023/10/25 16:11:422 by iCARUS           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in
NAME_BONUS		=	vizualizer

LIBMLX	:= libs/MLX42
HEADERS	:= -I includes -I $(LIBMLX)/include -I libs/libft
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -Llibs/libft -lft

LIBFT	=	libs/libft/libft.a

SRCS_N			=	lem_in							\
					utils/init						\
					utils/bugs						\
					utils/print_parsing				\
					utils/delete_things				\
					utils/queue						\
					parsing/read_input				\
					map_manipulation/add_link		\
					map_manipulation/add_room		\
					map_manipulation/include_link	\
					processing/check_for_trivials	\
					processing/resolve				\
					processing/throw_ants			\
					visualiser/visualiser			\
					visualiser/draw					\
					visualiser/hook					\
					visualiser/evaluate_coords		\

SRCS			=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N)))

OBJS			=	$(SRCS:.c=.o)
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

OBJ_COLOR		=		"\e[38;5;147m"
CLN_COLOR		=		"\e[38;5;124m"
BIN_COLOR		=		"\e[38;5;129m"
ERRASE_LINE		=		"\e[2K\r"

all: $(NAME)

$(LIBMLX)/build/libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null && make -C $(LIBMLX)/build -j4 > /dev/null
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"libmlx"\t\t\t\t[ ✓ ]\n\e[0m"

$(NAME): $(LIBFT) $(OBJS) $(LIBMLX)/build/libmlx42.a
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -fsanitize=address -g
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME)"\t\t\t\t[ ✓ ]\n\e[0m"

$(LIBFT):
	@$(MAKE) -C libs/libft/

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) -fsanitize=address -g
	@printf $(ERRASE_LINE)$(OBJ_COLOR)"\t"$@"\e[0m"

clean:
	@$(MAKE) -C libs/libft/ fclean
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)
	@printf $(CLN_COLOR)"\tClean \t\t\t\t[ ✓ ]\n\e[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@printf $(CLN_COLOR)"\tBinary clean \t\t\t[ ✓ ]\n\e[0m"

re: fclean all

.PHONY: all clean fclean re bonus
