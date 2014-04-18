
#include <stdlib.h>
#include "token.h"

int		lexer_find_occurences(t_token *current, t_ttype define)
{
  t_token	*tmp;
  int		i;

  i = 0;
  tmp = current;
  while (tmp && tmp->type == define)
    {
      tmp = tmp->next;
      i++;
    }
  return (i);
}

t_token		*lexer_find_last_occurences(t_token *current, t_ttype define)
{
  t_token	*tmp;

  tmp = current;
  while (tmp && tmp->type == define)
    tmp = tmp->next;
  return (tmp);
}

int	lexer_check_is_null(t_ttype define)
{
  if (define == PIPE || define == OR || define == AND)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	lexer_check_is_param(t_ttype define)
{
  if (define == CMD || define == WORD || define == B_QUOTE
      || define == S_QUOTE || define == D_QUOTE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	lexer_check_null_cmd(t_token **list)
{
  t_token	*tmp;

  tmp = *list;
  while (tmp)
    {
      if (lexer_check_is_null(tmp->type))
	{
	  if (tmp->next == NULL)
	    return (EXIT_FAILURE);
	  else if (lexer_check_is_param(tmp->next->type) == 0)
	    return (EXIT_FAILURE);
	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
