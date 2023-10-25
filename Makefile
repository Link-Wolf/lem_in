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

LIBMLX	:= ./mlx/MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT	=	libft/libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= -L$(LIBMLX)/build/ -lmlx42 -ldl -lglfw -pthread -lm

SRCS_N			=	lem_in							\
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

SRCS			=	$(addsuffix .c, $(addprefix srcs/, $(SRCS_N)))

SRCS_N_BONUS	=	visualizer/visualizer

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

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null && make -C $(LIBMLX)/build -j4 > /dev/null

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -Llibft $(OBJS) -lft -fsanitize=address -static-libasan
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME)"\t\t\t\t[ ✓ ]\n\e[0m"

$(LIBFT):
	@$(MAKE) -C libft/

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf $(ERRASE_LINE)$(OBJ_COLOR)"\t"$@"\e[0m"

bonus: libmlx $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME_BONUS)"\t\t\t\t[ ✓ ]\n\e[0m"
	
clean:
	@$(MAKE) -C libft/ fclean
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)
	@printf $(CLN_COLOR)"\tClean \t\t\t\t[ ✓ ]\n\e[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@printf $(CLN_COLOR)"\tBinary clean \t\t\t[ ✓ ]\n\e[0m"

re: fclean all

.PHONY: all clean fclean re bonus
