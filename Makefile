NAME = minishell

CFLAGS = -Wall -Werror -Wextra

LIBFT = libft/libft.a

SRCS = lexer/lexer.c lexer/lexer_utils.c lexer/quotes.c lexer/token.c \
		lexer/lexer_environement.c lexer/lexer_redirections.c lexer/useless_utils.c\
		parser/ast.c parser/parser.c parser/here_doc.c parser/parser_utils.c \
		parser/parser_pipelines.c parser/parser_redirections.c \
		utils.c signals.c free_elements.c main.c visitor.c \
		./exec/builtins/ft_cd.c ./exec/builtins/ft_echo.c \
		./exec/builtins/ft_env.c ./exec/builtins/ft_exit.c \
		./exec/builtins/ft_export.c ./exec/builtins/ft_pwd.c \
		./exec/builtins/ft_unset.c ./exec/touls/ft_getenv_exec.c \
		./exec/touls/utils.c ./exec/exec_main.c ./exec/child_proses.c \
		./exec/redirection_managment.c ./exec/touls/convert_var_to_env.c ./exec/touls/stack.c


OBJECTS = $(SRCS:.c=.o)

all : $(NAME) $(LIBFT)

$(NAME) :
	@gcc $(CFLAGS) $(SRCS) libft/*.c -o $(NAME) -lreadline

$(LIBFT) :
	@make -C libft/

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(OBJECTS)

re: fclean all