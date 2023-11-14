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
NAME_BONUS		=	visualiser

LIBMLX	:= libs/MLX42
HEADERS	:= -I includes -I $(LIBMLX)/include -I libs/libft
LIBS	:= -Llibs/libft -lft
LIBS_BONUS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -Llibs/libft -lft

LIBFT	=	libs/libft/libft.a

DEBUG	= -fsanitize=address -g -static-libasan

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

SRCS_N_BONUS	=	lem_in.bonus					\
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
					visualiser/visualize			\

SRCS			=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N)))
SRCS_BONUS		=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N_BONUS)))

OBJS			=	$(SRCS:.c=.o)
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

OBJ_COLOR		=		"\e[38;5;147m"
CLN_COLOR		=		"\e[38;5;124m"
BIN_COLOR		=		"\e[38;5;129m"
ERRASE_LINE		=		"\e[2K\r"

all: mandatory bonus

mandatory: $(NAME)
bonus: $(NAME_BONUS)

$(LIBMLX)/build/libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null && make -C $(LIBMLX)/build -j4 > /dev/null
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"libmlx"\t\t\t\t[ ✓ ]\n\e[0m"

$(LIBFT):
	@$(MAKE) -C libs/libft/

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBS)  -o $(NAME) $(DEBUG)
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME)"\t\t\t\t[ ✓ ]\n\e[0m"

$(NAME_BONUS): $(LIBFT) $(LIBMLX)/build/libmlx42.a $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS_BONUS) $(HEADERS) -o $(NAME_BONUS) $(DEBUG)
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME_BONUS)"\t\t\t[ ✓ ]\n\e[0m"


%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) $(DEBUG)
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
