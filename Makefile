# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/07/12 22:11:05 by aeid             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishellasvavas
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
PFLAGS = -L./Printft -lftprintf
LFLAGS = -L./Libft -lft
RM = rm -f
PRINT_DIR = ./Printft
LIBFT_DIR = ./Libft

#headers
H_SRC = lexer.h minishell.h builtins.h parsing.h execution.h get_next_line.h
H_DIR = headers/
H_PATH = $(addprefix $(H_DIR), $(H_SRC))

#main
M_SRC = main.c signals.c
M_OBJ = $(M_SRC:.c=.o)

#lexer
L_SRC = lexer.c word_token.c utils.c meta_token.c special_token.c \
		meta_cases.c
L_DIR = Lexer/
L_PATH = $(addprefix $(L_DIR), $(L_SRC))
L_OBJ = $(L_PATH:.c=.o)

#parser
P_SRC = parsing.c expander.c get_command.c parser.c define_builtins.c
P_DIR = parsing/
P_PATH = $(addprefix $(P_DIR), $(P_SRC))
P_OBJ = $(P_PATH:.c=.o)

#builtins
B_SRC = check_env_arg.c export.c get_env.c search_env.c cd.c set_env.c \
		pwd.c export_utils.c garbage_collector.c
B_DIR = builtins/
B_PATH = $(addprefix $(B_DIR), $(B_SRC))
B_OBJ = $(B_PATH:.c=.o)

#execution
E_SRC = execution.c execute_external.c execution_routine.c \
		ft_here_doc.c exec_errno_manage.c ft_redir_in.c ft_redir_out.c \
		ft_redir_append.c
E_DIR = execution/
E_PATH = $(addprefix $(E_DIR), $(E_SRC))
E_OBJ = $(E_PATH:.c=.o)

#utils
U_SRC = strjoin_free.c
U_DIR = utils/
U_PATH = $(addprefix $(U_DIR), $(U_SRC))
U_OBJ = $(U_PATH:.c=.o)

#get_next_line
G_SRC = get_next_line.c get_next_line_utils.c
G_DIR = get_next_line/
G_PATH = $(addprefix $(G_DIR), $(G_SRC))
G_OBJ = $(G_PATH:.c=.o)

%.o: %.c $(H_PATH) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(M_OBJ) $(L_OBJ) $(P_OBJ) $(B_OBJ) $(E_OBJ) $(U_OBJ) $(G_OBJ)
	make -C $(LIBFT_DIR)
	make -C $(PRINT_DIR)
	$(CC) $(M_OBJ) $(L_OBJ) $(P_OBJ) $(B_OBJ) $(E_OBJ) $(U_OBJ) $(G_OBJ) $(LFLAGS) $(PFLAGS) -lreadline -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(M_OBJ) $(L_OBJ) $(P_OBJ) $(B_OBJ) $(E_OBJ) $(U_OBJ) $(G_OBJ)
	
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/libft.a
	$(RM) $(PRINT_DIR)/libftprintf.a
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINT_DIR)
	
re: fclean all

.PHONY: all clean fclean re