##
## EPITECH PROJECT, 2018
## Fairefichier
## File description:
## This is a fairefichier, made by HeyShafty
##

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LIGHT_GREY	=	"\e[37m"
DARK_GREY	=	"\e[90m"
LIGHT_RED	=	"\e[91m"
LIGHT_GREEN	=	"\e[92m"
LIGHT_YELLO	=	"\e[93m"
LIGHT_BLUE	=	"\e[94m"
LIGHT_MAGEN	=	"\e[95m"
LIGHT_CYAN	=	"\e[96m"
LINE_RETURN	=	$(ECHO) ""

COLOR_THEME	=	$(BLUE_C)
DEBUG_THEME	=	$(CYAN_C)
TESTS_THEME	=	$(RED_C)

NAME	=	42sh
ROOT_PATH	=	./
SRC_NAME	=	src
TESTS_NAME	=	tests
INCL_NAME	=	include
SRC_PATH	=	$(ROOT_PATH)$(SRC_NAME)
INCL_PATH	=	$(ROOT_PATH)$(INCL_NAME)
TESTS_PATH	=	$(ROOT_PATH)$(TESTS_NAME)

BUILTINS	=	builtins/
TOKENIZER	=	tokenizer/
PARSER	=	parser/
UTILS	=	utils/

SRC	=	$(BUILTINS)echo/echo.c \
		$(BUILTINS)echo/flag_parsing.c \
		$(BUILTINS)set/set.c \
		$(BUILTINS)set/set_util.c \
		$(BUILTINS)setenv/setenv.c \
		$(BUILTINS)setenv/str_valid.c \
		$(BUILTINS)alias.c \
		$(BUILTINS)apply_alias.c \
		$(BUILTINS)apply_alias_utils.c \
		$(BUILTINS)builtins.c \
		$(BUILTINS)cd.c \
		$(BUILTINS)disp_alias.c \
		$(BUILTINS)env.c \
		$(BUILTINS)exit.c \
		$(BUILTINS)repeat.c \
		$(BUILTINS)unalias.c \
		$(BUILTINS)unset.c \
		$(BUILTINS)unsetenv.c \
		$(BUILTINS)utils_alias.c \
		$(BUILTINS)utils_builtins.c \
		$(BUILTINS)where.c \
		$(BUILTINS)which.c \
		$(BUILTINS)whoami.c \
		$(BUILTINS)yes.c \
		$(TOKENIZER)add_node.c \
		$(TOKENIZER)create_node.c \
		$(TOKENIZER)create_token_list_from_line.c \
		$(TOKENIZER)create_token_list_head.c \
		$(TOKENIZER)delete_node.c \
		$(TOKENIZER)get_delim_index.c \
		$(TOKENIZER)token_list.c \
		$(TOKENIZER)utils.c \
		$(PARSER)check_red_type_cond.c \
		$(PARSER)check_redirections.c \
		$(PARSER)check_separators.c \
		$(PARSER)check_syntax.c \
		$(PARSER)delete_pipe.c \
		$(PARSER)delete_separators.c \
		$(PARSER)parser_utils.c \
		$(PARSER)pipe_parser.c \
		$(PARSER)separate_token_list.c \
		$(PARSER)separate_cmd_list.c \
		$(UTILS)get_builtin_idx.c \
		$(UTILS)get_line.c \
		$(UTILS)is_builtin.c \
		$(UTILS)my_get.c \
		$(UTILS)my_getenv_index.c \
		$(UTILS)my_getenv.c \
		$(UTILS)set_foreground_pgrp.c \
		builtins_constants.c \
		create_my_shell.c \
		delete_command.c \
		destroy_my_shell.c \
		do_redirections.c \
		env_variables_tokens.c \
		env_variables.c	\
		execute_builtin.c \
		execute_command.c \
		execute_line.c \
		get_command_status.c \
		handle_signals.c \
		loop_shell.c \
		my_exec_child.c \
		my_execve.c \
		path_management.c \
		setup_io.c \
		signal_constants.c

SRC_LIB	=	stdio my string

LIB_PATHS	=	lib/stdio lib/my lib/string

SRCS	=	$(SRC:%=$(SRC_PATH)/%) $(SRC_PATH)/main.c
OBJ	=	$(SRCS:.c=.o)
LIBRARIES	=	$(SRC_LIB:%=-l%)
LIB_PATHS_FLAG	=	$(LIB_PATHS:%=-L$(ROOT_PATH)%)

CFLAGS	=	-W -Wall -Wextra -Werror -I $(INCL_PATH)
LDFLAGS	=	$(LIB_PATHS_FLAG) $(LIBRARIES)
DEBUG_FLAGS	=	-g3 -gdwarf-4

MAKE_RULE	=	all
CLEAN_RULE	=	clean

all:	message build_libs $(NAME)

message:
	@$(LINE_RETURN)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"  ___  _   _ ___       _     "$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)" / _ \| | | |_ _|  ___| |__  "$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"| | | | | | || |  / __| '_ \ "$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"| |_| | |_| || | _\__ \ | | |"$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)" \___/ \___/|___(_)___/_| |_|"$(DEFAULT)
	@$(LINE_RETURN)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

build_libs: $(LIB_PATHS)
	@for MAKE_PATH in $(LIB_PATHS) ; do \
		make -C $$MAKE_PATH $(MAKE_RULE) -s ; \
	done

clean_libs: $(LIB_PATHS)
	@for MAKE_PATH in $(LIB_PATHS) ; do \
		make $(CLEAN_RULE) -C $$MAKE_PATH -s ; \
	done
	@make $(CLEAN_RULE) -C $(TESTS_PATH) -s SRC="$(SRC)" COLOR_THEME="$(RED_C)"

clean: clean_libs
	@$(RM) $(OBJ)
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) \
		$(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.*
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) \
		$(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"Valgrind files"$(DEFAULT)

fclean: CLEAN_RULE=fclean
fclean:	clean
	@$(RM) $(NAME)
	@$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) \
		$(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"Binary $(NAME)"$(DEFAULT)

re:		fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: COLOR_THEME = $(DEBUG_THEME)
debug: MAKE_RULE = debug
debug: re
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"⚠ DEBUG MODE ACTIVATED ⚠\n"$(DEFAULT)

tests_run: build_libs
	@make -C $(TESTS_PATH) -s \
		SRC="$(SRC)" \
		COLOR_THEME="$(TESTS_THEME)" \
		LIB_PATHS="$(LIB_PATHS)" \
		LIBRARIES="$(LIBRARIES)"
	@$(ECHO) $(TESTS_THEME)""
	@gcovr --exclude "tests/" --sort-uncovered --branches
	@$(ECHO) $(BOLD_T)""
	@gcovr --exclude "tests/" --sort-uncovered --print-summary
	@$(ECHO) $(DEFAULT)

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $< && \
		$(ECHO) $(DIM_T) "cc $(CFLAGS) -c "$<$(COLOR_THEME)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"cc $(CFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

.PHONY: all $(NAME) build_libs message clean_libs clean fclean re debug tests_run
