# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/23 19:11:16 by tle-coza     #+#   ##    ##    #+#        #
#    Updated: 2018/10/15 11:17:46 by tle-coza    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME        =   42sh

FLAGS		= 	-Wall -Wextra -Werror -O2

MSH_INIT	=	$(addprefix msh_init/, \
				msh_hashbin_utils.c msh_prompt.c msh_local_var.c \
				init_shell.c  msh_lstenv.c  msh_hashbin.c \
				msh_environment.c msh_terminal.c msh_signal.c)

MSH_BULTIN	=	$(addprefix msh_builtin/, \
				msh_builtin.c msh_env.c msh_unset.c msh_export.c \
				msh_cd.c msh_var_utils.c msh_exit.c msh_echo.c \
				msh_unsetenv.c msh_setenv.c msh_hash.c msh_cd_calculate.c \
				msh_cd_utils.c msh_env_dispatch.c)

MSH_INPUT	=	$(addprefix msh_input/, \
				msh_input.c move_choice.c input_utils.c \
				cursor_position.c history_navigation.c cursor_navigation.c \
				backspace_delete.c utils_backspace_delete.c input_checker.c \
				cut_copy.c paste.c window_size.c process_input.c\
				msh_completion.c compl_get_matches.c compl_get_word.c \
				compl_display.c compl_display_calculate.c compl_process_word.c \
				compl_process_closest_match.c clear_screen.c \
				compl_matches_utils.c)

MSH_LEXER	=	$(addprefix msh_lexer/, \
				tokenize_backslash.c tokenize_operators.c tokenize_quote.c \
				tokenize_dquote.c tokenize_regular.c lexer_tokenize.c \
				tokenlst_utils.c tools_parse.c lexer_tools.c  operator_utils.c)

MSH_PARSER	=	$(addprefix msh_parser/, \
				ft_remove_quoting.c msh_expand.c cmds_utils.c here_doc.c \
				syntax_checker.c msh_redir.c msh_simple_cmd.c msh_parser.c \
				ft_expand_tilde.c ft_expand_dollar.c)

MSH_EXEC	=	$(addprefix msh_exec/, \
				exec_all.c process_redir.c fd_utils.c msh_pipe.c msh_exec.c \
				msh_dispatch_cmd.c msh_parse_status.c pipe_utils.c)

MSH_HISTORY	=	$(addprefix msh_history/, \
				msh_history.c history_utils.c history_options.c history_lst.c \
				bang_expand.c bang_hist_getters.c bang_event_utils.c \
				bang_process_event.c history_opt_utils.c history_opt_anrw.c \
				history_opt_cdsp.c bang_parsers.c bang_parser_utils.c)

FILENAMES   =   main.c msh_error2.c msh_error.c msh_error_term.c msh_utils.c \
				$(MSH_INIT) \
				$(MSH_BULTIN) \
				$(MSH_INPUT) \
				$(MSH_LEXER) \
				$(MSH_PARSER) \
				$(MSH_EXEC) \
				$(MSH_HISTORY)

SOURCES     =   $(addprefix srcs/, $(FILENAMES))

OBJECTS     =   $(SOURCES:.c=.o)

L_FT        =   ./libft

LIB_LNK     =   -L $(L_FT) -l ft

TERMCAP_LNK =	-ltermcap

LIB_INC     =   -I $(L_FT)/libft.h

CC			=	gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	    @$(MAKE) -C $(L_FT)
		$(CC) -I ./includes $(OBJECTS) $(TERMCAP_LNK) $(LIB_LNK) -o $@

%.o: ./%.c
	    $(CC) $(FLAGS) $(LIB_INC) -I ./includes -c $< -o $@

clean:
#		@$(MAKE) -C $(L_FT) clean
		rm -rf $(OBJECTS)

fclean: clean
		rm -rf $(NAME)
#		@$(MAKE) -C $(L_FT) fclean

clear:
		@$(MAKE) all
		@$(MAKE) clean

re:
	    @$(MAKE) fclean
		@$(MAKE) all
