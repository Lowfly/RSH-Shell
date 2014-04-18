
#include <stdlib.h>
#include <stdio.h>
#include "tokeniser.h"

t_token		*token_concate_file(t_token *tmp)
{
  t_token	*ptr;

  ptr = tmp;
  while (ptr && ptr->type != WORD)
    ptr = ptr->next;
  if (ptr == NULL)
    {
      tmp->value.str = NULL;
      fprintf(stderr, "Missing name for redirect.\n");
      return (NULL);
    }
  else
    ptr->type = FILENAME;
  return (tmp);
}

int		token_dirfile(t_token **list)
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
	quote = (quote + 1) % 2;
      if (tmp->type == D_QUOTE)
	dquote = (dquote + 1) % 2;
      if (tmp->type == RED_R || tmp->type == D_RED_R ||
	   tmp->type == RED_L || tmp->type == D_RED_L)
	{
	  if (quote || dquote)
	    tmp->type = WORD;
	  else if ((tmp = token_concate_file(tmp)) == NULL)
	    return (EXIT_FAILURE);
	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
