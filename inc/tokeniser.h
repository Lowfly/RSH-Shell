
#ifndef TOKENISER_H_
# define TOKENISER_H_

#include "token.h"
#include "token_define.h"
#include "shell.h"

typedef struct s_string t_string;

#define	NB_PRIMARY_TOKEN	13
#define NB_PRIMARY_FUNC		6

/*token_concat*/
int		token_concat(t_token **);
int		token_concat_type(t_token **, t_ttype);
int		token_concat_define(t_token **, char *, t_ttype, char);
int		token_concat_op(t_token **, char *, t_ttype, t_ttype);
t_token		*token_concat_by_type(t_token *, t_ttype);
char		*token_concat_string(t_token *, t_token *, int);
t_token		*token_concat_by_pair(t_token *, char *, t_ttype);
int		token_concat_word(t_token *);

/* token redirection */
int		token_dirfile(t_token **);
int		token_dirfile_ord(t_token **);

/* token_delete */
int		token_delete(t_token *);
void		token_delete_list(t_token *);
int		token_delete_type(t_token **, t_ttype);

/* token_replace */
int		token_replace(t_token **, t_shell *);
char		**token_alias_replace(char **, t_shell *);
t_token		*token_globing(t_token *);
int		token_replace_home(t_token **, t_shell *);
int		token_replace_exec(t_token **, t_shell *);

/* primary */
t_token		*tokeniser(char *);
t_token		*tokeniser_create(char *);
int		token_backslash(t_token **);
int		token_insert(t_token **, t_ttype, char);
int		token_normaliser(t_token **);

/* rebinding */
int		token_rebinding(t_token *, t_shell *);
int		token_rebinding_put_in_cmd(t_string **, char);

/* secondary */
int		token_secondary(t_token **);
int		token_group_by_type(t_token **, t_ttype);
int		token_parentheses(t_token **);
int		token_cmd(t_token **);
int		token_var(t_token **);
t_token		*token_var_replace(t_token *, t_shell *);
int		token_sequences(t_token **);
int		token_logic(t_token *);

/*lexer_utils*/
int		lexer_find_occurences(t_token *, t_ttype);
t_token		*lexer_find_last_occurences(t_token *, t_ttype);
int		lexer_check_null_cmd(t_token **);
int		lexer_check_is_param(t_ttype);
int		lexer_check_is_null(t_ttype);
void		show_token_list(t_token *);

#endif
