
#ifndef LEXER_H_
# define LEXER_H_

#include "tokeniser.h"

#define UNMATCHED 1
#define EMPTY 2
#define TOO_MANY 3
#define NULL_CMD 4
#define UNDIF_VAR 5

t_token	*lexer(char *, t_shell *, int);
int	lexer_err(int, t_ttype);
int	lexer_err_too_many(t_ttype);
int	lexer_err_unmatched(t_ttype);

#endif
