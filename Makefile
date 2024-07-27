# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:05:04 by oelharbi          #+#    #+#              #
#    Updated: 2024/06/07 19:38:44 by hbettal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINE_INC = -I$(shell brew --prefix readline)/include

READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

NAME = minishell

HEADER = minishell.h

OBJ = 	minishell.o							signals.o\
		parsing/lexer.o						parsing/error_exit.o\
		parsing/lexer_utils.o				parsing/prompt.o\
		parsing/parsing.o					parsing/parsing_utils.o\
		parsing/classification.o			parsing/expansion.o\
		parsing/expansion_utils.o			parsing/syntax_error.o\
		parsing/struct_to_execute_utils.o	parsing/struct_to_execute.o\
		parsing/garbage_collector.o			utils/ft_isalnum.o\
		utils/ft_isalpha.o					utils/ft_isdigit.o\
		utils/ft_itoa.o						utils/ft_memcpy.o\
		utils/ft_memmove.o					utils/ft_putchar_fd.o\
		utils/ft_putnbr_fd.o				utils/ft_putstr_fd.o\
		utils/ft_split.o					utils/ft_strdup.o\
		utils/ft_strlcat.o					utils/ft_strlcpy.o\
		utils/ft_strlen.o					utils/ft_strncmp.o\
		utils/ft_substr.o					utils/ft_strjoin.o\
		parsing/manage_fds.o				parsing/open_fds.o\
		utilities/numbers_utlis.o			utilities/utilities.o\
		excution/setup.o					redirect/here_doc.o\
		utilities/special_cases.o			builtins/pwd.o\
		builtins/echo.o						redirect/redirection.o\
		builtins/build_check.o				builtins/cd.o\
		builtins/env.o						utilities/list.o\
		builtins/export.o					excution/run_cmd.o\
		builtins/unset.o					utilities/ft_split_k.o\
		builtins/exit.o						parsing/expansion_2.o\

all: $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

$(NAME) : $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ)  $(READLINE_LIB)  -o $(NAME)

%.o : %.c $(HEADER)
	@echo "\033[0;34mCompiling $< .\033[0;m"
	@$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@echo "\033[0;31mRemoving object files.\033[0;m"

	@echo "\033[0;31mRemoving object files.\033[0;m"

	@rm -f $(OBJ)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

fclean: clean
	@echo "\033[0;31mRemoving program.\033[0;m"
	@echo "\033[1;32mDONE ✅\033[0;m"
	@rm -f $(NAME)

re: fclean all 

.PHONY: clean
