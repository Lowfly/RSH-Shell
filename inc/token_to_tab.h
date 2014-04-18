
#ifndef TOKEN_TO_TAB_H_
# define TOKEN_TO_TAB_H_

#include "token.h"

#define NB_CONVERT_FUNC 4

typedef struct s_shell t_shell;

char	**token_to_tab(t_token *);
int	token_to_tab_len(t_token *);
char	**token_convert_cmd(t_token *, t_shell *, int);
int	token_convert_squote(t_token *);
int	token_convert_dquote(t_token *, t_shell *);
int	token_convert_bquote(t_token *);
int	token_convert_parentheses(t_token *);
char	*token_convert_tab_to_str(char **);

#endif /* TOKEN_TO_TAB_H_ */
