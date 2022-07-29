# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliot <tliot@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 02:02:45 by engooh            #+#    #+#              #
#    Updated: 2022/07/29 01:48:48 by tliot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#                               INCLUDES                                       # 
#                                                                              #
################################################################################
INC = -I ./include

################################################################################
#                                                                              #
#                               SOURCE FILES                                   # 
#                                                                              #
################################################################################
SRC =	./source/main/main.c\
		./source/builtins/ft_exec_cd.c\
		./source/builtins/ft_exec_echo.c\
		./source/builtins/ft_exec_env.c\
		./source/builtins/ft_exec_export.c\
		./source/builtins/ft_exec_pwd.c\
		./source/builtins/ft_exec_unset.c\
		./source/builtins/ft_manage_builtins.c\
		./source/excution/FT_BUG.c\
		./source/excution/ft_path.c\
		./source/excution/ft_exec.c\
		./source/environement/env.c\
		./source/environement/ft_lst_env.c\
		./source/parsing/ft_lib_sim_parsing.c\
		./source/parsing/ft_sim_parsing.c
		
		
################################################################################
#                                                                              #
#                               OBJECT FILES                                   # 
#                                                                              #
################################################################################
OBJ = ${SRC:%.c=%.o}

################################################################################
#                                                                              #
#                               LIBRARY                                        # 
#                                                                              #
################################################################################
LIB = ./source/share/libft/libft.a

################################################################################
#                                                                              #
#                               DEPENDENCE                                     # 
#                                                                              #
################################################################################
DEPS = ${SRC:%.c=%.d}

################################################################################
#                                                                              #
#                               COMPILATIONS FLAGS                             # 
#                                                                              #
################################################################################
CC = gcc
CFLAG = -g3 -Werror -Wall -Wextra 

################################################################################
#                                                                              #
#                               OTHER MAKE                                     # 
#                                                                              #
################################################################################
NAME = minishell
PATH_LIBFT = ./source/share/libft/

################################################################################
#                                                                              #
#                               RULES                                          # 
#                                                                              #
################################################################################
all: MAKE_LIBFT $(NAME)

$(NAME) : $(OBJ)
	$(CC) -g3 $(CFLAG) $(OBJ) $(LIB) -lreadline -o $@ $(INC)

MAKE_LIBFT:
	make -C $(PATH_LIBFT)

%.o: %.c
	$(CC) $(CFLAG) -MMD -c $< -o $@ $(INC)

clean:
	rm -f $(OBJ)
	rm -f $(DEPS)
	make clean -C $(PATH_LIBFT)

fclean : clean
	rm -f $(NAME)
	make - fclean -C $(PATH_LIBFT)

re: fclean
	make all

.PHONY: all fclean clean re 
