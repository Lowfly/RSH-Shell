
#include <stdlib.h>
#include "tokeniser.h"

int		token_normaliser_transform(t_token *tmp, int quote, int dquote)
{
  if ((tmp->type == VAR || tmp->type == HOME)
      && quote != 0 && (quote % 2 != 0))
    tmp->type = WORD;
  else if ((tmp->type == RED_R || tmp->type == RED_L ||
	    tmp->type == D_RED_R || tmp->type == D_RED_L)
	   && ((quote != 0 && (quote % 2 != 0)) ||
	       (dquote != 0 && (dquote % 2 != 0))))
    tmp->type = WORD;
  else if (tmp->type != WORD && quote && (quote % 2 != 0))
    tmp->type = WORD;
  return (0);
}

int		token_normaliser(t_token **list)
{
  t_token	*tmp;
  int		quote;
  int		dquote;

  tmp = *list;
  quote = 0;
  dquote = 0;
  while (tmp)
    {
      if (tmp->type == S_QUOTE)
	quote += 1;
      else if (tmp->type == D_QUOTE)
	{
	  dquote += 1;
	  if (quote && quote % 2 != 0)
	    tmp->type = WORD;
	}
      else
	token_normaliser_transform(tmp, quote, dquote);
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
