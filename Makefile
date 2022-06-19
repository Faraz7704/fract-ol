# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:40:15 by fkhan             #+#    #+#              #
#    Updated: 2022/06/19 14:35:59 by fkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= fractol
CC 					= gcc
FLAGS 				= -Wall -Werror -Wextra
INCLUDES 			= -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) \
						-I$(FT_PRINTF_HEADERS) -I$(MINILIBX_HEADERS)
LIBRARIES 			= -lmlx -lm -lft -lft_printf \
						-L$(LIBFT_DIRECTORY) -L$(FT_PRINTF_DIRECTORY) -L$(MINILIBX_DIRECTORY) \
						-framework OpenGL -framework AppKit		

LIB_DIRECTORY 		= ./lib/

LIBFT 				= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY 	= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS 		= $(LIBFT_DIRECTORY)includes/

FT_PRINTF			= $(FT_PRINTF_DIRECTORY)libft_printf.a
FT_PRINTF_DIRECTORY = $(LIB_DIRECTORY)ft_printf/
FT_PRINTF_HEADERS 	= $(FT_PRINTF_DIRECTORY)includes/

MINILIBX 			= $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY 	= $(LIB_DIRECTORY)minilibx_opengl/
MINILIBX_HEADERS	= $(MINILIBX_DIRECTORY)

HEADERS_DIRECTORY 	= ./includes/
HEADERS_LIST 		= fractol.h
HEADERS 			= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY 	= ./sources/
SOURCES_LIST 		= fractol.c
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN 				= \033[0;32m
RED 				= \033[0;31m
RESET 				= \033[0m

.PHONY: all clean fclean re

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(FT_PRINTF) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo ".\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(FT_PRINTF):
	@echo "$(NAME): $(GREEN)Creating $(FT_PRINTF)...$(RESET)"
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(MINILIBX)
	@echo "$(NAME): $(RED)$(MINILIBX) was deleted$(RESET)"
	@rm -f $(FT_PRINTF)
	@echo "$(NAME): $(RED)$(FT_PRINTF) was deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re