
#include	<stdlib.h>
#include	<stdio.h>
#include	"lexer.h"
#include	"history.h"

/*
** Transformation of the command into a list of token in 2 parts:
** Elementary token (tokeniser) and group of token (token_secondary).
** Rebinding of the list for the history.
*/
t_token		*lexer(char *line, t_shell *sh, int opt)
{
  t_token	*list;

  if ((line == NULL) || ((list = tokeniser(line)) == NULL))
    return (NULL);
  if (opt && token_rebinding(list, sh) == EXIT_FAILURE)
    fprintf(stderr, "Error in commande rebinding: Malloc failled");
  if (token_replace(&list, sh) == EXIT_FAILURE)
    return (NULL);
  if (token_secondary(&list) == EXIT_FAILURE)
    return (NULL);
  return (list);
}
