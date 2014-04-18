
#include <stdlib.h>
#include "tokeniser.h"

int		token_bslash_changenext(t_token *tmp, int d_quote, int s_quote)
{
  t_token	*save;

  if (tmp->next->type == B_SLASH && tmp->next->next)
    {
      tmp->next->type = WORD;
      tmp->next->next->type = WORD;
      if (d_quote == 0 && s_quote == 0)
	{
	  save = tmp->next;
	  tmp->next = save->next;
	  save->next = NULL;
	  token_delete(save);
	}
      return (1);
    }
  return (0);
}

t_token		*token_backslash_change(t_token *tmp,
					t_token **begin,
					int d_quote,
					int s_quote)
{
  t_token	*save;

  if (token_bslash_changenext(tmp, d_quote, s_quote) == 1)
    return (tmp);
  else if (tmp->type == B_SLASH)
    {
      tmp->type = WORD;
      tmp->next->type = WORD;
      if (d_quote == 0 && s_quote == 0)
	{
	  save = tmp;
	  tmp = tmp->next;
	  *begin = tmp;
	  save->next = NULL;
	  token_delete(save);
	}
    }
  return (tmp);
}

int		token_backslash(t_token **list)
{
  t_token	*tmp;
  int		d_quote;
  int		s_quote;

  tmp = *list;
  d_quote = 0;
  s_quote = 0;
  while (tmp && tmp->next)
    {
      if (tmp->type == D_QUOTE)
	d_quote = (d_quote + 1) % 2;
      if (tmp->type == S_QUOTE)
	s_quote = (s_quote + 1) % 2;
      tmp = token_backslash_change(tmp, list, s_quote, d_quote);
      if (tmp)
	tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
