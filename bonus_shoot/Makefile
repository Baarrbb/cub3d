# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 23:25:19 by marvin            #+#    #+#              #
#    Updated: 2024/06/05 16:13:25 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This is a minimal set of ANSI/VT100 color codes
_END=\033[0;0m
_BOLD=\033[0;1m
_UNDER=\033[0;4m
_REV=\033[0;7m

# Colors
_GREY=\033[0;30m
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;35m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

# Inverted, i.e. colored backgrounds
_IGREY=\033[0;40m
_IRED=\033[0;41m
_IGREEN=\033[0;42m
_IYELLOW=\033[0;43m
_IBLUE=\033[0;44m
_IPURPLE=\033[0;45m
_ICYAN=\033[0;46m
_IWHITE=\033[0;47m

# Color test
_ROSE=\x1b[38;5;213m
_NEW_BLUE=\x1b[38;5;80m
_NEW_YELLOW=\x1b[38;5;228m
_GREEN_BOLD=\033[1;32m
_LIGHT_GREY=\x1b[38;5;242m
_ORANGE=\x1b[38;5;009m
_VERT=\x1b[38;5;029m
_VERT_UNDER=\033[0;4m\x1b[38;5;029m
_VERT_BOLD=\033[1m\x1b[38;5;029m
_VERT_REV=\x1b[48;5;029m

_PURPLE=\x1b[38;5;093m
_PURPLE_UNDER=\033[0;4m\x1b[38;5;093m
_PURPLE_BOLD=\033[1m\x1b[38;5;093m
_PURPLE_REV=\x1b[48;5;093m

MAKEFLAGS += --no-print-directory
OPTIONS_PRINTED = /tmp/options_printed
# OPTIONS_PRINTED = ~/sgoinfre/options_printed

SRC_DIR = src
PARS_DIR = $(SRC_DIR)/parsing

SRC_MAIN = \
	$(SRC_DIR)/game_init.c \
	$(SRC_DIR)/sanitize.c \
	$(SRC_DIR)/raycasting.c \
	$(SRC_DIR)/get_distance.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/mlx_pixel.c \
	$(SRC_DIR)/key_event.c \
	$(SRC_DIR)/trigo_utils.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/move.c \
	$(SRC_DIR)/shoot.c \
	$(SRC_DIR)/shoot_right.c \
	$(SRC_DIR)/shoot_left.c \
	$(SRC_DIR)/render_shoot.c
	

SRC_PARS = \
	$(PARS_DIR)/parsing_chars.c \
	$(PARS_DIR)/parsing_map.c \
	$(PARS_DIR)/parsing_map2.c \
	$(PARS_DIR)/parsing_sanitize.c \
	$(PARS_DIR)/parsing_struct.c \
	$(PARS_DIR)/parsing_utils.c \
	$(PARS_DIR)/parsing.c \
	$(PARS_DIR)/right_side.c \
	$(PARS_DIR)/parsing_utils2.c

SRC = \
	$(SRC_MAIN) \
	$(SRC_PARS)

OBJ_DIR = src/obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

NAME = cub3d
RM = rm -rf
CC = clang
CFLAGS = -Wall -Wextra -g3 -O3 #-Werror
LIBFT = libft/libft.a
LIB = -Lminilibx-linux -lmlx -lXext -lX11 -lm
INC = -I./headers -Iminilibx-linux

#ajouter regle pour compilation minilibx

all : $(NAME)

print_options : $(OPTIONS_PRINTED)

$(OPTIONS_PRINTED) :
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_ROSE)Compiling options$(_END) :  $(CC) $(CFLAGS)\""
	@ /bin/bash -c "echo"
	@ touch $(OPTIONS_PRINTED)

$(NAME) : $(LIBFT) $(OPTIONS_PRINTED) $(OBJ_DIR) $(OBJ)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_PURPLE_UNDER)Configuration minilibx-linux$(_END) 👇\""
	@ /bin/bash -c "echo"
	@ make -C minilibx-linux
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_NEW_BLUE)Linking files creating binary $(NAME)$(_END)\""
	@ /bin/bash -c "echo -e \"$(CC) $(CFLAGS) $(notdir $(OBJ) $(LIBFT))\""
	@ $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIB) -o $(NAME)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_GREEN_BOLD)[DONE]$(_END)\"" 

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ /bin/bash -c "printf \"$(_BLUE)Compiling$(_END) %-21s --> %-21s\n\" $(notdir $<) $(notdir $@)"
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT) :
	@ /bin/bash -c "echo -e \"$(_NEW_YELLOW)Entering directory 'libft'$(_END)\""
	@ make -C libft all
	@ /bin/bash -c "echo -e \"$(_NEW_YELLOW)Leaving directory 'libft'$(_END)\""
	@ /bin/bash -c "echo"

clean :
	@ make -C libft clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning object files$(_END)\""
	@ $(RM) $(OBJ_DIR)
	@ $(RM) $(OPTIONS_PRINTED)

fclean : clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning archive $(LIBFT) $(_END)\""
	@ $(RM) $(LIBFT)
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning binary$(_END)\""
	@ $(RM) $(NAME)

re : fclean all
