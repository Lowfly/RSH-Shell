NAME	=	rsh

DIRSRC	=	./src/

DIRCD	=	cd_src/

DIREXEC	=	exec/

DIRFORK	=	fork/

DIRENV	=	env/

DIRPRT	=	prompt/

DIRPARS	=	parser/

DIRLEX	=	lexer/

DIREPUR	=	epur_str/

DIRGNL	=	gnl/

DIRTREE	=	tree/

DIRHIST	=	history/

DIRSIGN	=	signal/

DIRBUIL	=	builtins/

DIRFD	=	filedescriptor/

DIRGFL 	= 	./get_f_line/

DIRBENV =       ./built_env/

DIRUNSET=       ./unsetenv/

DIRSET	=	./setenv/

DIRCONF	=	./conf/

DIRAL	=	./alias/

DIRECHO	=	./echo/

DIRINC 	= 	./inc/

MAKELIB	=	make -C./lib/

NCURSES = 	-lncurses

SRCS	=	$(DIRSRC)42sh.c \
		$(DIRSRC)get_opt.c \
		$(DIRSRC)$(DIRCD)cd.c \
		$(DIRSRC)$(DIREXEC)exec.c \
		$(DIRSRC)$(DIREXEC)exec_tree.c \
		$(DIRSRC)$(DIREXEC)redirect.c \
		$(DIRSRC)$(DIREXEC)rec_redirect.c \
		$(DIRSRC)$(DIREXEC)select_file.c \
		$(DIRSRC)$(DIREXEC)pipes.c \
		$(DIRSRC)$(DIREXEC)backquote.c \
		$(DIRSRC)$(DIREXEC)logic.c \
		$(DIRSRC)$(DIREXEC)reset_fd.c \
		$(DIRSRC)$(DIREXEC)exec_parsed.c \
		$(DIRSRC)$(DIRFORK)fork.c \
		$(DIRSRC)$(DIRFORK)gen_env.c \
		$(DIRSRC)$(DIRFORK)wait.c \
		$(DIRSRC)$(DIRFORK)job_control.c \
		$(DIRSRC)$(DIRENV)init_shell.c\
		$(DIRSRC)$(DIRENV)init_env.c \
		$(DIRSRC)$(DIRENV)cut_func.c \
		$(DIRSRC)$(DIRENV)control_env.c \
		$(DIRSRC)$(DIRENV)free_env.c\
		$(DIRSRC)$(DIRPRT)prompt.c \
		$(DIRSRC)$(DIRENV)explor_env.c \
		$(DIRSRC)$(DIRPARS)parser.c \
		$(DIRSRC)$(DIRENV)pars_path.c \
		$(DIRSRC)$(DIRGNL)get_next_line.c \
		$(DIRSRC)$(DIREPUR)epur_str.c \
		$(DIRSRC)$(DIREPUR)clean_tab.c \
		$(DIRSRC)$(DIRLEX)lexer.c \
		$(DIRSRC)$(DIRLEX)lexer_utils.c \
		$(DIRSRC)$(DIRLEX)lexer_err.c \
		$(DIRSRC)$(DIRLEX)token.c \
		$(DIRSRC)$(DIRLEX)token_cmd.c \
		$(DIRSRC)$(DIRLEX)token_glob.c \
		$(DIRSRC)$(DIRLEX)token_normaliser.c \
		$(DIRSRC)$(DIRLEX)token_logic.c \
		$(DIRSRC)$(DIRLEX)token_convert_cmd.c \
		$(DIRSRC)$(DIRLEX)token_convert_func.c \
		$(DIRSRC)$(DIRLEX)token_concat.c \
		$(DIRSRC)$(DIRLEX)token_var.c \
		$(DIRSRC)$(DIRLEX)token_dirfile.c \
		$(DIRSRC)$(DIRLEX)token_dirfile_ord.c \
		$(DIRSRC)$(DIRLEX)token_concat_func.c \
		$(DIRSRC)$(DIRLEX)token_concat_type.c \
		$(DIRSRC)$(DIRLEX)token_delete.c \
		$(DIRSRC)$(DIRLEX)token_secondary.c \
		$(DIRSRC)$(DIRLEX)token_bslash.c \
		$(DIRSRC)$(DIRLEX)token_replace.c \
		$(DIRSRC)$(DIRLEX)token_group_by.c \
		$(DIRSRC)$(DIRLEX)token_parentheses.c \
		$(DIRSRC)$(DIRLEX)token_rebinding.c \
		$(DIRSRC)$(DIRLEX)token_sequences.c \
		$(DIRSRC)$(DIRLEX)token_alias.c \
		$(DIRSRC)$(DIRLEX)tokeniser.c \
		$(DIRSRC)$(DIRLEX)show_token.c \
		$(DIRSRC)$(DIRLEX)token_to_tab.c \
		$(DIRSRC)$(DIRHIST)history.c \
		$(DIRSRC)$(DIRHIST)free_history.c \
		$(DIRSRC)$(DIRHIST)init_history.c \
		$(DIRSRC)$(DIRHIST)b_history.c \
		$(DIRSRC)$(DIRHIST)b_options.c \
		$(DIRSRC)$(DIRTREE)tree.c \
		$(DIRSRC)$(DIRTREE)tree_free.c \
		$(DIRSRC)$(DIRTREE)node.c \
		$(DIRSRC)$(DIRTREE)split.c \
		$(DIRSRC)$(DIRGFL)edit_cast.c \
		$(DIRSRC)$(DIRGFL)edit_tools.c \
		$(DIRSRC)$(DIRGFL)edit_free.c \
		$(DIRSRC)$(DIRGFL)edit_buffer.c \
		$(DIRSRC)$(DIRGFL)edit_comp.c \
		$(DIRSRC)$(DIRGFL)edit_free2.c \
		$(DIRSRC)$(DIRGFL)edit_history.c \
		$(DIRSRC)$(DIRGFL)edit_move.c \
		$(DIRSRC)$(DIRGFL)edit_line.c \
		$(DIRSRC)$(DIRGFL)edit_puts.c \
		$(DIRSRC)$(DIRGFL)edit_write.c \
		$(DIRSRC)$(DIRGFL)edit_key2.c \
		$(DIRSRC)$(DIRGFL)edit_idx.c  \
		$(DIRSRC)$(DIRGFL)edit_resize.c \
		$(DIRSRC)$(DIRGFL)edit_copy.c \
		$(DIRSRC)$(DIRGFL)edit_init.c \
		$(DIRSRC)$(DIRGFL)edit_key.c \
		$(DIRSRC)$(DIRGFL)edit_printable.c \
		$(DIRSRC)$(DIRGFL)edit_utils.c \
		$(DIRSRC)$(DIRGFL)get_f_line.c \
		$(DIRSRC)$(DIRSIGN)process_statut.c \
		$(DIRSRC)$(DIRSIGN)get_signal.c \
		$(DIRSRC)$(DIRBUIL)builtins.c \
		$(DIRSRC)$(DIRBUIL)is_builtins.c \
		$(DIRSRC)$(DIRBUIL)return.c \
                $(DIRSRC)$(DIRUNSET)unsetenv.c \
		$(DIRSRC)$(DIRSET)setenv.c \
		$(DIRSRC)$(DIRCONF)conf.c \
                $(DIRSRC)$(DIRBENV)b_env.c \
                $(DIRSRC)$(DIRBENV)bad_option.c \
                $(DIRSRC)$(DIRBENV)check_op_null.c \
                $(DIRSRC)$(DIRBENV)exec.c \
                $(DIRSRC)$(DIRBENV)help_version.c \
                $(DIRSRC)$(DIRBENV)loop.c \
                $(DIRSRC)$(DIRBENV)options.c \
		$(DIRSRC)$(DIRBENV)check_name_value.c \
		$(DIRSRC)$(DIRFD)fd_msg_err.c \
		$(DIRSRC)$(DIRFD)fd_mode.c \
		$(DIRSRC)$(DIRFD)fd_mode2.c \
		$(DIRSRC)$(DIRFD)fd_err.c \
		$(DIRSRC)$(DIRFD)fd_err_2.c \
		$(DIRSRC)$(DIRFD)fd_check.c \
		$(DIRSRC)$(DIRAL)alias.c \
		$(DIRSRC)$(DIRAL)unalias.c \
		$(DIRSRC)$(DIRAL)free_alias.c \
		$(DIRSRC)$(DIRECHO)echo.c \


OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -I$(DIRINC)
LFLAGS	=	./lib/libmy.a $(NCURSES)

CC	=	gcc

RM	=	rm -f

all:		$(NAME)


$(NAME):	$(OBJS)
		$(MAKELIB)
		$(CC) -o $@ $(OBJS) $(LFLAGS)

clean:
		$(RM) $(OBJS)
		$(MAKELIB) clean

fclean:		clean
		$(RM) $(NAME)
		$(MAKELIB) fclean


re:		fclean all


install:	$(NAME)
		@ mkdir -p /usr/local/man/man2/
		@ cp .rsh.2.gz /usr/local/man/man2/rsh.2.gz

.PHONY:		all clean fclean re
