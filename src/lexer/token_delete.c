
#include <stdlib.h>
#include "tokeniser.h"

int	token_delete_is_freeable(t_ttype type)
{
  if (type == WORD || type == CMD || type == SPACE || type == VAR
      || type == FILENAME)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void	token_delete_list(t_token *list)
{
  if (list)
    {
      if (list->next)
	token_delete_list(list->next);
      list->next = NULL;
      token_delete(list);
    }
}

int	token_delete(t_token *current)
{
  if (current == NULL)
    return (EXIT_FAILURE);
  if (current->value_type == STRING)
    {
      if (token_delete_is_freeable(current->type))
	free(current->value.str);
    }
  else if (current->value_type == LIST)
    token_delete_list(current->value.list);
  current->value.str = NULL;
  free(current);
  return (EXIT_SUCCESS);
}

int	token_delete_type(t_token **begin, t_ttype token_id)
{
  t_token       *tmp;
  t_token       *link;

  tmp = *begin;
  while (tmp)
    {
      link = tmp;
      if (tmp->next && tmp->next->type == token_id)
        {
          tmp = tmp->next->next;
          token_delete(link->next);
          link->next = tmp;
        }
      else if (tmp->type == token_id)
	{
	  *begin = tmp->next;
          token_delete(tmp);
	  tmp = *begin;
	}
      else
        tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}
